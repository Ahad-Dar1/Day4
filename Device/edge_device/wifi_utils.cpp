#include "wifi_utils.h"
static uint8_t Timer_check=0;
int connectToWiFi() {
    WiFi.begin(AP_SSID, WIFI_PASS);
    
    // Wait until the device is connected to the WiFi network.
    while (WiFi.status() != WL_CONNECTED) {
       Timer_check++;
         if ( Wifi_Timer_Count==Timer_check){
          return FALSE; 
          }
       else delay(1000); 
        Serial.println("Connecting...");
    }
    return TRUE;
    // Print a confirmation message and the device's IP address once connected to the WiFi network.
    //Serial.println("Connected to WiFi");
    //Serial.println(WiFi.localIP());
}
