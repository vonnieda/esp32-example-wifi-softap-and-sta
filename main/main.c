#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_system.h"

#include "esp_wifi.h"
#include "nvs_flash.h"

static const char *TAG = "wifi-softap+sta";

static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data) {
    switch (event_id) {
        case WIFI_EVENT_STA_START:
            esp_wifi_connect();
            break;
        case WIFI_EVENT_STA_DISCONNECTED:
            esp_wifi_connect();
            break;
    }
}

static void ip_event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data) {
    switch (event_id) {
        case IP_EVENT_STA_GOT_IP: {
            ip_event_got_ip_t* event = event_data;
            ESP_LOGI(TAG, "Station connected with IP: "IPSTR", GW: "IPSTR", Mask: "IPSTR".",
                IP2STR(&event->ip_info.ip),
                IP2STR(&event->ip_info.gw),
                IP2STR(&event->ip_info.netmask));
            break;
        }
        case IP_EVENT_AP_STAIPASSIGNED: {
            ip_event_ap_staipassigned_t* event = event_data;
            ESP_LOGI(TAG, "SoftAP client connected with IP: "IPSTR".",
                IP2STR(&event->ip));
            break;
        }
    }
}

void app_main(void) {
    // NVS: Required by WiFi Driver
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // TCP/IP
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    // WiFi Interfaces (AP + STA) 
    esp_netif_create_default_wifi_ap();
    esp_netif_create_default_wifi_sta();

    // WiFi Driver
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    // Event Handlers
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
        ESP_EVENT_ANY_ID,
        &wifi_event_handler,
        NULL,
        NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
        ESP_EVENT_ANY_ID,
        &ip_event_handler,
        NULL,
        NULL));

    // WiFi Mode AP + STA
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));

    // WiFi STA Config (Minimum)
    wifi_config_t wifi_sta_config = {
        .sta = {
            .ssid = CONFIG_ESP_WIFI_STA_SSID,
            .password = CONFIG_ESP_WIFI_STA_PASSWORD,
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_sta_config));

    // WiFi API Config (Minimum)
    wifi_config_t wifi_ap_config = {
        .ap = {
            .ssid = CONFIG_ESP_WIFI_AP_SSID,
            .password = CONFIG_ESP_WIFI_AP_PASSWORD,
            .authmode = WIFI_AUTH_WPA2_PSK,
            .max_connection = 4,
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_ap_config));

    // Start the stack and events will do the rest.
    ESP_ERROR_CHECK(esp_wifi_start());
}

