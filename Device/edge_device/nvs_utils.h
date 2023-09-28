/**
 * @file nvs_utils.h
 * @brief Utility functions for nvs operations.
 * 
 * This header provides utility functions to manage nvs read and write operations.
 */

#ifndef NVS_UTILS_H
#define NVS_UTILS_H

// Dependencies
#include <Preferences.h>

//Object of Preferences
extern Preferences preferences;
extern String Device_key_GET;
/**
 * @brief using function for nvs write.
 * return None
 */
void readToNvs(char* Device_name);

/**
 * @brief using function for nvs write.
 * return None
 */
void writeToNvs(char* Device_name);

#endif // WIFI_UTILS_H
