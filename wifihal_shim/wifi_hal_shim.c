// Interposer for the SPRD vendor wifi HAL blob.
// The blob dereferences wifi_handle/wifi_interface_handle args without NULL
// checks, but the AOSP wifi service issues capability queries before
// wifi_initialize() has produced a handle, which crashed in wifi_get_ifaces.
// Every entry point that takes a handle is guarded: a NULL handle returns
// WIFI_ERROR_UNINITIALIZED (-2) instead of crashing the HAL service.
#include <dlfcn.h>
#include <log/log.h>
#include <hardware_legacy/wifi_hal.h>

#define IMPL_LIB "/vendor/lib64/libwifi-hal-sprd-impl.so"

typedef wifi_error (*init_fn_t)(wifi_hal_fn *);

void *wifishim_orig_wifi_get_supported_feature_set;
extern void shim_wifi_get_supported_feature_set(void);
void *wifishim_orig_wifi_get_concurrency_matrix;
extern void shim_wifi_get_concurrency_matrix(void);
void *wifishim_orig_wifi_set_scanning_mac_oui;
extern void shim_wifi_set_scanning_mac_oui(void);
void *wifishim_orig_wifi_get_supported_channels;
extern void shim_wifi_get_supported_channels(void);
void *wifishim_orig_wifi_is_epr_supported;
extern void shim_wifi_is_epr_supported(void);
void *wifishim_orig_wifi_get_ifaces;
extern void shim_wifi_get_ifaces(void);
void *wifishim_orig_wifi_get_iface_name;
extern void shim_wifi_get_iface_name(void);
void *wifishim_orig_wifi_set_iface_event_handler;
extern void shim_wifi_set_iface_event_handler(void);
void *wifishim_orig_wifi_reset_iface_event_handler;
extern void shim_wifi_reset_iface_event_handler(void);
void *wifishim_orig_wifi_start_gscan;
extern void shim_wifi_start_gscan(void);
void *wifishim_orig_wifi_stop_gscan;
extern void shim_wifi_stop_gscan(void);
void *wifishim_orig_wifi_get_cached_gscan_results;
extern void shim_wifi_get_cached_gscan_results(void);
void *wifishim_orig_wifi_set_bssid_hotlist;
extern void shim_wifi_set_bssid_hotlist(void);
void *wifishim_orig_wifi_reset_bssid_hotlist;
extern void shim_wifi_reset_bssid_hotlist(void);
void *wifishim_orig_wifi_set_significant_change_handler;
extern void shim_wifi_set_significant_change_handler(void);
void *wifishim_orig_wifi_reset_significant_change_handler;
extern void shim_wifi_reset_significant_change_handler(void);
void *wifishim_orig_wifi_get_gscan_capabilities;
extern void shim_wifi_get_gscan_capabilities(void);
void *wifishim_orig_wifi_set_link_stats;
extern void shim_wifi_set_link_stats(void);
void *wifishim_orig_wifi_get_link_stats;
extern void shim_wifi_get_link_stats(void);
void *wifishim_orig_wifi_clear_link_stats;
extern void shim_wifi_clear_link_stats(void);
void *wifishim_orig_wifi_get_valid_channels;
extern void shim_wifi_get_valid_channels(void);
void *wifishim_orig_wifi_rtt_range_request;
extern void shim_wifi_rtt_range_request(void);
void *wifishim_orig_wifi_rtt_range_cancel;
extern void shim_wifi_rtt_range_cancel(void);
void *wifishim_orig_wifi_get_rtt_capabilities;
extern void shim_wifi_get_rtt_capabilities(void);
void *wifishim_orig_wifi_rtt_get_responder_info;
extern void shim_wifi_rtt_get_responder_info(void);
void *wifishim_orig_wifi_enable_responder;
extern void shim_wifi_enable_responder(void);
void *wifishim_orig_wifi_disable_responder;
extern void shim_wifi_disable_responder(void);
void *wifishim_orig_wifi_set_nodfs_flag;
extern void shim_wifi_set_nodfs_flag(void);
void *wifishim_orig_wifi_start_logging;
extern void shim_wifi_start_logging(void);
void *wifishim_orig_wifi_set_epno_list;
extern void shim_wifi_set_epno_list(void);
void *wifishim_orig_wifi_reset_epno_list;
extern void shim_wifi_reset_epno_list(void);
void *wifishim_orig_wifi_set_country_code;
extern void shim_wifi_set_country_code(void);
void *wifishim_orig_wifi_get_firmware_memory_dump;
extern void shim_wifi_get_firmware_memory_dump(void);
void *wifishim_orig_wifi_set_log_handler;
extern void shim_wifi_set_log_handler(void);
void *wifishim_orig_wifi_reset_log_handler;
extern void shim_wifi_reset_log_handler(void);
void *wifishim_orig_wifi_set_alert_handler;
extern void shim_wifi_set_alert_handler(void);
void *wifishim_orig_wifi_reset_alert_handler;
extern void shim_wifi_reset_alert_handler(void);
void *wifishim_orig_wifi_get_firmware_version;
extern void shim_wifi_get_firmware_version(void);
void *wifishim_orig_wifi_get_ring_buffers_status;
extern void shim_wifi_get_ring_buffers_status(void);
void *wifishim_orig_wifi_get_logger_supported_feature_set;
extern void shim_wifi_get_logger_supported_feature_set(void);
void *wifishim_orig_wifi_get_ring_data;
extern void shim_wifi_get_ring_data(void);
void *wifishim_orig_wifi_enable_tdls;
extern void shim_wifi_enable_tdls(void);
void *wifishim_orig_wifi_disable_tdls;
extern void shim_wifi_disable_tdls(void);
void *wifishim_orig_wifi_get_tdls_status;
extern void shim_wifi_get_tdls_status(void);
void *wifishim_orig_wifi_get_tdls_capabilities;
extern void shim_wifi_get_tdls_capabilities(void);
void *wifishim_orig_wifi_get_driver_version;
extern void shim_wifi_get_driver_version(void);
void *wifishim_orig_wifi_set_passpoint_list;
extern void shim_wifi_set_passpoint_list(void);
void *wifishim_orig_wifi_reset_passpoint_list;
extern void shim_wifi_reset_passpoint_list(void);
void *wifishim_orig_wifi_set_lci;
extern void shim_wifi_set_lci(void);
void *wifishim_orig_wifi_set_lcr;
extern void shim_wifi_set_lcr(void);
void *wifishim_orig_wifi_start_sending_offloaded_packet;
extern void shim_wifi_start_sending_offloaded_packet(void);
void *wifishim_orig_wifi_stop_sending_offloaded_packet;
extern void shim_wifi_stop_sending_offloaded_packet(void);
void *wifishim_orig_wifi_start_rssi_monitoring;
extern void shim_wifi_start_rssi_monitoring(void);
void *wifishim_orig_wifi_stop_rssi_monitoring;
extern void shim_wifi_stop_rssi_monitoring(void);
void *wifishim_orig_wifi_get_wake_reason_stats;
extern void shim_wifi_get_wake_reason_stats(void);
void *wifishim_orig_wifi_configure_nd_offload;
extern void shim_wifi_configure_nd_offload(void);
void *wifishim_orig_wifi_get_driver_memory_dump;
extern void shim_wifi_get_driver_memory_dump(void);
void *wifishim_orig_wifi_start_pkt_fate_monitoring;
extern void shim_wifi_start_pkt_fate_monitoring(void);
void *wifishim_orig_wifi_get_tx_pkt_fates;
extern void shim_wifi_get_tx_pkt_fates(void);
void *wifishim_orig_wifi_get_rx_pkt_fates;
extern void shim_wifi_get_rx_pkt_fates(void);
void *wifishim_orig_wifi_nan_enable_request;
extern void shim_wifi_nan_enable_request(void);
void *wifishim_orig_wifi_nan_disable_request;
extern void shim_wifi_nan_disable_request(void);
void *wifishim_orig_wifi_nan_publish_request;
extern void shim_wifi_nan_publish_request(void);
void *wifishim_orig_wifi_nan_publish_cancel_request;
extern void shim_wifi_nan_publish_cancel_request(void);
void *wifishim_orig_wifi_nan_subscribe_request;
extern void shim_wifi_nan_subscribe_request(void);
void *wifishim_orig_wifi_nan_subscribe_cancel_request;
extern void shim_wifi_nan_subscribe_cancel_request(void);
void *wifishim_orig_wifi_nan_transmit_followup_request;
extern void shim_wifi_nan_transmit_followup_request(void);
void *wifishim_orig_wifi_nan_stats_request;
extern void shim_wifi_nan_stats_request(void);
void *wifishim_orig_wifi_nan_config_request;
extern void shim_wifi_nan_config_request(void);
void *wifishim_orig_wifi_nan_tca_request;
extern void shim_wifi_nan_tca_request(void);
void *wifishim_orig_wifi_nan_beacon_sdf_payload_request;
extern void shim_wifi_nan_beacon_sdf_payload_request(void);
void *wifishim_orig_wifi_nan_register_handler;
extern void shim_wifi_nan_register_handler(void);
void *wifishim_orig_wifi_nan_get_version;
extern void shim_wifi_nan_get_version(void);
void *wifishim_orig_wifi_nan_get_capabilities;
extern void shim_wifi_nan_get_capabilities(void);
void *wifishim_orig_wifi_nan_data_interface_create;
extern void shim_wifi_nan_data_interface_create(void);
void *wifishim_orig_wifi_nan_data_interface_delete;
extern void shim_wifi_nan_data_interface_delete(void);
void *wifishim_orig_wifi_nan_data_request_initiator;
extern void shim_wifi_nan_data_request_initiator(void);
void *wifishim_orig_wifi_nan_data_indication_response;
extern void shim_wifi_nan_data_indication_response(void);
void *wifishim_orig_wifi_nan_data_end;
extern void shim_wifi_nan_data_end(void);
void *wifishim_orig_wifi_select_tx_power_scenario;
extern void shim_wifi_select_tx_power_scenario(void);
void *wifishim_orig_wifi_reset_tx_power_scenario;
extern void shim_wifi_reset_tx_power_scenario(void);
void *wifishim_orig_wifi_get_packet_filter_capabilities;
extern void shim_wifi_get_packet_filter_capabilities(void);
void *wifishim_orig_wifi_set_packet_filter;
extern void shim_wifi_set_packet_filter(void);
void *wifishim_orig_wifi_read_packet_filter;
extern void shim_wifi_read_packet_filter(void);
void *wifishim_orig_wifi_get_roaming_capabilities;
extern void shim_wifi_get_roaming_capabilities(void);
void *wifishim_orig_wifi_enable_firmware_roaming;
extern void shim_wifi_enable_firmware_roaming(void);
void *wifishim_orig_wifi_configure_roaming;
extern void shim_wifi_configure_roaming(void);
void *wifishim_orig_wifi_set_radio_mode_change_handler;
extern void shim_wifi_set_radio_mode_change_handler(void);
void *wifishim_orig_wifi_set_latency_mode;
extern void shim_wifi_set_latency_mode(void);
void *wifishim_orig_wifi_set_thermal_mitigation_mode;
extern void shim_wifi_set_thermal_mitigation_mode(void);
void *wifishim_orig_wifi_map_dscp_access_category;
extern void shim_wifi_map_dscp_access_category(void);
void *wifishim_orig_wifi_reset_dscp_mapping;
extern void shim_wifi_reset_dscp_mapping(void);
void *wifishim_orig_wifi_virtual_interface_create;
extern void shim_wifi_virtual_interface_create(void);
void *wifishim_orig_wifi_virtual_interface_delete;
extern void shim_wifi_virtual_interface_delete(void);
void *wifishim_orig_wifi_set_subsystem_restart_handler;
extern void shim_wifi_set_subsystem_restart_handler(void);
void *wifishim_orig_wifi_get_supported_iface_name;
extern void shim_wifi_get_supported_iface_name(void);
void *wifishim_orig_wifi_get_chip_feature_set;
extern void shim_wifi_get_chip_feature_set(void);
void *wifishim_orig_wifi_multi_sta_set_primary_connection;
extern void shim_wifi_multi_sta_set_primary_connection(void);
void *wifishim_orig_wifi_multi_sta_set_use_case;
extern void shim_wifi_multi_sta_set_use_case(void);
void *wifishim_orig_wifi_set_coex_unsafe_channels;
extern void shim_wifi_set_coex_unsafe_channels(void);
void *wifishim_orig_wifi_set_voip_mode;
extern void shim_wifi_set_voip_mode(void);
void *wifishim_orig_wifi_twt_register_handler;
extern void shim_wifi_twt_register_handler(void);
void *wifishim_orig_wifi_twt_get_capability;
extern void shim_wifi_twt_get_capability(void);
void *wifishim_orig_wifi_twt_setup_request;
extern void shim_wifi_twt_setup_request(void);
void *wifishim_orig_wifi_twt_teardown_request;
extern void shim_wifi_twt_teardown_request(void);
void *wifishim_orig_wifi_twt_info_frame_request;
extern void shim_wifi_twt_info_frame_request(void);
void *wifishim_orig_wifi_twt_get_stats;
extern void shim_wifi_twt_get_stats(void);
void *wifishim_orig_wifi_twt_clear_stats;
extern void shim_wifi_twt_clear_stats(void);
void *wifishim_orig_wifi_set_dtim_config;
extern void shim_wifi_set_dtim_config(void);
void *wifishim_orig_wifi_get_usable_channels;
extern void shim_wifi_get_usable_channels(void);
void *wifishim_orig_wifi_trigger_subsystem_restart;
extern void shim_wifi_trigger_subsystem_restart(void);
void *wifishim_orig_wifi_cleanup;
extern void shim_wifi_cleanup(void);
void *wifishim_orig_wifi_event_loop;
extern void shim_wifi_event_loop(void);

wifi_error init_wifi_vendor_hal_func_table(wifi_hal_fn *fn) {
    void *h = dlopen(IMPL_LIB, RTLD_NOW | RTLD_LOCAL);
    if (!h) { ALOGE("wifishim: dlopen %s failed: %s", IMPL_LIB, dlerror()); return WIFI_ERROR_UNKNOWN; }
    init_fn_t init = (init_fn_t)dlsym(h, "init_wifi_vendor_hal_func_table");
    if (!init) { ALOGE("wifishim: init fn missing"); return WIFI_ERROR_UNKNOWN; }
    wifi_error ret = init(fn);
    if (ret != WIFI_SUCCESS || !fn) return ret;
    if (fn->wifi_get_supported_feature_set) {
        wifishim_orig_wifi_get_supported_feature_set = *(void **)&fn->wifi_get_supported_feature_set;
        fn->wifi_get_supported_feature_set = (__typeof__(fn->wifi_get_supported_feature_set))shim_wifi_get_supported_feature_set;
    }
    if (fn->wifi_get_concurrency_matrix) {
        wifishim_orig_wifi_get_concurrency_matrix = *(void **)&fn->wifi_get_concurrency_matrix;
        fn->wifi_get_concurrency_matrix = (__typeof__(fn->wifi_get_concurrency_matrix))shim_wifi_get_concurrency_matrix;
    }
    if (fn->wifi_set_scanning_mac_oui) {
        wifishim_orig_wifi_set_scanning_mac_oui = *(void **)&fn->wifi_set_scanning_mac_oui;
        fn->wifi_set_scanning_mac_oui = (__typeof__(fn->wifi_set_scanning_mac_oui))shim_wifi_set_scanning_mac_oui;
    }
    if (fn->wifi_get_supported_channels) {
        wifishim_orig_wifi_get_supported_channels = *(void **)&fn->wifi_get_supported_channels;
        fn->wifi_get_supported_channels = (__typeof__(fn->wifi_get_supported_channels))shim_wifi_get_supported_channels;
    }
    if (fn->wifi_is_epr_supported) {
        wifishim_orig_wifi_is_epr_supported = *(void **)&fn->wifi_is_epr_supported;
        fn->wifi_is_epr_supported = (__typeof__(fn->wifi_is_epr_supported))shim_wifi_is_epr_supported;
    }
    if (fn->wifi_get_ifaces) {
        wifishim_orig_wifi_get_ifaces = *(void **)&fn->wifi_get_ifaces;
        fn->wifi_get_ifaces = (__typeof__(fn->wifi_get_ifaces))shim_wifi_get_ifaces;
    }
    if (fn->wifi_get_iface_name) {
        wifishim_orig_wifi_get_iface_name = *(void **)&fn->wifi_get_iface_name;
        fn->wifi_get_iface_name = (__typeof__(fn->wifi_get_iface_name))shim_wifi_get_iface_name;
    }
    if (fn->wifi_set_iface_event_handler) {
        wifishim_orig_wifi_set_iface_event_handler = *(void **)&fn->wifi_set_iface_event_handler;
        fn->wifi_set_iface_event_handler = (__typeof__(fn->wifi_set_iface_event_handler))shim_wifi_set_iface_event_handler;
    }
    if (fn->wifi_reset_iface_event_handler) {
        wifishim_orig_wifi_reset_iface_event_handler = *(void **)&fn->wifi_reset_iface_event_handler;
        fn->wifi_reset_iface_event_handler = (__typeof__(fn->wifi_reset_iface_event_handler))shim_wifi_reset_iface_event_handler;
    }
    if (fn->wifi_start_gscan) {
        wifishim_orig_wifi_start_gscan = *(void **)&fn->wifi_start_gscan;
        fn->wifi_start_gscan = (__typeof__(fn->wifi_start_gscan))shim_wifi_start_gscan;
    }
    if (fn->wifi_stop_gscan) {
        wifishim_orig_wifi_stop_gscan = *(void **)&fn->wifi_stop_gscan;
        fn->wifi_stop_gscan = (__typeof__(fn->wifi_stop_gscan))shim_wifi_stop_gscan;
    }
    if (fn->wifi_get_cached_gscan_results) {
        wifishim_orig_wifi_get_cached_gscan_results = *(void **)&fn->wifi_get_cached_gscan_results;
        fn->wifi_get_cached_gscan_results = (__typeof__(fn->wifi_get_cached_gscan_results))shim_wifi_get_cached_gscan_results;
    }
    if (fn->wifi_set_bssid_hotlist) {
        wifishim_orig_wifi_set_bssid_hotlist = *(void **)&fn->wifi_set_bssid_hotlist;
        fn->wifi_set_bssid_hotlist = (__typeof__(fn->wifi_set_bssid_hotlist))shim_wifi_set_bssid_hotlist;
    }
    if (fn->wifi_reset_bssid_hotlist) {
        wifishim_orig_wifi_reset_bssid_hotlist = *(void **)&fn->wifi_reset_bssid_hotlist;
        fn->wifi_reset_bssid_hotlist = (__typeof__(fn->wifi_reset_bssid_hotlist))shim_wifi_reset_bssid_hotlist;
    }
    if (fn->wifi_set_significant_change_handler) {
        wifishim_orig_wifi_set_significant_change_handler = *(void **)&fn->wifi_set_significant_change_handler;
        fn->wifi_set_significant_change_handler = (__typeof__(fn->wifi_set_significant_change_handler))shim_wifi_set_significant_change_handler;
    }
    if (fn->wifi_reset_significant_change_handler) {
        wifishim_orig_wifi_reset_significant_change_handler = *(void **)&fn->wifi_reset_significant_change_handler;
        fn->wifi_reset_significant_change_handler = (__typeof__(fn->wifi_reset_significant_change_handler))shim_wifi_reset_significant_change_handler;
    }
    if (fn->wifi_get_gscan_capabilities) {
        wifishim_orig_wifi_get_gscan_capabilities = *(void **)&fn->wifi_get_gscan_capabilities;
        fn->wifi_get_gscan_capabilities = (__typeof__(fn->wifi_get_gscan_capabilities))shim_wifi_get_gscan_capabilities;
    }
    if (fn->wifi_set_link_stats) {
        wifishim_orig_wifi_set_link_stats = *(void **)&fn->wifi_set_link_stats;
        fn->wifi_set_link_stats = (__typeof__(fn->wifi_set_link_stats))shim_wifi_set_link_stats;
    }
    if (fn->wifi_get_link_stats) {
        wifishim_orig_wifi_get_link_stats = *(void **)&fn->wifi_get_link_stats;
        fn->wifi_get_link_stats = (__typeof__(fn->wifi_get_link_stats))shim_wifi_get_link_stats;
    }
    if (fn->wifi_clear_link_stats) {
        wifishim_orig_wifi_clear_link_stats = *(void **)&fn->wifi_clear_link_stats;
        fn->wifi_clear_link_stats = (__typeof__(fn->wifi_clear_link_stats))shim_wifi_clear_link_stats;
    }
    if (fn->wifi_get_valid_channels) {
        wifishim_orig_wifi_get_valid_channels = *(void **)&fn->wifi_get_valid_channels;
        fn->wifi_get_valid_channels = (__typeof__(fn->wifi_get_valid_channels))shim_wifi_get_valid_channels;
    }
    if (fn->wifi_rtt_range_request) {
        wifishim_orig_wifi_rtt_range_request = *(void **)&fn->wifi_rtt_range_request;
        fn->wifi_rtt_range_request = (__typeof__(fn->wifi_rtt_range_request))shim_wifi_rtt_range_request;
    }
    if (fn->wifi_rtt_range_cancel) {
        wifishim_orig_wifi_rtt_range_cancel = *(void **)&fn->wifi_rtt_range_cancel;
        fn->wifi_rtt_range_cancel = (__typeof__(fn->wifi_rtt_range_cancel))shim_wifi_rtt_range_cancel;
    }
    if (fn->wifi_get_rtt_capabilities) {
        wifishim_orig_wifi_get_rtt_capabilities = *(void **)&fn->wifi_get_rtt_capabilities;
        fn->wifi_get_rtt_capabilities = (__typeof__(fn->wifi_get_rtt_capabilities))shim_wifi_get_rtt_capabilities;
    }
    if (fn->wifi_rtt_get_responder_info) {
        wifishim_orig_wifi_rtt_get_responder_info = *(void **)&fn->wifi_rtt_get_responder_info;
        fn->wifi_rtt_get_responder_info = (__typeof__(fn->wifi_rtt_get_responder_info))shim_wifi_rtt_get_responder_info;
    }
    if (fn->wifi_enable_responder) {
        wifishim_orig_wifi_enable_responder = *(void **)&fn->wifi_enable_responder;
        fn->wifi_enable_responder = (__typeof__(fn->wifi_enable_responder))shim_wifi_enable_responder;
    }
    if (fn->wifi_disable_responder) {
        wifishim_orig_wifi_disable_responder = *(void **)&fn->wifi_disable_responder;
        fn->wifi_disable_responder = (__typeof__(fn->wifi_disable_responder))shim_wifi_disable_responder;
    }
    if (fn->wifi_set_nodfs_flag) {
        wifishim_orig_wifi_set_nodfs_flag = *(void **)&fn->wifi_set_nodfs_flag;
        fn->wifi_set_nodfs_flag = (__typeof__(fn->wifi_set_nodfs_flag))shim_wifi_set_nodfs_flag;
    }
    if (fn->wifi_start_logging) {
        wifishim_orig_wifi_start_logging = *(void **)&fn->wifi_start_logging;
        fn->wifi_start_logging = (__typeof__(fn->wifi_start_logging))shim_wifi_start_logging;
    }
    if (fn->wifi_set_epno_list) {
        wifishim_orig_wifi_set_epno_list = *(void **)&fn->wifi_set_epno_list;
        fn->wifi_set_epno_list = (__typeof__(fn->wifi_set_epno_list))shim_wifi_set_epno_list;
    }
    if (fn->wifi_reset_epno_list) {
        wifishim_orig_wifi_reset_epno_list = *(void **)&fn->wifi_reset_epno_list;
        fn->wifi_reset_epno_list = (__typeof__(fn->wifi_reset_epno_list))shim_wifi_reset_epno_list;
    }
    if (fn->wifi_set_country_code) {
        wifishim_orig_wifi_set_country_code = *(void **)&fn->wifi_set_country_code;
        fn->wifi_set_country_code = (__typeof__(fn->wifi_set_country_code))shim_wifi_set_country_code;
    }
    if (fn->wifi_get_firmware_memory_dump) {
        wifishim_orig_wifi_get_firmware_memory_dump = *(void **)&fn->wifi_get_firmware_memory_dump;
        fn->wifi_get_firmware_memory_dump = (__typeof__(fn->wifi_get_firmware_memory_dump))shim_wifi_get_firmware_memory_dump;
    }
    if (fn->wifi_set_log_handler) {
        wifishim_orig_wifi_set_log_handler = *(void **)&fn->wifi_set_log_handler;
        fn->wifi_set_log_handler = (__typeof__(fn->wifi_set_log_handler))shim_wifi_set_log_handler;
    }
    if (fn->wifi_reset_log_handler) {
        wifishim_orig_wifi_reset_log_handler = *(void **)&fn->wifi_reset_log_handler;
        fn->wifi_reset_log_handler = (__typeof__(fn->wifi_reset_log_handler))shim_wifi_reset_log_handler;
    }
    if (fn->wifi_set_alert_handler) {
        wifishim_orig_wifi_set_alert_handler = *(void **)&fn->wifi_set_alert_handler;
        fn->wifi_set_alert_handler = (__typeof__(fn->wifi_set_alert_handler))shim_wifi_set_alert_handler;
    }
    if (fn->wifi_reset_alert_handler) {
        wifishim_orig_wifi_reset_alert_handler = *(void **)&fn->wifi_reset_alert_handler;
        fn->wifi_reset_alert_handler = (__typeof__(fn->wifi_reset_alert_handler))shim_wifi_reset_alert_handler;
    }
    if (fn->wifi_get_firmware_version) {
        wifishim_orig_wifi_get_firmware_version = *(void **)&fn->wifi_get_firmware_version;
        fn->wifi_get_firmware_version = (__typeof__(fn->wifi_get_firmware_version))shim_wifi_get_firmware_version;
    }
    if (fn->wifi_get_ring_buffers_status) {
        wifishim_orig_wifi_get_ring_buffers_status = *(void **)&fn->wifi_get_ring_buffers_status;
        fn->wifi_get_ring_buffers_status = (__typeof__(fn->wifi_get_ring_buffers_status))shim_wifi_get_ring_buffers_status;
    }
    if (fn->wifi_get_logger_supported_feature_set) {
        wifishim_orig_wifi_get_logger_supported_feature_set = *(void **)&fn->wifi_get_logger_supported_feature_set;
        fn->wifi_get_logger_supported_feature_set = (__typeof__(fn->wifi_get_logger_supported_feature_set))shim_wifi_get_logger_supported_feature_set;
    }
    if (fn->wifi_get_ring_data) {
        wifishim_orig_wifi_get_ring_data = *(void **)&fn->wifi_get_ring_data;
        fn->wifi_get_ring_data = (__typeof__(fn->wifi_get_ring_data))shim_wifi_get_ring_data;
    }
    if (fn->wifi_enable_tdls) {
        wifishim_orig_wifi_enable_tdls = *(void **)&fn->wifi_enable_tdls;
        fn->wifi_enable_tdls = (__typeof__(fn->wifi_enable_tdls))shim_wifi_enable_tdls;
    }
    if (fn->wifi_disable_tdls) {
        wifishim_orig_wifi_disable_tdls = *(void **)&fn->wifi_disable_tdls;
        fn->wifi_disable_tdls = (__typeof__(fn->wifi_disable_tdls))shim_wifi_disable_tdls;
    }
    if (fn->wifi_get_tdls_status) {
        wifishim_orig_wifi_get_tdls_status = *(void **)&fn->wifi_get_tdls_status;
        fn->wifi_get_tdls_status = (__typeof__(fn->wifi_get_tdls_status))shim_wifi_get_tdls_status;
    }
    if (fn->wifi_get_tdls_capabilities) {
        wifishim_orig_wifi_get_tdls_capabilities = *(void **)&fn->wifi_get_tdls_capabilities;
        fn->wifi_get_tdls_capabilities = (__typeof__(fn->wifi_get_tdls_capabilities))shim_wifi_get_tdls_capabilities;
    }
    if (fn->wifi_get_driver_version) {
        wifishim_orig_wifi_get_driver_version = *(void **)&fn->wifi_get_driver_version;
        fn->wifi_get_driver_version = (__typeof__(fn->wifi_get_driver_version))shim_wifi_get_driver_version;
    }
    if (fn->wifi_set_passpoint_list) {
        wifishim_orig_wifi_set_passpoint_list = *(void **)&fn->wifi_set_passpoint_list;
        fn->wifi_set_passpoint_list = (__typeof__(fn->wifi_set_passpoint_list))shim_wifi_set_passpoint_list;
    }
    if (fn->wifi_reset_passpoint_list) {
        wifishim_orig_wifi_reset_passpoint_list = *(void **)&fn->wifi_reset_passpoint_list;
        fn->wifi_reset_passpoint_list = (__typeof__(fn->wifi_reset_passpoint_list))shim_wifi_reset_passpoint_list;
    }
    if (fn->wifi_set_lci) {
        wifishim_orig_wifi_set_lci = *(void **)&fn->wifi_set_lci;
        fn->wifi_set_lci = (__typeof__(fn->wifi_set_lci))shim_wifi_set_lci;
    }
    if (fn->wifi_set_lcr) {
        wifishim_orig_wifi_set_lcr = *(void **)&fn->wifi_set_lcr;
        fn->wifi_set_lcr = (__typeof__(fn->wifi_set_lcr))shim_wifi_set_lcr;
    }
    if (fn->wifi_start_sending_offloaded_packet) {
        wifishim_orig_wifi_start_sending_offloaded_packet = *(void **)&fn->wifi_start_sending_offloaded_packet;
        fn->wifi_start_sending_offloaded_packet = (__typeof__(fn->wifi_start_sending_offloaded_packet))shim_wifi_start_sending_offloaded_packet;
    }
    if (fn->wifi_stop_sending_offloaded_packet) {
        wifishim_orig_wifi_stop_sending_offloaded_packet = *(void **)&fn->wifi_stop_sending_offloaded_packet;
        fn->wifi_stop_sending_offloaded_packet = (__typeof__(fn->wifi_stop_sending_offloaded_packet))shim_wifi_stop_sending_offloaded_packet;
    }
    if (fn->wifi_start_rssi_monitoring) {
        wifishim_orig_wifi_start_rssi_monitoring = *(void **)&fn->wifi_start_rssi_monitoring;
        fn->wifi_start_rssi_monitoring = (__typeof__(fn->wifi_start_rssi_monitoring))shim_wifi_start_rssi_monitoring;
    }
    if (fn->wifi_stop_rssi_monitoring) {
        wifishim_orig_wifi_stop_rssi_monitoring = *(void **)&fn->wifi_stop_rssi_monitoring;
        fn->wifi_stop_rssi_monitoring = (__typeof__(fn->wifi_stop_rssi_monitoring))shim_wifi_stop_rssi_monitoring;
    }
    if (fn->wifi_get_wake_reason_stats) {
        wifishim_orig_wifi_get_wake_reason_stats = *(void **)&fn->wifi_get_wake_reason_stats;
        fn->wifi_get_wake_reason_stats = (__typeof__(fn->wifi_get_wake_reason_stats))shim_wifi_get_wake_reason_stats;
    }
    if (fn->wifi_configure_nd_offload) {
        wifishim_orig_wifi_configure_nd_offload = *(void **)&fn->wifi_configure_nd_offload;
        fn->wifi_configure_nd_offload = (__typeof__(fn->wifi_configure_nd_offload))shim_wifi_configure_nd_offload;
    }
    if (fn->wifi_get_driver_memory_dump) {
        wifishim_orig_wifi_get_driver_memory_dump = *(void **)&fn->wifi_get_driver_memory_dump;
        fn->wifi_get_driver_memory_dump = (__typeof__(fn->wifi_get_driver_memory_dump))shim_wifi_get_driver_memory_dump;
    }
    if (fn->wifi_start_pkt_fate_monitoring) {
        wifishim_orig_wifi_start_pkt_fate_monitoring = *(void **)&fn->wifi_start_pkt_fate_monitoring;
        fn->wifi_start_pkt_fate_monitoring = (__typeof__(fn->wifi_start_pkt_fate_monitoring))shim_wifi_start_pkt_fate_monitoring;
    }
    if (fn->wifi_get_tx_pkt_fates) {
        wifishim_orig_wifi_get_tx_pkt_fates = *(void **)&fn->wifi_get_tx_pkt_fates;
        fn->wifi_get_tx_pkt_fates = (__typeof__(fn->wifi_get_tx_pkt_fates))shim_wifi_get_tx_pkt_fates;
    }
    if (fn->wifi_get_rx_pkt_fates) {
        wifishim_orig_wifi_get_rx_pkt_fates = *(void **)&fn->wifi_get_rx_pkt_fates;
        fn->wifi_get_rx_pkt_fates = (__typeof__(fn->wifi_get_rx_pkt_fates))shim_wifi_get_rx_pkt_fates;
    }
    if (fn->wifi_nan_enable_request) {
        wifishim_orig_wifi_nan_enable_request = *(void **)&fn->wifi_nan_enable_request;
        fn->wifi_nan_enable_request = (__typeof__(fn->wifi_nan_enable_request))shim_wifi_nan_enable_request;
    }
    if (fn->wifi_nan_disable_request) {
        wifishim_orig_wifi_nan_disable_request = *(void **)&fn->wifi_nan_disable_request;
        fn->wifi_nan_disable_request = (__typeof__(fn->wifi_nan_disable_request))shim_wifi_nan_disable_request;
    }
    if (fn->wifi_nan_publish_request) {
        wifishim_orig_wifi_nan_publish_request = *(void **)&fn->wifi_nan_publish_request;
        fn->wifi_nan_publish_request = (__typeof__(fn->wifi_nan_publish_request))shim_wifi_nan_publish_request;
    }
    if (fn->wifi_nan_publish_cancel_request) {
        wifishim_orig_wifi_nan_publish_cancel_request = *(void **)&fn->wifi_nan_publish_cancel_request;
        fn->wifi_nan_publish_cancel_request = (__typeof__(fn->wifi_nan_publish_cancel_request))shim_wifi_nan_publish_cancel_request;
    }
    if (fn->wifi_nan_subscribe_request) {
        wifishim_orig_wifi_nan_subscribe_request = *(void **)&fn->wifi_nan_subscribe_request;
        fn->wifi_nan_subscribe_request = (__typeof__(fn->wifi_nan_subscribe_request))shim_wifi_nan_subscribe_request;
    }
    if (fn->wifi_nan_subscribe_cancel_request) {
        wifishim_orig_wifi_nan_subscribe_cancel_request = *(void **)&fn->wifi_nan_subscribe_cancel_request;
        fn->wifi_nan_subscribe_cancel_request = (__typeof__(fn->wifi_nan_subscribe_cancel_request))shim_wifi_nan_subscribe_cancel_request;
    }
    if (fn->wifi_nan_transmit_followup_request) {
        wifishim_orig_wifi_nan_transmit_followup_request = *(void **)&fn->wifi_nan_transmit_followup_request;
        fn->wifi_nan_transmit_followup_request = (__typeof__(fn->wifi_nan_transmit_followup_request))shim_wifi_nan_transmit_followup_request;
    }
    if (fn->wifi_nan_stats_request) {
        wifishim_orig_wifi_nan_stats_request = *(void **)&fn->wifi_nan_stats_request;
        fn->wifi_nan_stats_request = (__typeof__(fn->wifi_nan_stats_request))shim_wifi_nan_stats_request;
    }
    if (fn->wifi_nan_config_request) {
        wifishim_orig_wifi_nan_config_request = *(void **)&fn->wifi_nan_config_request;
        fn->wifi_nan_config_request = (__typeof__(fn->wifi_nan_config_request))shim_wifi_nan_config_request;
    }
    if (fn->wifi_nan_tca_request) {
        wifishim_orig_wifi_nan_tca_request = *(void **)&fn->wifi_nan_tca_request;
        fn->wifi_nan_tca_request = (__typeof__(fn->wifi_nan_tca_request))shim_wifi_nan_tca_request;
    }
    if (fn->wifi_nan_beacon_sdf_payload_request) {
        wifishim_orig_wifi_nan_beacon_sdf_payload_request = *(void **)&fn->wifi_nan_beacon_sdf_payload_request;
        fn->wifi_nan_beacon_sdf_payload_request = (__typeof__(fn->wifi_nan_beacon_sdf_payload_request))shim_wifi_nan_beacon_sdf_payload_request;
    }
    if (fn->wifi_nan_register_handler) {
        wifishim_orig_wifi_nan_register_handler = *(void **)&fn->wifi_nan_register_handler;
        fn->wifi_nan_register_handler = (__typeof__(fn->wifi_nan_register_handler))shim_wifi_nan_register_handler;
    }
    if (fn->wifi_nan_get_version) {
        wifishim_orig_wifi_nan_get_version = *(void **)&fn->wifi_nan_get_version;
        fn->wifi_nan_get_version = (__typeof__(fn->wifi_nan_get_version))shim_wifi_nan_get_version;
    }
    if (fn->wifi_nan_get_capabilities) {
        wifishim_orig_wifi_nan_get_capabilities = *(void **)&fn->wifi_nan_get_capabilities;
        fn->wifi_nan_get_capabilities = (__typeof__(fn->wifi_nan_get_capabilities))shim_wifi_nan_get_capabilities;
    }
    if (fn->wifi_nan_data_interface_create) {
        wifishim_orig_wifi_nan_data_interface_create = *(void **)&fn->wifi_nan_data_interface_create;
        fn->wifi_nan_data_interface_create = (__typeof__(fn->wifi_nan_data_interface_create))shim_wifi_nan_data_interface_create;
    }
    if (fn->wifi_nan_data_interface_delete) {
        wifishim_orig_wifi_nan_data_interface_delete = *(void **)&fn->wifi_nan_data_interface_delete;
        fn->wifi_nan_data_interface_delete = (__typeof__(fn->wifi_nan_data_interface_delete))shim_wifi_nan_data_interface_delete;
    }
    if (fn->wifi_nan_data_request_initiator) {
        wifishim_orig_wifi_nan_data_request_initiator = *(void **)&fn->wifi_nan_data_request_initiator;
        fn->wifi_nan_data_request_initiator = (__typeof__(fn->wifi_nan_data_request_initiator))shim_wifi_nan_data_request_initiator;
    }
    if (fn->wifi_nan_data_indication_response) {
        wifishim_orig_wifi_nan_data_indication_response = *(void **)&fn->wifi_nan_data_indication_response;
        fn->wifi_nan_data_indication_response = (__typeof__(fn->wifi_nan_data_indication_response))shim_wifi_nan_data_indication_response;
    }
    if (fn->wifi_nan_data_end) {
        wifishim_orig_wifi_nan_data_end = *(void **)&fn->wifi_nan_data_end;
        fn->wifi_nan_data_end = (__typeof__(fn->wifi_nan_data_end))shim_wifi_nan_data_end;
    }
    if (fn->wifi_select_tx_power_scenario) {
        wifishim_orig_wifi_select_tx_power_scenario = *(void **)&fn->wifi_select_tx_power_scenario;
        fn->wifi_select_tx_power_scenario = (__typeof__(fn->wifi_select_tx_power_scenario))shim_wifi_select_tx_power_scenario;
    }
    if (fn->wifi_reset_tx_power_scenario) {
        wifishim_orig_wifi_reset_tx_power_scenario = *(void **)&fn->wifi_reset_tx_power_scenario;
        fn->wifi_reset_tx_power_scenario = (__typeof__(fn->wifi_reset_tx_power_scenario))shim_wifi_reset_tx_power_scenario;
    }
    if (fn->wifi_get_packet_filter_capabilities) {
        wifishim_orig_wifi_get_packet_filter_capabilities = *(void **)&fn->wifi_get_packet_filter_capabilities;
        fn->wifi_get_packet_filter_capabilities = (__typeof__(fn->wifi_get_packet_filter_capabilities))shim_wifi_get_packet_filter_capabilities;
    }
    if (fn->wifi_set_packet_filter) {
        wifishim_orig_wifi_set_packet_filter = *(void **)&fn->wifi_set_packet_filter;
        fn->wifi_set_packet_filter = (__typeof__(fn->wifi_set_packet_filter))shim_wifi_set_packet_filter;
    }
    if (fn->wifi_read_packet_filter) {
        wifishim_orig_wifi_read_packet_filter = *(void **)&fn->wifi_read_packet_filter;
        fn->wifi_read_packet_filter = (__typeof__(fn->wifi_read_packet_filter))shim_wifi_read_packet_filter;
    }
    if (fn->wifi_get_roaming_capabilities) {
        wifishim_orig_wifi_get_roaming_capabilities = *(void **)&fn->wifi_get_roaming_capabilities;
        fn->wifi_get_roaming_capabilities = (__typeof__(fn->wifi_get_roaming_capabilities))shim_wifi_get_roaming_capabilities;
    }
    if (fn->wifi_enable_firmware_roaming) {
        wifishim_orig_wifi_enable_firmware_roaming = *(void **)&fn->wifi_enable_firmware_roaming;
        fn->wifi_enable_firmware_roaming = (__typeof__(fn->wifi_enable_firmware_roaming))shim_wifi_enable_firmware_roaming;
    }
    if (fn->wifi_configure_roaming) {
        wifishim_orig_wifi_configure_roaming = *(void **)&fn->wifi_configure_roaming;
        fn->wifi_configure_roaming = (__typeof__(fn->wifi_configure_roaming))shim_wifi_configure_roaming;
    }
    if (fn->wifi_set_radio_mode_change_handler) {
        wifishim_orig_wifi_set_radio_mode_change_handler = *(void **)&fn->wifi_set_radio_mode_change_handler;
        fn->wifi_set_radio_mode_change_handler = (__typeof__(fn->wifi_set_radio_mode_change_handler))shim_wifi_set_radio_mode_change_handler;
    }
    if (fn->wifi_set_latency_mode) {
        wifishim_orig_wifi_set_latency_mode = *(void **)&fn->wifi_set_latency_mode;
        fn->wifi_set_latency_mode = (__typeof__(fn->wifi_set_latency_mode))shim_wifi_set_latency_mode;
    }
    if (fn->wifi_set_thermal_mitigation_mode) {
        wifishim_orig_wifi_set_thermal_mitigation_mode = *(void **)&fn->wifi_set_thermal_mitigation_mode;
        fn->wifi_set_thermal_mitigation_mode = (__typeof__(fn->wifi_set_thermal_mitigation_mode))shim_wifi_set_thermal_mitigation_mode;
    }
    if (fn->wifi_map_dscp_access_category) {
        wifishim_orig_wifi_map_dscp_access_category = *(void **)&fn->wifi_map_dscp_access_category;
        fn->wifi_map_dscp_access_category = (__typeof__(fn->wifi_map_dscp_access_category))shim_wifi_map_dscp_access_category;
    }
    if (fn->wifi_reset_dscp_mapping) {
        wifishim_orig_wifi_reset_dscp_mapping = *(void **)&fn->wifi_reset_dscp_mapping;
        fn->wifi_reset_dscp_mapping = (__typeof__(fn->wifi_reset_dscp_mapping))shim_wifi_reset_dscp_mapping;
    }
    if (fn->wifi_virtual_interface_create) {
        wifishim_orig_wifi_virtual_interface_create = *(void **)&fn->wifi_virtual_interface_create;
        fn->wifi_virtual_interface_create = (__typeof__(fn->wifi_virtual_interface_create))shim_wifi_virtual_interface_create;
    }
    if (fn->wifi_virtual_interface_delete) {
        wifishim_orig_wifi_virtual_interface_delete = *(void **)&fn->wifi_virtual_interface_delete;
        fn->wifi_virtual_interface_delete = (__typeof__(fn->wifi_virtual_interface_delete))shim_wifi_virtual_interface_delete;
    }
    if (fn->wifi_set_subsystem_restart_handler) {
        wifishim_orig_wifi_set_subsystem_restart_handler = *(void **)&fn->wifi_set_subsystem_restart_handler;
        fn->wifi_set_subsystem_restart_handler = (__typeof__(fn->wifi_set_subsystem_restart_handler))shim_wifi_set_subsystem_restart_handler;
    }
    if (fn->wifi_get_supported_iface_name) {
        wifishim_orig_wifi_get_supported_iface_name = *(void **)&fn->wifi_get_supported_iface_name;
        fn->wifi_get_supported_iface_name = (__typeof__(fn->wifi_get_supported_iface_name))shim_wifi_get_supported_iface_name;
    }
    if (fn->wifi_get_chip_feature_set) {
        wifishim_orig_wifi_get_chip_feature_set = *(void **)&fn->wifi_get_chip_feature_set;
        fn->wifi_get_chip_feature_set = (__typeof__(fn->wifi_get_chip_feature_set))shim_wifi_get_chip_feature_set;
    }
    if (fn->wifi_multi_sta_set_primary_connection) {
        wifishim_orig_wifi_multi_sta_set_primary_connection = *(void **)&fn->wifi_multi_sta_set_primary_connection;
        fn->wifi_multi_sta_set_primary_connection = (__typeof__(fn->wifi_multi_sta_set_primary_connection))shim_wifi_multi_sta_set_primary_connection;
    }
    if (fn->wifi_multi_sta_set_use_case) {
        wifishim_orig_wifi_multi_sta_set_use_case = *(void **)&fn->wifi_multi_sta_set_use_case;
        fn->wifi_multi_sta_set_use_case = (__typeof__(fn->wifi_multi_sta_set_use_case))shim_wifi_multi_sta_set_use_case;
    }
    if (fn->wifi_set_coex_unsafe_channels) {
        wifishim_orig_wifi_set_coex_unsafe_channels = *(void **)&fn->wifi_set_coex_unsafe_channels;
        fn->wifi_set_coex_unsafe_channels = (__typeof__(fn->wifi_set_coex_unsafe_channels))shim_wifi_set_coex_unsafe_channels;
    }
    if (fn->wifi_set_voip_mode) {
        wifishim_orig_wifi_set_voip_mode = *(void **)&fn->wifi_set_voip_mode;
        fn->wifi_set_voip_mode = (__typeof__(fn->wifi_set_voip_mode))shim_wifi_set_voip_mode;
    }
    if (fn->wifi_twt_register_handler) {
        wifishim_orig_wifi_twt_register_handler = *(void **)&fn->wifi_twt_register_handler;
        fn->wifi_twt_register_handler = (__typeof__(fn->wifi_twt_register_handler))shim_wifi_twt_register_handler;
    }
    if (fn->wifi_twt_get_capability) {
        wifishim_orig_wifi_twt_get_capability = *(void **)&fn->wifi_twt_get_capability;
        fn->wifi_twt_get_capability = (__typeof__(fn->wifi_twt_get_capability))shim_wifi_twt_get_capability;
    }
    if (fn->wifi_twt_setup_request) {
        wifishim_orig_wifi_twt_setup_request = *(void **)&fn->wifi_twt_setup_request;
        fn->wifi_twt_setup_request = (__typeof__(fn->wifi_twt_setup_request))shim_wifi_twt_setup_request;
    }
    if (fn->wifi_twt_teardown_request) {
        wifishim_orig_wifi_twt_teardown_request = *(void **)&fn->wifi_twt_teardown_request;
        fn->wifi_twt_teardown_request = (__typeof__(fn->wifi_twt_teardown_request))shim_wifi_twt_teardown_request;
    }
    if (fn->wifi_twt_info_frame_request) {
        wifishim_orig_wifi_twt_info_frame_request = *(void **)&fn->wifi_twt_info_frame_request;
        fn->wifi_twt_info_frame_request = (__typeof__(fn->wifi_twt_info_frame_request))shim_wifi_twt_info_frame_request;
    }
    if (fn->wifi_twt_get_stats) {
        wifishim_orig_wifi_twt_get_stats = *(void **)&fn->wifi_twt_get_stats;
        fn->wifi_twt_get_stats = (__typeof__(fn->wifi_twt_get_stats))shim_wifi_twt_get_stats;
    }
    if (fn->wifi_twt_clear_stats) {
        wifishim_orig_wifi_twt_clear_stats = *(void **)&fn->wifi_twt_clear_stats;
        fn->wifi_twt_clear_stats = (__typeof__(fn->wifi_twt_clear_stats))shim_wifi_twt_clear_stats;
    }
    if (fn->wifi_set_dtim_config) {
        wifishim_orig_wifi_set_dtim_config = *(void **)&fn->wifi_set_dtim_config;
        fn->wifi_set_dtim_config = (__typeof__(fn->wifi_set_dtim_config))shim_wifi_set_dtim_config;
    }
    if (fn->wifi_get_usable_channels) {
        wifishim_orig_wifi_get_usable_channels = *(void **)&fn->wifi_get_usable_channels;
        fn->wifi_get_usable_channels = (__typeof__(fn->wifi_get_usable_channels))shim_wifi_get_usable_channels;
    }
    if (fn->wifi_trigger_subsystem_restart) {
        wifishim_orig_wifi_trigger_subsystem_restart = *(void **)&fn->wifi_trigger_subsystem_restart;
        fn->wifi_trigger_subsystem_restart = (__typeof__(fn->wifi_trigger_subsystem_restart))shim_wifi_trigger_subsystem_restart;
    }
    if (fn->wifi_cleanup) {
        wifishim_orig_wifi_cleanup = *(void **)&fn->wifi_cleanup;
        fn->wifi_cleanup = (__typeof__(fn->wifi_cleanup))shim_wifi_cleanup;
    }
    if (fn->wifi_event_loop) {
        wifishim_orig_wifi_event_loop = *(void **)&fn->wifi_event_loop;
        fn->wifi_event_loop = (__typeof__(fn->wifi_event_loop))shim_wifi_event_loop;
    }
    return WIFI_SUCCESS;
}
