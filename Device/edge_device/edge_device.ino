#include "spiffs_utils.h"
#include "wifi_utils.h"
#include "http_utils.h"
#include <esp_system.h>

//Device name 1,2,3,..etc
char* Device_name="3";

//Global variable
uint8_t WIFI_STATUS;
static int One_Time_POST=0;

// The setup function runs once when the device starts/restarts.
void setup() {

    Serial.begin(115200);

    // Initialize SPIFFS and NVS
    initSPIFFS();
  //String myString = "Hello, World!";
  //char charArray[myString.length() + 1];
  //myString.toCharArray(charArray, sizeof(charArray));
    // Wait for a second before proceeding.
    delay(1000);
    
    // Check or generate hash key
    checkOrGenerateHashKey(Device_name);

    // Start the process of connecting to a WiFi network.
    Serial.println("Connecting to WiFi...");

    // Connect to WiFi
    WIFI_STATUS=connectToWiFi();
    if (WIFI_STATUS) {
      Serial.println("Connection Established");
      }
    else{
      Serial.println("Connection Failed");
      } 
}

// The loop function runs continuously after the setup function completes.
void loop() {
Serial.println(WiFi.localIP());
  if (!One_Time_POST){
    One_Time_POST++;
    WIFI_STATUS ? sendDataToServer(Device_name): delay(100) ;
  }
    delay(10000);  // Delay for 10 seconds before next loop
}
