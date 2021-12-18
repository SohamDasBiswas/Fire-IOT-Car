# Fire-IOT-Car

## **Content :**
1. [Description](#description)
0. [Installation](#installation)
0. [Languages Used](#languages)
0. [Project Images](#project-images)


## **Description :**
This is a demonstration on using Firebase Client on microcontroller for building IoT systems. Here Node MCU is used as the microcontroller. Some of the utilities used here, are described below:

- **Node MCU** provides us with WiFi connectivity for ease of its implementation in home IoT systems. It has an 32bit 80MHz processor from espressif which is pretty fast for embedded project. What attracts many hobbyist to use it in their projects, is Arduino support and presence of a lot of libraries. It is very cheap (cheaper than an Arduino Uno board) and compact in size.

- **Firebase** is a platform developed by Google for creating mobile and web applications. Firebase RTDB or Realtime Database among is a service in firebase which can be used to make realtime communications from client to server just by including Firebase client libraries in the client applications. Here RTDB is used in the app as well as the nodemcu used in the IoT car 

For the Android Studio Application Source code(for IoT Car), visit [Fire-IoT-Car-Application](https://github.com/SohamDasBiswas/Fire-IOT-Car-Application)

## **Installation :**
### Softwares required :

- [**Visual Studio Code**](https://code.visualstudio.com/)

- [**Platform IO**](https://platformio.org/)

### Libraries :
- [**Arduino.h**](https://www.arduino.cc/en/Main/Software_)
- [**ESP8266WiFi.h**](https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/ESP8266WiFi.h)
- [**FirebaseESP8266.h** for ESP8266](https://firebase.google.com/)
<br>

***Just install Platform IO from VS Code extensions, open the repository on VS code and start working on the main.cpp inside ```src/main.cpp```***

## **Project Images :**

![IoT Car](https://user-images.githubusercontent.com/72512900/146649810-362d40a7-f6f4-4d80-8d5e-715b806d06c0.jpg)


## **Languages Used :**

- <img align="left" alt="C plus plus" width="60px" src="https://user-images.githubusercontent.com/72512900/146313275-30ec5b18-531f-4444-a777-025ff4deacbb.png" />