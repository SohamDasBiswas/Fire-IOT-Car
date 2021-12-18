#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#include "config.h"

#define ENA 14  // Enable/speed motors Right        GPIO14(D5)
#define ENB 12  // Enable/speed motors Left         GPIO12(D6)
#define IN_1 5  // L298N in1 motors Rightx          GPIO15(D8)
#define IN_2 13 // L298N in2 motors Right           GPIO13(D7)
#define IN_3 2  // L298N in3 motors Left            GPIO2(D4)
#define IN_4 4  // L298N in4 motors Left            GPIO0(D3)
#define LOWER_LIMIT 0
#define UPPER_LIMIT 1023

// Turning Speed Lower bound 250 to avoid stalling
#define TURN_SPEED 200 // 350

String command; // String to store app command state.
int direction;
int prevDirection;
uint16_t speedCar = 610; // 400 - 1023.
uint16_t prevSpeed;
FirebaseData fbdo;

enum Choice
{
  FW_LEFT = 11,
  LEFT = 21,
  RE_LEFT = 31,

  FORWARD = 12,
  STOP = 0,
  BACKWARD = 32,

  FW_RIGHT = 13,
  RIGHT = 23,
  RE_RIGHT = 33,

  SPEED_1 = 1,
  SPEED_2 = 2,
  SPEED_3 = 3,
  SPEED_4 = 4,
  SPEED_5 = 5,
  SPEED_6 = 6,
  SPEED_7 = 7,
  SPEED_8 = 8,
  SPEED_9 = 9,
  SPEED_10 = 10,
};

/* prototypes */
void updateSpeed();                                                   // update speed from global speed
void updateSpeed(uint16_t);                                           // update speed specified in param
void setDirection(bool in1, bool in2, bool in3, bool in4);            // keeps speed unaffected
void setDirections(bool in1, bool in2, bool in3, bool in4, uint16_t); // changes speed
void goAhead();
void goBack();
void goRight();
void goLeft();
void goAheadRight();
void goAheadLeft();
void goBackRight();
void goBackLeft();
void stopRobot();

void setup()
{
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
  analogWriteFreq(150); // Lowers the freq. from 1kHz default to 150Hz
  Serial.begin(74880);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnected.");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop()
{
  if (Firebase.getInt(fbdo, "car/move"))
  {
    direction = fbdo.intData();
    Serial.println(direction);
    if (prevDirection != direction)
    {
      prevDirection = direction;
      switch (direction)
      {
      case FORWARD:
        Serial.println("Forward");
        goAhead();
        break;

      case BACKWARD:
        Serial.println("Reverse");
        goBack();
        break;

      case LEFT:
        Serial.println("Left");
        goLeft();
        break;

      case RIGHT:
        Serial.println("Right");
        goRight();
        break;

      case FW_RIGHT:
        Serial.println("Forword-Right");
        goAheadRight();
        break;

      case FW_LEFT:
        Serial.println("Forword-Left");
        goAheadLeft();
        break;

      case RE_RIGHT:
        Serial.println("Reverse-Right");
        goBackRight();
        break;

      case RE_LEFT:
        Serial.println("Reverse-Left");
        goBackLeft();
        break;
      // deprecated from here
      case SPEED_1:
        Serial.println("Speed of the car 1");
        speedCar = 200;
        analogWrite(ENA, speedCar);
        analogWrite(ENB, speedCar);
        break;

      case SPEED_2:
        Serial.println("Speed of the car 2");
        speedCar = 400;
        analogWrite(ENA, speedCar);
        analogWrite(ENB, speedCar);
        break;

      case SPEED_3:
        Serial.println("Speed of the car 3");
        speedCar = 540;
        analogWrite(ENA, speedCar);
        analogWrite(ENB, speedCar);
        break;

      case SPEED_4:
        Serial.println("Speed of the car 4");
        speedCar = 610;
        analogWrite(ENA, speedCar);
        analogWrite(ENB, speedCar);
        break;

      case SPEED_5:
        Serial.println("Speed of the car 5");
        speedCar = 680;
        analogWrite(ENA, speedCar);
        analogWrite(ENB, speedCar);
        break;

      case SPEED_6:
        Serial.println("Speed of the car 6");
        speedCar = 750;
        analogWrite(ENA, speedCar);
        analogWrite(ENB, speedCar);
        break;

      case SPEED_7:
        Serial.println("Speed of the car 7");
        speedCar = 820;
        analogWrite(ENA, speedCar);
        analogWrite(ENB, speedCar);
        break;

      case SPEED_8:
        Serial.println("Speed of the car 8");
        speedCar = 890;
        analogWrite(ENA, speedCar);
        analogWrite(ENB, speedCar);
        break;

      case SPEED_9:
        Serial.println("Speed of the car 9");
        speedCar = 960;
        analogWrite(ENA, speedCar);
        analogWrite(ENB, speedCar);
        break;

      case SPEED_10:
        Serial.println("Speed of the car 10");
        speedCar = 1023;
        analogWrite(ENA, speedCar);
        analogWrite(ENB, speedCar);
        break;
        // deprecated till here
      case STOP:
        Serial.println("Stop");
        stopRobot();
        break;
      }
      delay(10);
    }
  }
  delay(5);
  // modified
  if (Firebase.getInt(fbdo, "car/speed"))
  {
    speedCar = fbdo.intData();
    Serial.println(speedCar);
    // if the speed is not same as the previous poll
    if (speedCar != prevSpeed)
    {
      // if speed is within limits
      if (speedCar >= LOWER_LIMIT && speedCar <= UPPER_LIMIT)
      {
        updateSpeed(speedCar);
        delay(10);
      }
      else
        speedCar = prevSpeed; // speed remains unaffected
      prevSpeed = speedCar;   // update the previous speed
    }
  }
  delay(5);
}

void goAhead()
{

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}

void goBack()
{

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}

void goRight()
{

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}

void goLeft()
{

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}

void goAheadRight()
{

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
  delay(100);
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}

void goAheadLeft()
{

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
  delay(100);
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}

void goBackRight()
{

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
  delay(100);
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}

void goBackLeft()
{

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
  delay(100);
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}
// modified
void stopRobot()
{
  setDirection(LOW, LOW, LOW, LOW);
}

// native update speed function
void updateSpeed()
{
  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
}
// call if speed is specified in the parameter
void updateSpeed(uint16_t speed)
{
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  // update the global variable
  speedCar = speed;
}
// set directions
void setDirection(bool in1, bool in2, bool in3, bool in4)
{
  digitalWrite(IN_1, in1);
  digitalWrite(IN_2, in2);
  digitalWrite(IN_3, in3);
  digitalWrite(IN_4, in4);
}
// set directions as well as speed
void setDirection(bool in1, bool in2, bool in3, bool in4, uint16_t speed)
{
  setDirection(in1, in2, in3, in4);
  updateSpeed(speed);
}
