#ifndef WIFI_H_INCLUDED
#define WIFI_H_INCLUDED

#include <Arduino.h>
#include <IPAddress.h>
#include <WiFiType.h>


typedef enum
{
    WIFI_AUTH_OPEN = 0,         /**< authenticate mode : open */
    WIFI_AUTH_WEP,              /**< authenticate mode : WEP */
    WIFI_AUTH_WPA_PSK,          /**< authenticate mode : WPA_PSK */
    WIFI_AUTH_WPA2_PSK,         /**< authenticate mode : WPA2_PSK */
    WIFI_AUTH_WPA_WPA2_PSK,     /**< authenticate mode : WPA_WPA2_PSK */
    WIFI_AUTH_WPA2_ENTERPRISE,  /**< authenticate mode : WPA2_ENTERPRISE */
    WIFI_AUTH_MAX
} wifi_auth_mode_t;



class WiFiClass
{
public:
    byte scanNetworks();
    String SSID(byte wifiAccessPoint);
    long RSSI(byte wifiAccessPoint);
    String BSSIDstr(byte wifiAccessPoint);
    byte encryptionType(byte wifiAccessPoint);
    byte begin(String ssid, String pass);
    byte status();
    String macAddress();
    IPAddress localIP();
    IPAddress gatewayIP();

};
extern WiFiClass WiFi;

#endif // WIFI_H_INCLUDED
