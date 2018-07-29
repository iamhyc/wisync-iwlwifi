# mvm/mac80211.c

**tx**

> * Handler that 802.11 module calls for **each transmitted frame**. *skb* contains the buffer starting from the IEEE 802.11 header.  **Must be atomic.**
> * 发送函数，从这里传输给底层driver；该函数不会fail
>
> @param **hw**: (struct ieee80211_hw \*)
> @param **control**: (struct ieee80211_tx_control \*)
> @param **skb**: (struct sk_buff \*)

```C
void iwl_mvm_mac_tx()
```



**start**

> * Called before the first netdevice attached to the hardware is enabled. This should turn on the hardware and must turn on frame reception (for possibly enabled monitor interfaces.) **Must be implemented and can sleep.**
> * 一个hardware可以add多个interface来implement多个role；于是在add动作之前需要start
>
> @param **hw**: (struct ieee80211_hw \*)

```C
int iwl_mvm_mac_start()
```



**stop**

> * Called after last netdevice attached to the hardware is disabled. This should turn off the hardware (at least  it must turn off frame reception.) May be called right after add_interface if that rejects  an interface. If you added any work onto the mac80211 workqueue you should ensure to cancel it on this callback. **Must be implemented and can sleep.**
> * 在上述条件下stop会被触发
>
> @param **hw**: (struct ieee80211_hw \*)

```C
void iwl_mvm_mac_stop()
```



**suspend**

> * Suspend the device; mac80211 itself will quiesce before and stop transmitting and doing any other configuration, and then ask the device to suspend. This is only invoked when WoWLAN is configured, otherwise the device is deconfigured completely and reconfigured at resume time. The driver may also impose special conditions under which it wants to use the "normal" suspend (deconfigure), say if it only supports WoWLAN when the device is associated.
> * 如上文
>
> @param **wowlan**: (struct cfg80211_wowlan \*)
>
> @param **hw**: (struct ieee80211_hw \*)

```C
int iwl_mvm_suspend() //CONFIG_PM_SLEEP
```



**resume**

> * If WoWLAN was configured, this indicates that mac80211 is now resuming its operation, after this the device must be fully functional again.
> * If this returns an error, the only way out is to also unregister the device. If it returns 1, then mac80211 will also go through the regular complete restart on resume.
> * suspend的反义词；返回0是没问题的，其他状态如上文所示
>
> @param **hw**: (struct ieee80211_hw \*)

```C
int iwl_mvm_resume() //CONFIG_PM_SLEEP
```



**set_wakeup**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **enabled** : (bool)

```C
void iwl_mvm_set_wakeup() //CONFIG_PM_SLEEP
```



**add_interface**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)

```C
int iwl_mvm_mac_add_interface()
```



**change_interface**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **new_type** : (enum nl80211_iftype)
>
> @param **p2p**: (bool)



**remove_interface**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)

```C
void iwl_mvm_mac_remove_interface()
```



**config**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **changed**: (u32)

```C
int iwl_mvm_mac_config()
{
	return 0;
}
```



**bss_info_changed**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **info**: (struct ieee80211_bss_conf \*)
>
> @param **changed**: (u32)

```C
void iwl_mvm_bss_info_changed()
```



**prepare_multicast**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **mc_list**: (struct netdev_hw_addr_list \*)

```C
u64 iwl_mvm_prepare_multicast()
```



**configure_filter**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **changed_flags**: (unsigned int)
>
> @param **total_flags**: (unsigned int \*),
>
> @param **multicast**: (u64)

```C
void iwl_mvm_configure_filter()
```



**config_iface_filter**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **filter_flags**: (unsigned int)
>
> @param **changed_flags**: (unsigned int)

```C
void iwl_mvm_config_iface_filter()
```



**set_tim**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **sta**: (struct ieee80211_sta \*)
>
> @param **set**: (bool)

```C
int iwl_mvm_set_tim()
```



**set_key**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param  **cmd**:(enum set_key_cmd)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **sta**: (struct ieee80211_sta \*)
>
> @param **key**: (struct ieee80211_key_conf \*)

```C
int iwl_mvm_mac_set_key()
```



**update_tkip_key**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **key**: (struct ieee80211_key_conf \*)
>
> @param **sta**: (struct ieee80211_sta \*)
>
> @param **iv32**: (u32)
>
> @param **phase1key**: (u16 \*)

```C
void iwl_mvm_mac_update_tkip_key()
```



**set_rekey_data**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **data**: (struct cfg80211_gtk_rekey_data \*)

```C
void iwl_mvm_set_rekey_data() //CONFIG_PM_SLEEP
```



**set_default_unicast_key**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **idx**: (int)

```C
void iwl_mvm_set_default_unicast_key() //CONFIG_PM_SLEEP
```



**hw_scan**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **req**: (struct ieee80211_scan_request \*)

```C
int iwl_mvm_mac_hw_scan()
```



**cancel_hw_scan**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)

```C
void iwl_mvm_mac_cancel_hw_scan()
```



**sched_scan_start**

> Description

```C
int iwl_mvm_mac_sched_scan_start()
```



**sched_scan_stop**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **req**: (struct cfg80211_sched_scan_request \*)
>
> @param **ies**: (ieee80211_scan_ies \*)

```C
int iwl_mvm_mac_sched_scan_stop()
```



**sw_scan_start**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **mac_addr**: (const u8 \*)



**sw_scan_complete**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)



**get_stats**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **stats**: (struct ieee80211_low_level_stats \*)



**get_key_seq**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **key**: (struct ieee80211_key_conf \*)
>
> @param **seq**: (struct ieee80211_key_seq \*)



**set_frag_threshold**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **value**: (u32)



**set_rts_threshold**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **value**: (u32)

```C
int iwl_mvm_mac_set_rts_threshold()
```



**sta_add**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **sta**: (struct ieee80211_sta \*)



**sta_remove**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **sta**: (struct ieee80211_sta \*)



**sta_add_debugfs**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **sta**: (struct ieee80211_sta \*)
>
> @param **dir**: (struct dentry \*)



**sta_notify**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **cmd**: (enum sta_notify_cmd)
>
> @param **sta**: (struct ieee80211_sta \*)

```C
void iwl_mvm_mac_sta_notify()
```



**sta_state**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **sta**: (struct ieee80211_sta \*)
>
> @param **old_state**: (enum ieee80211_sta_state)
>
> @param **new_state**: (enum ieee80211_sta_state)

```C
int iwl_mvm_mac_sta_state()
```



**sta_pre_rcu_remove**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **sta**: (struct ieee80211_sta \*)

```C
void iwl_mvm_sta_pre_rcu_remove()
```



**sta_rc_update**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **sta**: (struct ieee80211_sta \*)
>
> @param **changed**: (u32)

```C
void iwl_mvm_sta_rc_update()
```



**sta_rate_tbl_update**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **sta**: (struct ieee80211_sta \*)



**sta_statistics**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **sta**: (struct ieee80211_sta \*)
>
> @param **sinfo**: (struct station_info \*)

```C
void iwl_mvm_mac_sta_statistics()
```



**conf_tx**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **ac**: (u16)
>
> @param **params**: (const struct ieee80211_tx_queue_params \*)

```C
int iwl_mvm_mac_conf_tx()
```



**get_tsf**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)



**set_tsf**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **tsf**: (u64)



**offset_tsf**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **offset**: (s64)



**reset_tsf**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)



**tx_last_beacon**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)

```C
int iwl_mvm_tx_last_beacon()
```



**get_survey**

> Description
>
> @param **hw**: (struct ieee80211_hw *)
>
> @param **idx**: (int)
>
> @param **survey**: (struct survey_info \*)

```C
int iwl_mvm_mac_get_survey()
```



**rfkill_poll**

> Description
>
> @param **hw**: (struct ieee80211_hw *)



**set_coverage_class**

> Description
>
> @param **hw**: (struct ieee80211_hw *)
>
> @param **coverage_class**: (s16)



**testmode_cmd**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **data**: (void *)
>
> @param **len**: (int)

```C
int iwl_mvm_mac_testmode_cmd() //CONFIG_NL80211_TESTMODE
```



**testmode_dump**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **skb**: (struct sk_buff \*)
>
> @param **cb**: (struct netlink_callback \*)
>
> @param **data**: (void *)
>
> @param **len**: (int)



**flush**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **queues**: (u32)
>
> @param **drop**: (bool)

```C
void iwl_mvm_mac_flush()
```



**channel_switch**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **ch_switch**: (struct ieee80211_channel_switch \*)

```C
void iwl_mvm_channel_switch()
```



**set_antenna**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **tx_ant**: (u32)
>
> @param **rx_ant**: (u32)



**get_antenna**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **tx_ant**: (u32 *)
>
> @param **rx_ant**: (u32 *)



**remain_on_channel**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **chan**: ( struct ieee80211_channel \*)
>
> @param **duration**: (int)
>
> @param **type**: (enum ieee80211_roc_type)

```C
int iwl_mvm_roc()
```



**cancel_remain_on_channel**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)

```C
int iwl_mvm_cancel_roc()
```



**set_ringparam**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **tx**: (u32)
>
> @param **rx**: (u32)



**get_ringparam**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **tx**: (u32 \*)
>
> @param **tx_max**: (u32 \*)
>
> @param **rx**: (u32 \*)
>
> @param **rx_max**: (u32 \*)



**tx_frames_pending**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)



**set_bitrate_mask**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **mask**: (const struct cfg80211_bitrate_mask \*)



**event_callback**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **event**: (const struct ieee80211_event \*)

```C
void iwl_mvm_mac_event_callback()
```



**release_buffered_frames**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **sta**: (struct ieee80211_sta \*)
>
> @param **tids**: (u16)
>
> @param **num_frames**: (int)
>
> @param **reason**: (enum ieee80211_frame_release_type)
>
> @param **more_data**: (bool)

```C
void iwl_mvm_mac_release_buffered_frames()
```



**allow_buffered_frames**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **sta**: (struct ieee80211_sta \*)
>
> @param **tids**: (u16)
>
> @param **num_frames**: (int)
>
> @param **reason**: (enum ieee80211_frame_release_type)
>
> @param **more_data**: (bool)

```C
void iwl_mvm_mac_allow_buffered_frames()
```



**get_et_sset_count**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **sset**: (int)



**get_et_stats**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **stats**: (struct ethtool_stats \*)
>
> @param **data**: (u64 \*)



**get_et_strings**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **sset**: (u32)
>
> @param **data**: (u8 *)



**mgd_prepare_tx**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)

```C
void iwl_mvm_mac_mgd_prepare_tx()
```



**mgd_protect_tdls_discover**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)

```C
void iwl_mvm_mac_mgd_protect_tdls_discover()
```



**add_chanctx**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **ctx**: (struct ieee80211_chanctx_conf \*)

```C
int iwl_mvm_add_chanctx()
```



**remove_chanctx**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **ctx**: (struct ieee80211_chanctx_conf \*)

```C
void iwl_mvm_remove_chanctx()
```



**change_chanctx**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **ctx**: (struct ieee80211_chanctx_conf \*)
>
> @param **changed**: (u32)

```C
void iwl_mvm_change_chanctx()
```



**assign_vif_chanctx**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **ctx**: (struct ieee80211_chanctx_conf \*)

```C
int iwl_mvm_assign_vif_chanctx()
```



**unassign_vif_chanctx**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **ctx**: (struct ieee80211_chanctx_conf \*) 

```C
void iwl_mvm_unassign_vif_chanctx()
```



**switch_vif_chanctx**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vifs**: (struct ieee80211_vif_chanctx_switch \*)
>
> @param **n_vifs**: (int)
>
> @param **mode**: (enum ieee80211_chanctx_switch_mode)

```C
int iwl_mvm_switch_vif_chanctx()
```



**start_ap**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)

```C
int iwl_mvm_start_ap_ibss()
```



**stop_ap**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)

```C
void iwl_mvm_stop_ap_ibss()
```



**reconfig_complete**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **reconfig_type**: (enum ieee80211_reconfig_type)

```C
void iwl_mvm_mac_reconfig_complete()
```



**ipv6_addr_change**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **idev**: (struct inet6_dev \*)

```C
void iwl_mvm_ipv6_addr_change() //CONFIG_PM_SLEEP && IS_ENABLED(CONFIG_IPV6)
```



**channel_switch_beacon**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **chandef**: (struct cfg80211_chan_def \*)



**pre_channel_switch**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **ch_switch**: (struct ieee80211_channel_switch \*)

```C
int iwl_mvm_pre_channel_switch()
```



**post_channel_switch**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)

```C
int iwl_mvm_post_channel_switch()
```



**join_ibss**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)

```C
int iwl_mvm_start_ap_ibss()
```



**leave_ibss**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)

```C
void iwl_mvm_stop_ap_ibss()
```



**get_expected_throughput**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **sta**: (struct ieee80211_sta \*)



**get_txpower**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **dbm**: (int)



**tdls_channel_switch**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **sta**: (struct ieee80211_sta \*)
>
> @param **oper_class**: (u8)
>
> @param **chandef**: (struct cfg80211_chan_def \*)
>
> @param **tmpl_skb**: (struct sk_buff \*)
>
> @param **ch_sw_tm_ie**: (u32)

```C
int iwl_mvm_tdls_channel_switch()
```



**tdls_cancel_channel_switch**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **sta**: (struct ieee80211_sta \*)

```C
void tdls_cancel_channel_switch()
```



**tdls_recv_channel_switch**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **params**: (struct ieee80211_tdls_ch_sw_params \*)

```C
void iwl_mvm_tdls_recv_channel_switch()
```



**wake_tx_queue**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **txq**: (struct ieee80211_txq \*)



**sync_rx_queues**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)

```C
void iwl_mvm_sync_rx_queues()
```



**start_nan**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **conf**: (struct cfg80211_nan_conf \*)



**stop_nan**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)



**nan_change_conf**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **conf**: (struct cfg80211_nan_conf \*)
>
> @param **changes**: (u32)



**add_nan_func**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **nan_func**: (const struct cfg80211_nan_func \*)



**del_nan_func**

> Description
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **instance_id**: (u8)



**ampdu_action**

> * Perform a certain A-MPDU action. The RA/TID combination determines the destination and TID we want the ampdu action to be performed for. The action is defined through ieee80211_ampdu_mlme_action. **The callback can sleep.**
>
> @param **hw**: (struct ieee80211_hw \*)
>
> @param **vif**: (struct ieee80211_vif \*)
>
> @param **params**: (struct ieee80211_ampdu_params \*)

```C
int iwl_mvm_mac_ampdu_action()
```

