# IoT System Setup Guide

This guide provides detailed instructions on setting up each module of the IoT system: Smart Device (with PUF emulation), Gateway, Blockchain, and Local Admin.

## Table of Contents

- [Smart Device Setup (PUF Emulation)](#smart-device-setup-puf-emulation)
- [Gateway Setup](#gateway-setup)
- [Blockchain Setup](#blockchain-setup)
- [Local Admin Setup](#local-admin-setup)

## Smart Device Setup (PUF Emulation)

1. **Install PUF Emulator**: Download and install the PUF emulator software from the official repository.
2. **Configure PUF Emulator**: Launch the emulator and select the device role that would emulate PUF to generate HIDD1.
3. **Test PUF Response**: Challenge the PUF emulator and ensure it provides a consistent response.
   # Libraries used :
   1. "FS.h"                                                                  -- built-in
   2. "SPIFFS.h"                                                              -- built-in
   3. "esp_system.h"                                                          -- built-in
   4. "HTTPClient.h"                                                          -- built-in
   5. "Wifi.h"                                                                -- built-in
   6. "Crypto.h" -- [Cryptography](https://github.com/OperatorFoundation/Crypto)
   7. "ArduinoJson.h" -- [ArduinoJson Repository](https://github.com/bblanchon/ArduinoJson)

## Gateway Setup

1. **Install Gateway Software**: Download and install the IoT gateway software.
2. **Configure Gateway**: Set up the gateway's secret key for encrypting and decrypting device keys.
3. **Connect to Local Blockchain**: Ensure the gateway has network access to the local blockchain for fetching device public IDs.

## Blockchain Setup

1. **Install Blockchain Node**: Set up a local blockchain node. This can be a lightweight node if resources are limited.
2. **Initialize Blockchain**: Create the genesis block and initialize the blockchain dataset.
3. **API Access**: Ensure the blockchain provides an API endpoint for the gateway and local admin to interact with.

## Local Admin Setup

1. **Install Admin Dashboard**: Download and install the local admin dashboard software.
2. **Connect to Blockchain**: Configure the dashboard to connect to the local blockchain for device registration and verification.
3. **Device Registration**: Use the dashboard to register new devices, challenge their PUFs, and upload their details to the blockchain.
4. **Device Verification**: Periodically verify the devices connected to the IoT system using the dashboard.

## Conclusion

Once all modules are set up and configured, the IoT system should be operational. Regularly update each module to ensure security and performance. For any issues or support, refer to the official documentation or contact the support team.
