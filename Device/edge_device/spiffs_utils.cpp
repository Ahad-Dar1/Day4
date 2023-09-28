#include "spiffs_utils.h"


// Global Variables
String deviceContent;
char hexHashString[32 * 2 + 1];
byte hash[HASH_VAL_SIZE];
uint8_t deviceMac[RANDOM_NUM_LEN];

// Function to initialize SPIFFS and formate if issue
void initSPIFFS() {
    if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
        Serial.println("SPIFFS Mount Failed");
        return;
    }
}

// Function to read file from SPIFFS
void readFileFromSPIFFS(fs::FS &fs, const char * path) {
    Serial.printf("Reading file: %s\r\n", path);
    File file = fs.open(path);
    
    // Check if file pointer is valid
    if (!file || file.isDirectory()) {
        Serial.println("- failed to open file for reading");
        return;
    }
    
    Serial.println("- read from file:");
    while (file.available()) {
        char c = file.read();
        deviceContent += c;
    }
    
    Serial.print(deviceContent);
    file.close();
}


// Function to write data to a file in the SPIFFS (SPI Flash File System) of the ESP device.
void writeFileToSPIFFS(fs::FS &fs, const char * path, const char * message) {

    Serial.printf("Writing file: %s\r\n", path);

    // Open the specified file in write mode.
    File file = fs.open(path, FILE_WRITE);

    // Check if the file was successfully opened.
    if (!file) {
        // If the file couldn't be opened, print an error message to the serial port and exit the function.
        Serial.println("- failed to open file for writing");
        return;
    }

    // Write the provided message (data) to the file.
    if (file.print(message)) {
        // If the write operation was successful
        Serial.println("- Write Operation Successfull");
    } else {
        // If the write operation failed, print an error message to the serial port.
        Serial.println("- Write Operation Failed");
    }

    // Close the file after the write operation is complete.
    file.close();
}


// Function to delete a specified file from the SPIFFS (SPI Flash File System) of the ESP device.
void deleteFileFromSPIFFS(fs::FS &fs, const char * path) {
    
    // Attempt to remove the specified file from SPIFFS.
    if (fs.remove(path)) {
        // If the file was successfully deleted, print a confirmation message to the serial port.
        Serial.println("- File Deleted");
    } else {
        // If the delete operation failed, print an error message to the serial port.
        Serial.println("- Delete Operation Failed");
    }
}


// Function to generate and print hash
void generateDeviceHash() {
    SHA256 sha256;
    uint32_t randomValue;

    // Buffer to store concatenated data (random number + MAC address)
    uint8_t data[10] = {0};
    
    /* 
      This is impostant step for PUF emulation 
      We would generate a random_number representing a PUF retreived from EEPROM / memory
      Concatenate random_num + Device_ID [MAC] to create a private_id
      Calculate Hash on private_id to create HIDD1 [ archived on Local Admin ]
    */

    // Generating random number
    randomValue = esp_random();

    // Get base MAC address from EFUSE BLK3
    // This MAC address will act as the unique Device ID.
    esp_read_mac(deviceMac, ESP_MAC_WIFI_STA);

    // Ensure the destination buffer is large enough
    if (sizeof(data) < DEVICE_MAC_LEN + RANDOM_NUM_LEN) {
        // Handle error: destination buffer is too small
        return;
    }

    // Copy the MAC address (Device ID) into the data buffer
    memcpy(data, deviceMac, sizeof(deviceMac));

    // Append the random number to the data buffer, right after the MAC address
    memcpy(data + sizeof(deviceMac), &randomValue, sizeof(randomValue));

    // Calculate the SHA256 hash of the concatenated data (MAC address + random number).
    sha256.update(data, sizeof(data));
    sha256.finalize(hash, sizeof(hash));

    // Convert the hash into a hexadecimal string for easy display and logging
    for (int i = 0; i < sizeof(hash); i++) {
        sprintf(&hexHashString[i * 2], "%02X", hash[i]);
    }

    Serial.println(hexHashString);
}

void checkOrGenerateHashKey(char* Device_name) {
  Serial.print(Device_name);
    // Check if a file named "hashkey.txt" exists in SPIFFS.
       char concatenated_file_name[15];
       char* hashkey="/hashkey";
       char* txt=".txt";
        strcpy(concatenated_file_name,hashkey);
        strcat(concatenated_file_name,Device_name);
        strcat(concatenated_file_name,txt);
    if (SPIFFS.exists(concatenated_file_name)) {
        // If the file exists, read its contents.
        readFileFromSPIFFS(SPIFFS, concatenated_file_name);
    } else {
        // If the file doesn't exist, generate a device hash key.
        generateDeviceHash();
        // Write the generated hash key to a file named "hashkey.txt" in SPIFFS.
        writeFileToSPIFFS(SPIFFS, concatenated_file_name , hexHashString);
    }
}
