# ESP8266 RGB Lamp & DHT11 Control Station

This project is an **ESP8266-based web server** that provides:
- Control over an RGB lamp with multiple color modes and effects.
- Real-time monitoring of temperature and humidity using a **DHT11 sensor**.

The project includes a built-in **WiFi Access Point**, allowing devices to connect and control the lamp or monitor sensor data via a user-friendly web interface.

## Configure the WiFi settings:
   - Open the code and locate the following section:
     ```cpp
     const char* ssid = "lamp";       // Access Point Name
     const char* password = "12345678";  // Access Point Password
     ```
   - Replace `"lamp"` and `"12345678"` with your desired SSID and password

## Features

### RGB Lamp Modes
- **Custom Color**: Choose your own color via an interactive interface.
- **Rainbow Mode**: Gradually transitions through a rainbow spectrum.
- **Fire Mode**: Simulates a warm flickering firelight.
- **Warm Mode**: Displays a cozy warm light.
- **Cold Mode**: Simulates a cool blue-white light.
- **Water Mode**: Mimics the shades of water.
- **Bright Mode**: Sets the lamp to maximum brightness.
- **Hacker Mode**: Displays a green blinking effect.
- **Random Blink Mode**: Randomly blinks different colors.

### Temperature & Humidity Display
- View real-time temperature (°C) and humidity (%) on the web interface.

### WiFi Access Point
- Create a local network with the **ESP8266**, allowing easy connection for nearby devices.

## Hardware Requirements
1. **ESP8266 Board** (e.g., NodeMCU or ESP-01)
2. **DHT11 Temperature and Humidity Sensor**
3. RGB LED or LED strip with the following pins:
   - Red LED pin: `D13`
   - Green LED pin: `D12`
   - Blue LED pin: `D15`
4. Breadboard and jumper wires
5. Power supply for the ESP8266

## Software Requirements
- **Arduino IDE** with the ESP8266 board package installed.
- Required libraries:
  - `ESP8266WiFi.h`
  - `ESP8266WebServer.h`
  - `DHT.h`
