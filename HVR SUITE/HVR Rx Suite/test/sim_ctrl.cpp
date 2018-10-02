
#include <windows.h>
#include <iostream>
#include <chrono>

#define RECV_BUF 2048

int main(int argc, char const *argv[])
{
    
    while(true)
    {
        // period 0
        auto t0 = std::chrono::high_resolution_clock::now();
        // period 1
        Sleep(1E3);
        // period 2
        auto t1 = std::chrono::high_resolution_clock::now();
        auto tmp = std::chrono::duration_cast<std::chrono::microseconds>(t1-t0).count();
        std::cout << tmp << " usec" << std::endl;
        Sleep(1E3);
    }
    
    return 0;
}
