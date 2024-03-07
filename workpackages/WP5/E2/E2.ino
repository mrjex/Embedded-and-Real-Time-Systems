// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 5
// Exercise 2
// Submission code: 543765

// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h" // include the dht library

#define DHTPIN 12     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

#define N 5 // the number of leds
#define LED1 6 // define pin for led 1
#define LED2 5 // define pin for led 5
#define LED3 4 // define pin for led 4
#define LED4 3 // define pin for led 3
#define LED5 2 // define pin for led 5

int lights[N] = {
  LED1, LED2, LED3, LED4, LED5
}; // define an array of all pins

DHT dht(DHTPIN, DHTTYPE); // initialise the dht sensor

// define the setup function
void setup() {

  Serial.begin(9600); // begin the serial monitor

  // initialize all leds to output
  
  for(int i = 0; i<N; i++) { // for each pin
    pinMode(lights[i], OUTPUT); // set all pin modes to output
  }

  dht.begin(); // begin the dht library

}

void loop() {

  // Wait a few seconds between measurements.
  delay(2000);

  float t = dht.readTemperature(); // read the temperature
  // Check if any reads failed and exit early (to try again).
  if (isnan(t)) { // if the value is not a number
    Serial.println(F("Failed to read from DHT sensor!"));
    return; // exit the program
  }
  
  for(int i = 0; i < N; i++) { // for each light
    if(t >= i * 10) { // if the temperature has succeeded the threshold (i * 10)
      digitalWrite(lights[i], HIGH); // turn on the light
    }
    else {  //otherwise 
      digitalWrite(lights[i], LOW); // turn off the light
    }
  }


  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.println();
  
}