/**
 * @file wifi_utils.h
 * @brief Utility functions for WiFi operations.
 * 
 * This header provides utility functions to manage WiFi operations such as connection.
 */

#ifndef WIFI_UTILS_H
#define WIFI_UTILS_H

// Dependencies
#include <WiFi.h>
#include "config.h"

/**
 * @brief Connects to the WiFi using credentials from config.h.
 * 
 * This function will attempt to establish a connection to the WiFi network using the SSID
 * and password defined in config.h. If the connection is successful, the device will remain
 * connected; otherwise, it will retry until a connection is established.
 */
int connectToWiFi();

#endif // WIFI_UTILS_H
