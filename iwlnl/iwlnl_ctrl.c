
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <string.h>
#include "iwlnl.h"

#define BUFLEN 24

pthread_mutex_t g_mutex;
pthread_cond_t g_cond;

int timesub_usec(struct timeval *tt, long usec);
int timeadd_usec(struct timeval *tt, long usec);

inline int timesub_usec(struct timeval *tt, long usec)
{
    if ( tt->tv_usec > usec )
    {
        tt->tv_usec -= usec;
    }
    else
    {
        tt->tv_usec = usec - tt->tv_usec;
        --(tt->tv_sec);
    }
    return 0;
}

inline int timeadd_usec(struct timeval *tt, long usec)
{
    tt->tv_usec += usec;
    if(tt->tv_usec > 1E6)
    {
        ++(tt->tv_sec);
        tt->tv_usec -= (long)1E6;
    }
    return 0;
}

void *ctrl_thread(void *arg)
{
    int stat = -1;
    long t_prior=0, t_reset=0;
    struct timeval now, tmp;
    param_t *param = (param_t *)arg;

    while(1)
    {
        if (param->updated) //update when could
        {
            stat = 0;
            param->updated = 0; //disable update flag
        }

        pthread_mutex_lock(&g_mutex);
        switch(stat)
        {
            case -1://init wait loop
                gettimeofday((struct timeval *)&now, NULL);
                now.tv_sec += 10; //long wait sleep
                printf("in wait loop...\n");
                pthread_cond_timedwait(&g_cond, &g_mutex, (struct timespec *)&now);
                break;
            case 0://sync sleep
                ++ stat;
                t_prior = param->ctrlpak.duration;
                t_reset = param->ctrlpak.period - t_prior;
                printf("p-%ld, r-%ld\n", t_prior, t_reset);
                gettimeofday((struct timeval *)&now, NULL);
                // timersub(&now, &(param->ti), &tmp);
                // timeadd_usec(&now,
                //     param->ctrlpak.period
                //     -(tmp.tv_sec*1000000 + tmp.tv_usec) % param->ctrlpak.period
                //     +param->ctrlpak.offset - CTRL_MARGIN);
                timeadd_usec(&now, param->ctrlpak.offset);
                pthread_cond_timedwait(&g_cond, &g_mutex, (struct timespec *)&now);
                printf("sync finished\n");
                break;
            case 1://prior sleep
                ++ stat;
                gettimeofday((struct timeval *)&now, NULL);
                nlsock_set_prior(); //NOTE: priorized here
                timeadd_usec(&now, t_prior);
                pthread_cond_timedwait(&g_cond, &g_mutex, (struct timespec *)&now);
                break;
            case 2://reset sleep
                -- stat; //loop
                gettimeofday((struct timeval *)&now, NULL);
                nlsock_reset_prior(); //NOTE: reset priority here
                timeadd_usec(&now, t_reset);
                pthread_cond_timedwait(&g_cond, &g_mutex, (struct timespec *)&now);
                break;
            default:
                stat = 0;
        }
        pthread_mutex_unlock(&g_mutex);
    }
}

int serial_open(const char *port)
{
    int fd;

    if ((fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY)) < 0)
    {
        perror("Can't Open Serial Port");
        return -1;
    }
    if (fcntl(fd, F_SETFL, 0) < 0)
    {
        perror("fcntl failed");
        return -1;
    }

    return fd;
}
 
int serial_init(int fd)  
{  
    struct termios options;

    //get attr
    if ( tcgetattr(fd, &options) != 0)
    {
        perror("Setup Serial 1");
        return -1;
    }

    //setup baudrate 115200
    cfsetispeed(&options, B115200); //input stream speed
    cfsetospeed(&options, B115200); //output stream speed

    options.c_cflag |= CLOCAL; //permission: local usage
    options.c_cflag |= CREAD; //permission: read data
    options.c_cflag &= ~CRTSCTS; //no flow control, RTS/CTS

    //Setup data bit,  8
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    //Setup parity bit, even parity check
    options.c_cflag |= PARENB;         
    options.c_cflag &= ~PARODD;         
    options.c_iflag |= INPCK; 
    //Setup stop bit, 1
    options.c_cflag &= ~CSTOPB; // stopbit = 1
	//raw data output
	options.c_oflag &= ~OPOST;
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_cc[VTIME] = 1; //read byte wait at least 1*(1/10) second
    options.c_cc[VMIN] = 1; //read 1 byte at least each time
    tcflush(fd, TCIFLUSH);

    //set attr
    if (tcsetattr(fd, TCSANOW, &options) != 0)
    {
        perror("Serial Set Error");
        return -1;
    }

    return 1;
}  

int serial_recv(int fd, char *recv_buf, int len)
{
    int recv_len, fs_sel;
    fd_set fs_read;

    FD_ZERO(&fs_read);
    FD_SET(fd, &fs_read);
    fs_sel = select(fd+1, &fs_read, NULL, NULL, NULL);
    
    if(fs_sel)
    {
        recv_len = read(fd, recv_buf, len);
        return recv_len;
    }
    
    return -1;
}

int serial_send(int fd, char *send_buf, int len)
{
    int ret;
    ret = write(fd, send_buf, len);

    if (ret == len)
    {
        return len;
    }
    else
    {
        tcflush(fd, TCOFLUSH);
        return -1;
    }
}


void* echo_thread(void *arg)
{
    int fd, recv_len;
    struct timeval t0;
    char buf[BUFLEN];
    param_t *param = (param_t *)arg;
    ctrlpak_t *cpak = (ctrlpak_t *)buf;
    
    if ( (fd = serial_open("/dev/ttyUSB0")) < 0 )
    {
        exit(1);
    }
    else
    {
        serial_init(fd);
    }
    
    while(1)
    {
        // period 0, wait
        
        if ( (recv_len=serial_recv(fd, buf, sizeof(ctrlpak_t))) < 0)
        {
            printf("serial ctrl_recv error\n");          
            continue;
        }
        gettimeofday(&t0, NULL);
        param->ctrlpak = *cpak;
        printf("%d, %d, %d\n", cpak->duration, cpak->offset, cpak->period);

        // //period 1, echo
        // if (serial_send(fd, buf, sizeof(ctrlpak_t)) < 0)
        // {
        //     printf("serial echo_send error\n");          
        //     continue;
        // }

        // //period 2
        // if ( (recv_len=serial_recv(fd, buf, sizeof(uint32_t))) < 0)
        // {
        //     perror("serial time_recv error");          
        //     continue;
        // }
        // timesub_usec(&t0, *(long *)buf);
        // param->ti = t0;
        
        //update now
        pthread_mutex_lock(&g_mutex);
        param->updated = 1;
        pthread_cond_signal(&g_cond);
        pthread_mutex_unlock(&g_mutex);  
    }
    
    return ((void *)0);
}

int main(int argc, char const *argv[])
{
    int ret;
    pthread_t echo_t, ctrl_t;
    param_t param = {0};

    nlsock_init();
    pthread_mutex_init(&g_mutex, NULL);
    pthread_cond_init(&g_cond, NULL);

    if ((ret = pthread_create(&echo_t, NULL, echo_thread, &param)) < 0)
    {
        perror("creat_udp_thread_error");
        return -1;
    }
    
    if ((ret = pthread_create(&ctrl_t, NULL, ctrl_thread, &param)) < 0)
    {
        perror("create_ctrl_thread_error");
        return -1;
    }

    pthread_join(echo_t, NULL);
    pthread_join(ctrl_t, NULL);
    nlsock_init();
    pthread_mutex_destroy(&g_mutex);
    pthread_cond_destroy(&g_cond);
    return 0;
}
