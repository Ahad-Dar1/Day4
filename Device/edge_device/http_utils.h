/**
 * @file HTTPUtils.h
 * @brief Utility functions for HTTP operations.
 * 
 * This header defines the utility functions used for sending data to the server.
 * It includes necessary libraries and configurations for HTTP operations.
 */

#ifndef HTTP_UTILS_H
#define HTTP_UTILS_H

// Required Libraries
#include <ArduinoJson.h>
#include <HTTPClient.h>

#include "config.h"

/**
 * @brief Sends data to the server.
 * 
 * This function is responsible for sending data to the server using HTTP protocol.
 * It utilizes the HTTPClient library for the operations.
 */
void sendDataToServer(char* Device_name);

#endif // HTTP_UTILS_H
