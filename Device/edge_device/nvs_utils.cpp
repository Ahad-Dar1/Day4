#include "nvs_utils.h"

//Globalvariable
String Device_key_GET;
Preferences preferences;

void writeToNvs(char* Device_name){
       preferences.begin("my-app", false);
       Serial.println(Device_name);
       char concatenated_nvs_ns[6];
       char* nvskey="nvs";
       strcpy(concatenated_nvs_ns,nvskey);
       strcat(concatenated_nvs_ns,Device_name);
       preferences.putString("myKey", Device_key_GET);
       // Close the NVS partition
       preferences.end();
}

void readToNvs(char* Device_name){
       preferences.begin("my-app", false);   
       Serial.println(Device_name);
       char concatenated_nvs_ns[6];
       char* nvskey="nvs";
       strcpy(concatenated_nvs_ns,nvskey);
       strcat(concatenated_nvs_ns,Device_name);
       Device_key_GET = preferences.getString("myKey", "No_Key");
       // Close the NVS partition
  
  }
