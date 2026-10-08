// Auto-generated guard stubs for SPRD wifi HAL shim
.text

   .globl shim_wifi_get_supported_feature_set
   .p2align 2
shim_wifi_get_supported_feature_set:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_supported_feature_set
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_supported_feature_set]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_concurrency_matrix
   .p2align 2
shim_wifi_get_concurrency_matrix:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_concurrency_matrix
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_concurrency_matrix]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_set_scanning_mac_oui
   .p2align 2
shim_wifi_set_scanning_mac_oui:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_set_scanning_mac_oui
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_set_scanning_mac_oui]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_supported_channels
   .p2align 2
shim_wifi_get_supported_channels:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_supported_channels
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_supported_channels]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_is_epr_supported
   .p2align 2
shim_wifi_is_epr_supported:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_is_epr_supported
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_is_epr_supported]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_ifaces
   .p2align 2
shim_wifi_get_ifaces:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_ifaces
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_ifaces]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_iface_name
   .p2align 2
shim_wifi_get_iface_name:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_iface_name
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_iface_name]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_set_iface_event_handler
   .p2align 2
shim_wifi_set_iface_event_handler:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_set_iface_event_handler
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_set_iface_event_handler]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_reset_iface_event_handler
   .p2align 2
shim_wifi_reset_iface_event_handler:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_reset_iface_event_handler
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_reset_iface_event_handler]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_start_gscan
   .p2align 2
shim_wifi_start_gscan:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_start_gscan
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_start_gscan]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_stop_gscan
   .p2align 2
shim_wifi_stop_gscan:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_stop_gscan
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_stop_gscan]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_cached_gscan_results
   .p2align 2
shim_wifi_get_cached_gscan_results:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_cached_gscan_results
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_cached_gscan_results]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_set_bssid_hotlist
   .p2align 2
shim_wifi_set_bssid_hotlist:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_set_bssid_hotlist
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_set_bssid_hotlist]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_reset_bssid_hotlist
   .p2align 2
shim_wifi_reset_bssid_hotlist:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_reset_bssid_hotlist
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_reset_bssid_hotlist]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_set_significant_change_handler
   .p2align 2
shim_wifi_set_significant_change_handler:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_set_significant_change_handler
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_set_significant_change_handler]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_reset_significant_change_handler
   .p2align 2
shim_wifi_reset_significant_change_handler:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_reset_significant_change_handler
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_reset_significant_change_handler]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_gscan_capabilities
   .p2align 2
shim_wifi_get_gscan_capabilities:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_gscan_capabilities
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_gscan_capabilities]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_set_link_stats
   .p2align 2
shim_wifi_set_link_stats:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_set_link_stats
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_set_link_stats]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_link_stats
   .p2align 2
shim_wifi_get_link_stats:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_get_link_stats
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_link_stats]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_clear_link_stats
   .p2align 2
shim_wifi_clear_link_stats:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_clear_link_stats
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_clear_link_stats]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_valid_channels
   .p2align 2
shim_wifi_get_valid_channels:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_valid_channels
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_valid_channels]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_rtt_range_request
   .p2align 2
shim_wifi_rtt_range_request:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_rtt_range_request
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_rtt_range_request]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_rtt_range_cancel
   .p2align 2
shim_wifi_rtt_range_cancel:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_rtt_range_cancel
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_rtt_range_cancel]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_rtt_capabilities
   .p2align 2
shim_wifi_get_rtt_capabilities:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_rtt_capabilities
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_rtt_capabilities]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_rtt_get_responder_info
   .p2align 2
shim_wifi_rtt_get_responder_info:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_rtt_get_responder_info
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_rtt_get_responder_info]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_enable_responder
   .p2align 2
shim_wifi_enable_responder:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_enable_responder
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_enable_responder]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_disable_responder
   .p2align 2
shim_wifi_disable_responder:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_disable_responder
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_disable_responder]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_set_nodfs_flag
   .p2align 2
shim_wifi_set_nodfs_flag:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_set_nodfs_flag
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_set_nodfs_flag]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_start_logging
   .p2align 2
shim_wifi_start_logging:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_start_logging
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_start_logging]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_set_epno_list
   .p2align 2
shim_wifi_set_epno_list:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_set_epno_list
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_set_epno_list]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_reset_epno_list
   .p2align 2
shim_wifi_reset_epno_list:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_reset_epno_list
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_reset_epno_list]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_set_country_code
   .p2align 2
shim_wifi_set_country_code:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_set_country_code
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_set_country_code]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_firmware_memory_dump
   .p2align 2
shim_wifi_get_firmware_memory_dump:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_firmware_memory_dump
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_firmware_memory_dump]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_set_log_handler
   .p2align 2
shim_wifi_set_log_handler:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_set_log_handler
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_set_log_handler]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_reset_log_handler
   .p2align 2
shim_wifi_reset_log_handler:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_reset_log_handler
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_reset_log_handler]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_set_alert_handler
   .p2align 2
shim_wifi_set_alert_handler:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_set_alert_handler
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_set_alert_handler]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_reset_alert_handler
   .p2align 2
shim_wifi_reset_alert_handler:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_reset_alert_handler
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_reset_alert_handler]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_firmware_version
   .p2align 2
shim_wifi_get_firmware_version:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_firmware_version
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_firmware_version]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_ring_buffers_status
   .p2align 2
shim_wifi_get_ring_buffers_status:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_ring_buffers_status
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_ring_buffers_status]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_logger_supported_feature_set
   .p2align 2
shim_wifi_get_logger_supported_feature_set:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_logger_supported_feature_set
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_logger_supported_feature_set]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_ring_data
   .p2align 2
shim_wifi_get_ring_data:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_ring_data
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_ring_data]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_enable_tdls
   .p2align 2
shim_wifi_enable_tdls:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_enable_tdls
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_enable_tdls]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_disable_tdls
   .p2align 2
shim_wifi_disable_tdls:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_disable_tdls
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_disable_tdls]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_tdls_status
   .p2align 2
shim_wifi_get_tdls_status:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_tdls_status
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_tdls_status]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_tdls_capabilities
   .p2align 2
shim_wifi_get_tdls_capabilities:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_tdls_capabilities
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_tdls_capabilities]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_driver_version
   .p2align 2
shim_wifi_get_driver_version:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_driver_version
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_driver_version]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_set_passpoint_list
   .p2align 2
shim_wifi_set_passpoint_list:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_set_passpoint_list
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_set_passpoint_list]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_reset_passpoint_list
   .p2align 2
shim_wifi_reset_passpoint_list:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_reset_passpoint_list
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_reset_passpoint_list]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_set_lci
   .p2align 2
shim_wifi_set_lci:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_set_lci
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_set_lci]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_set_lcr
   .p2align 2
shim_wifi_set_lcr:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_set_lcr
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_set_lcr]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_start_sending_offloaded_packet
   .p2align 2
shim_wifi_start_sending_offloaded_packet:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_start_sending_offloaded_packet
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_start_sending_offloaded_packet]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_stop_sending_offloaded_packet
   .p2align 2
shim_wifi_stop_sending_offloaded_packet:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_stop_sending_offloaded_packet
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_stop_sending_offloaded_packet]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_start_rssi_monitoring
   .p2align 2
shim_wifi_start_rssi_monitoring:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_start_rssi_monitoring
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_start_rssi_monitoring]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_stop_rssi_monitoring
   .p2align 2
shim_wifi_stop_rssi_monitoring:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_stop_rssi_monitoring
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_stop_rssi_monitoring]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_wake_reason_stats
   .p2align 2
shim_wifi_get_wake_reason_stats:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_wake_reason_stats
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_wake_reason_stats]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_configure_nd_offload
   .p2align 2
shim_wifi_configure_nd_offload:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_configure_nd_offload
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_configure_nd_offload]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_driver_memory_dump
   .p2align 2
shim_wifi_get_driver_memory_dump:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_driver_memory_dump
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_driver_memory_dump]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_start_pkt_fate_monitoring
   .p2align 2
shim_wifi_start_pkt_fate_monitoring:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_start_pkt_fate_monitoring
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_start_pkt_fate_monitoring]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_tx_pkt_fates
   .p2align 2
shim_wifi_get_tx_pkt_fates:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_tx_pkt_fates
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_tx_pkt_fates]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_rx_pkt_fates
   .p2align 2
shim_wifi_get_rx_pkt_fates:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_rx_pkt_fates
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_rx_pkt_fates]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_nan_enable_request
   .p2align 2
shim_wifi_nan_enable_request:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_nan_enable_request
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_nan_enable_request]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_nan_disable_request
   .p2align 2
shim_wifi_nan_disable_request:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_nan_disable_request
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_nan_disable_request]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_nan_publish_request
   .p2align 2
shim_wifi_nan_publish_request:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_nan_publish_request
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_nan_publish_request]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_nan_publish_cancel_request
   .p2align 2
shim_wifi_nan_publish_cancel_request:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_nan_publish_cancel_request
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_nan_publish_cancel_request]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_nan_subscribe_request
   .p2align 2
shim_wifi_nan_subscribe_request:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_nan_subscribe_request
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_nan_subscribe_request]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_nan_subscribe_cancel_request
   .p2align 2
shim_wifi_nan_subscribe_cancel_request:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_nan_subscribe_cancel_request
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_nan_subscribe_cancel_request]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_nan_transmit_followup_request
   .p2align 2
shim_wifi_nan_transmit_followup_request:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_nan_transmit_followup_request
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_nan_transmit_followup_request]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_nan_stats_request
   .p2align 2
shim_wifi_nan_stats_request:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_nan_stats_request
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_nan_stats_request]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_nan_config_request
   .p2align 2
shim_wifi_nan_config_request:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_nan_config_request
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_nan_config_request]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_nan_tca_request
   .p2align 2
shim_wifi_nan_tca_request:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_nan_tca_request
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_nan_tca_request]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_nan_beacon_sdf_payload_request
   .p2align 2
shim_wifi_nan_beacon_sdf_payload_request:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_nan_beacon_sdf_payload_request
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_nan_beacon_sdf_payload_request]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_nan_register_handler
   .p2align 2
shim_wifi_nan_register_handler:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_nan_register_handler
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_nan_register_handler]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_nan_get_version
   .p2align 2
shim_wifi_nan_get_version:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_nan_get_version
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_nan_get_version]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_nan_get_capabilities
   .p2align 2
shim_wifi_nan_get_capabilities:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_nan_get_capabilities
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_nan_get_capabilities]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_nan_data_interface_create
   .p2align 2
shim_wifi_nan_data_interface_create:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_nan_data_interface_create
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_nan_data_interface_create]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_nan_data_interface_delete
   .p2align 2
shim_wifi_nan_data_interface_delete:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_nan_data_interface_delete
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_nan_data_interface_delete]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_nan_data_request_initiator
   .p2align 2
shim_wifi_nan_data_request_initiator:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_nan_data_request_initiator
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_nan_data_request_initiator]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_nan_data_indication_response
   .p2align 2
shim_wifi_nan_data_indication_response:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_nan_data_indication_response
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_nan_data_indication_response]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_nan_data_end
   .p2align 2
shim_wifi_nan_data_end:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_nan_data_end
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_nan_data_end]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_select_tx_power_scenario
   .p2align 2
shim_wifi_select_tx_power_scenario:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_select_tx_power_scenario
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_select_tx_power_scenario]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_reset_tx_power_scenario
   .p2align 2
shim_wifi_reset_tx_power_scenario:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_reset_tx_power_scenario
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_reset_tx_power_scenario]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_packet_filter_capabilities
   .p2align 2
shim_wifi_get_packet_filter_capabilities:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_packet_filter_capabilities
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_packet_filter_capabilities]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_set_packet_filter
   .p2align 2
shim_wifi_set_packet_filter:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_set_packet_filter
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_set_packet_filter]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_read_packet_filter
   .p2align 2
shim_wifi_read_packet_filter:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_read_packet_filter
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_read_packet_filter]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_roaming_capabilities
   .p2align 2
shim_wifi_get_roaming_capabilities:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_roaming_capabilities
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_roaming_capabilities]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_enable_firmware_roaming
   .p2align 2
shim_wifi_enable_firmware_roaming:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_enable_firmware_roaming
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_enable_firmware_roaming]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_configure_roaming
   .p2align 2
shim_wifi_configure_roaming:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_configure_roaming
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_configure_roaming]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_set_radio_mode_change_handler
   .p2align 2
shim_wifi_set_radio_mode_change_handler:
   cbz x1, 1f
   adrp x9, :got:wifishim_orig_wifi_set_radio_mode_change_handler
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_set_radio_mode_change_handler]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_set_latency_mode
   .p2align 2
shim_wifi_set_latency_mode:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_set_latency_mode
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_set_latency_mode]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_set_thermal_mitigation_mode
   .p2align 2
shim_wifi_set_thermal_mitigation_mode:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_set_thermal_mitigation_mode
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_set_thermal_mitigation_mode]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_map_dscp_access_category
   .p2align 2
shim_wifi_map_dscp_access_category:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_map_dscp_access_category
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_map_dscp_access_category]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_reset_dscp_mapping
   .p2align 2
shim_wifi_reset_dscp_mapping:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_reset_dscp_mapping
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_reset_dscp_mapping]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_virtual_interface_create
   .p2align 2
shim_wifi_virtual_interface_create:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_virtual_interface_create
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_virtual_interface_create]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_virtual_interface_delete
   .p2align 2
shim_wifi_virtual_interface_delete:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_virtual_interface_delete
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_virtual_interface_delete]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_set_subsystem_restart_handler
   .p2align 2
shim_wifi_set_subsystem_restart_handler:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_set_subsystem_restart_handler
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_set_subsystem_restart_handler]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_supported_iface_name
   .p2align 2
shim_wifi_get_supported_iface_name:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_supported_iface_name
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_supported_iface_name]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_chip_feature_set
   .p2align 2
shim_wifi_get_chip_feature_set:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_chip_feature_set
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_chip_feature_set]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_multi_sta_set_primary_connection
   .p2align 2
shim_wifi_multi_sta_set_primary_connection:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_multi_sta_set_primary_connection
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_multi_sta_set_primary_connection]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_multi_sta_set_use_case
   .p2align 2
shim_wifi_multi_sta_set_use_case:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_multi_sta_set_use_case
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_multi_sta_set_use_case]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_set_coex_unsafe_channels
   .p2align 2
shim_wifi_set_coex_unsafe_channels:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_set_coex_unsafe_channels
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_set_coex_unsafe_channels]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_set_voip_mode
   .p2align 2
shim_wifi_set_voip_mode:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_set_voip_mode
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_set_voip_mode]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_twt_register_handler
   .p2align 2
shim_wifi_twt_register_handler:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_twt_register_handler
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_twt_register_handler]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_twt_get_capability
   .p2align 2
shim_wifi_twt_get_capability:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_twt_get_capability
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_twt_get_capability]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_twt_setup_request
   .p2align 2
shim_wifi_twt_setup_request:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_twt_setup_request
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_twt_setup_request]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_twt_teardown_request
   .p2align 2
shim_wifi_twt_teardown_request:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_twt_teardown_request
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_twt_teardown_request]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_twt_info_frame_request
   .p2align 2
shim_wifi_twt_info_frame_request:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_twt_info_frame_request
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_twt_info_frame_request]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_twt_get_stats
   .p2align 2
shim_wifi_twt_get_stats:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_twt_get_stats
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_twt_get_stats]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_twt_clear_stats
   .p2align 2
shim_wifi_twt_clear_stats:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_twt_clear_stats
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_twt_clear_stats]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_set_dtim_config
   .p2align 2
shim_wifi_set_dtim_config:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_set_dtim_config
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_set_dtim_config]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_get_usable_channels
   .p2align 2
shim_wifi_get_usable_channels:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_get_usable_channels
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_get_usable_channels]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_trigger_subsystem_restart
   .p2align 2
shim_wifi_trigger_subsystem_restart:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_trigger_subsystem_restart
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_trigger_subsystem_restart]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_cleanup
   .p2align 2
shim_wifi_cleanup:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_cleanup
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_cleanup]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret

   .globl shim_wifi_event_loop
   .p2align 2
shim_wifi_event_loop:
   cbz x0, 1f
   adrp x9, :got:wifishim_orig_wifi_event_loop
   ldr  x9, [x9, :got_lo12:wifishim_orig_wifi_event_loop]
   ldr  x9, [x9]
   cbz  x9, 1f
   br   x9
1: mov w0, #-2
   ret
