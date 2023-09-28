#include "http_utils.h"
#include "spiffs_utils.h"
#include "nvs_utils.h"

//Global Variable
static int One_Time_request=0;
char Device_identity[13];
int POST_Request(char* Device_name){
   StaticJsonDocument<200> jsonDocument2;
   StaticJsonDocument<200> jsonDocument3;
   String jsonData;
   jsonDocument2["DeviceName"]=Device_identity;
   serializeJson(jsonDocument2, jsonData);
   HTTPClient httpClient;
   httpClient.begin(SERVER_URL2);
   httpClient.addHeader("Content-Type", "application/json");
   int httpResponseCode = httpClient.POST(jsonData);  
   httpClient.end();
   if (httpResponseCode==200){
     String serverResponse = httpClient.getString();
     deserializeJson(jsonDocument3,serverResponse);
     Device_key_GET=jsonDocument3["RandomNumber"].as<String>();
     if (Device_key_GET){
      writeToNvs(Device_name);
    return 1;
    }
   else {
    return 0;
    }
  }
}
void sendDataToServer(char* Device_name) {
    // Create a JSON object to store device data.
    StaticJsonDocument<200> jsonDocument1;
    strcpy(Device_identity,"Silicon __a");
    strcat(Device_identity,Device_name);
    jsonDocument1["DeviceName"] = Device_identity;
    jsonDocument1["DeviceId"]=deviceContent;
    Serial .print(Device_identity);
    // Convert (serialize) the JSON object to a String format.
    String jsonData;
    serializeJson(jsonDocument1, jsonData);
    Serial.println(jsonData);
    // Initialize an HTTP client to send data to a server.
    HTTPClient httpClient;
    httpClient.begin(SERVER_URL);

    // Set the content type of the HTTP request to JSON.
    httpClient.addHeader("Content-Type", "application/json");

    // Send a POST request with the JSON data to the server.
   int httpResponseCode = httpClient.POST(jsonData);
    //Serial.print(httpResponseCode);
    //deserializeJson(jsonDocument2,httpResponseCode);

    httpClient.end();
   if(httpResponseCode==404 && One_Time_request==0){
            while(One_Time_request>5){
            One_Time_request++;
            Serial.print("Found");
            int checker;
            checker=POST_Request(Device_name);
            if (checker){
              break;
              }
            delay(1000);
            }
      }
    // If the server responded with a positive response code
    Serial.println("\nHTTP Response code: ");
    //Serial.println(httpResponseCode);

    // Check the server's response code.
    //if (httpResponseCode > 0) {
        // Get the server's response message and print it to the serial port.
      //  String serverResponse = httpClient.getString();
      //  Serial.println(serverResponse);
   // } else {
    //    // If the HTTP request failed, print an error message to the serial port.
    //    Serial.println("HTTP request failed");
   // }
}
