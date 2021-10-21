#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>


#include "config.h"

int fireStatus = 0;
int prevStatus = 0;
FirebaseData fbdo;

#define ENA   14          // Enable/speed motors Right        GPIO14(D5)
#define ENB   12          // Enable/speed motors Left         GPIO12(D6)
#define IN_1  5          // L298N in1 motors Rightx          GPIO15(D8)
#define IN_2  13          // L298N in2 motors Right           GPIO13(D7)
#define IN_3  2           // L298N in3 motors Left            GPIO2(D4)
#define IN_4  4           // L298N in4 motors Left            GPIO0(D3)


//Turning Speed Lower bound 250 to avoid stalling
#define TURN_SPEED 200      //350


String command;             //String to store app command state.
uint16_t speedCar = 610;         // 400 - 1023.
int speed_Coeff = 4;

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
void goAhead();
void goBack();
void goRight();
void goLeft();
void goAheadRight();
void goAheadLeft();
void goBackRight();
void goBackLeft() ;
void stopRobot();

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
  analogWriteFreq(150); //Lowers the freq. from 1kHz default to 150Hz
  Serial.begin(74880);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnected.");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}


void loop() {
  if (Firebase.getInt(fbdo, "car/move"))
  {
    fireStatus = fbdo.intData();
    Serial.println(fireStatus);
    if (prevStatus != fireStatus)
    {
      prevStatus = fireStatus;
      switch(fireStatus){
        case FORWARD:
          Serial.println("Forward");
          goAhead();
          delay(10);
          break;
        
        case BACKWARD:
          Serial.println("Reverse");
          goBack();
          delay(10);
          break;
        
        case LEFT:
          Serial.println("Left");
          goLeft();
          delay(10);
          break;
        
        case RIGHT:
          Serial.println("Right");
          goRight();
          delay(10);
          break;
        
        case FW_RIGHT:
          Serial.println("Forword-Right");
          goAheadRight();
          delay(10);
          break;
        
        case FW_LEFT:
          Serial.println("Forword-Left");
          goAheadLeft();
          delay(10);
          break;
        
        case RE_RIGHT:
          Serial.println("Reverse-Right");
          goBackRight();
          delay(10);
          break;
        
        case RE_LEFT:
          Serial.println("Reverse-Left");
          goBackLeft();
          delay(10);
          break;
        
        case SPEED_1:
          Serial.println("Speed of the car 1");
          speedCar = 200;
          analogWrite(ENA, speedCar);
          analogWrite(ENB, speedCar);
          delay(10);
          break;
        
        case SPEED_2:
          Serial.println("Speed of the car 2");
          speedCar = 400;
          analogWrite(ENA, speedCar);
          analogWrite(ENB, speedCar);
          delay(10);
          break;
        
        case SPEED_3:
          Serial.println("Speed of the car 3");
          speedCar = 540;
          analogWrite(ENA, speedCar);
          analogWrite(ENB, speedCar);
          delay(10);
          break;
        
        case SPEED_4:
          Serial.println("Speed of the car 4");
          speedCar = 610;
          analogWrite(ENA, speedCar);
          analogWrite(ENB, speedCar);
          delay(10);
          break;
        
        case SPEED_5:
          Serial.println("Speed of the car 5");
          speedCar = 680;
          analogWrite(ENA, speedCar);
          analogWrite(ENB, speedCar);
          delay(10);
          break;
        
        case SPEED_6:
          Serial.println("Speed of the car 6");
          speedCar = 750;
          analogWrite(ENA, speedCar);
          analogWrite(ENB, speedCar);
          delay(10);
          break;
        
        case SPEED_7:
          Serial.println("Speed of the car 7");
          speedCar = 820;
          analogWrite(ENA, speedCar);
          analogWrite(ENB, speedCar);
          delay(10);
          break;
        
        case SPEED_8:
          Serial.println("Speed of the car 8");
          speedCar = 890;
          analogWrite(ENA, speedCar);
          analogWrite(ENB, speedCar);
          delay(10);
          break;
        
        case SPEED_9:
          Serial.println("Speed of the car 9");
          speedCar = 960;
          analogWrite(ENA, speedCar);
          analogWrite(ENB, speedCar);
          delay(10);
          break;
        
        case SPEED_10:
          Serial.println("Speed of the car 10");
          speedCar = 1023;
          analogWrite(ENA, speedCar);
          analogWrite(ENB, speedCar);
          delay(10);
          break;
        
        case STOP:
          Serial.println("Stop");
          stopRobot();
          delay(10);
          break;
        
      }
    }
  }
  delay(10);
}


void goAhead() {

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}

void goBack() {

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}

void goRight() {

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}

void goLeft() {

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}

void goAheadRight() {

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

void goAheadLeft() {

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

void goBackRight() {

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

void goBackLeft() {

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

void stopRobot() {

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}