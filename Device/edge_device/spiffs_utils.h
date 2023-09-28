/**
 * @file spiffs_utils.h
 * @brief ESP32 File Operations with SPIFFS
 *
 * This header file provides functions for handling file operations on the ESP32 using SPIFFS.
 * It includes methods for reading, writing, and deleting files, as well as generating SHA256 hashes.
 */

#ifndef SPIFFS_UTILS_H
#define SPIFFS_UTILS_H

// Dependencies
#include "FS.h"
#include "SPIFFS.h"
#include <SHA256.h>
#include <string.h>

// Constants
#define DEVICE_MAC_LEN      6  ///< Length of the device MAC address in bytes.
#define RANDOM_NUM_LEN      4  ///< Length of the random number in bytes.
#define PRIVATE_KEY_SIZE    DEVICE_MAC_LEN + RANDOM_NUM_LEN  ///< Total size of the private key.
#define HASH_VAL_SIZE       32 ///< Size of the hash value.

#define FORMAT_SPIFFS_IF_FAILED true ///< Flag to format SPIFFS if initialization fails.

/**
 * @brief Reads the content from a specified file.
 * 
 * @param fs Filesystem reference.
 * @param path Path to the file.
 */
void readFileFromSPIFFS(fs::FS &fs, const char * path);

/**
 * @brief Generates a SHA256 hash of a given input and prints the result.
 */
void generateDeviceHash();

/**
 * @brief Checks if a hash key exists, if not, generates a SHA256 hash.
 */
void checkOrGenerateHashKey(char* Device_name);

/**
 * @brief Writes a specified message to a specified file.
 * 
 * @param fs Filesystem reference.
 * @param path Path to the file.
 * @param message Message to be written to the file.
 */
void writeFileToSPIFFS(fs::FS &fs, const char * path, const char * message);

/**
 * @brief Deletes a specified file.
 * 
 * @param fs Filesystem reference.
 * @param path Path to the file.
 */
void deleteFile(fs::FS &fs, const char * path);

/**
 * @brief HIDDI to transfer to endpoint for verification
 */
 
extern String deviceContent;

/**
 * @brief Checks if a hash key exists, if not, generates a SHA256 hash.
 */
 
void initSPIFFS();

#endif // SPIFFS_UTILS_H
