// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 6
// Exercise 2: Sensing obstacles using ultrasonic sensor
// Submission code: 8BRU21

// ARDUINO PIN CONFIGURATION
# define BUZZER_PIN 2 // Piezo buzzer pin
# define TRIG_PIN 3 // Ultrasonic Sensor's TRIG pin
# define ECHO_PIN 4 // Ultrasonic Sensor's ECHO pin
const int LED_PINS[4] = {6, 7, 8, 9}; // LED pins

// UltraSonic Sensor Variables
float duration_us; // pulse duration in microseconds
float distance_cm; // distance in centimeters

// buzzer tones
const int BUZZER_TONES[5] = {600, 700, 800, 1000, 1500}; // buzzer tones (Hz)

// blink timer variables
int ledState = 0; // LED state (ON or OFF)
const int BLINK_PERIOD = 200; // blink period in milliseconds
unsigned long startTime = 0; // start time
unsigned long currentTime = 0; // current time

// OPTIONAL: the following variables are to enable averaging of distance
const int N = 1; // change variable from 1 to N to take running average of N samples
int count = 0; // counter
float sum_distance = 0.0; // sum of distance
float avg_distance = 0.0; // average distance

// Setup - runs once
void setup() {
  Serial.begin (9600);         // initialize serial port to 9600 baud rate
  pinMode(TRIG_PIN, OUTPUT);   // initialize trigger pin to OUTPUT
  pinMode(ECHO_PIN, INPUT);    // initialize echo pin to INPUT
  pinMode(BUZZER_PIN, OUTPUT); // initialize buzzer pin to OUTPUT

  // initialize LED pins
  for(int i = 0; i<4; i++){
    pinMode(LED_PINS[i], OUTPUT); // initialize LED pins to OUTPUT
  }
}

// Loop - runs continuously
void loop() {
  sum_distance += detectDistance(); // add the distance to sum
  count++; // increment the counter

  // if N>1 samples are collected, calculate the average distance
  if (count == N){ // default is N = 1
    avg_distance = sum_distance / count; // calculate the average distance
    checkObstacles(avg_distance); // check for obstacles
    sum_distance = 0; // reset the sum
    count = 0; // reset the counter
  }

  delay(100/N); // delay based on sampling frequency
}

float detectDistance(){
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, LOW); // turn off the pulse
  delayMicroseconds(2); // wait for 2 microseconds
  digitalWrite(TRIG_PIN, HIGH); // send 10-microsecond pulse
  delayMicroseconds(10); // wait for 10 microseconds
  digitalWrite(TRIG_PIN, LOW); // turn off the pulse

  // calculate distance using d = v*t/2 where v = 0.034 cm/microsecond (speed of sound in air)
  duration_us = pulseIn(ECHO_PIN, HIGH); // measure the echo duration in microseconds
  distance_cm = 0.034 * duration_us / 2; // calculate the distance in centimeters

  return distance_cm; // return the distance
}

// function to check for obstacles
void checkObstacles(int distance){
  if(distance <= 25){ // if distance is less than 25 cm
    turnOffLEDs(); // turn off all LEDs
    buzz(4); // generate buzzer tone
    blinkLEDs(); // blink four LEDs
  }else if(distance <= 30  && distance > 25){ // if distance is less than 30 cm
    turnOffLEDs(); // turn off all LEDs
    turnOnLEDs(4); // turn on four LEDs
    buzz(3); // generate buzzer tone
  }else if(distance <= 50 && distance > 30){ // if distance is less than 50 cm
    turnOffLEDs(); // turn off all LEDs
    turnOnLEDs(3); // turn on three LEDs
    buzz(2); // generate buzzer tone
  }else if(distance <= 100 && distance > 50){ // if distance is less than 100 cm
    turnOffLEDs(); // turn off all LEDs
    turnOnLEDs(2); // turn on two LEDs
    buzz(1); // generate buzzer tone
  }else if(distance <= 200&& distance > 100){ // if distance is less than 200 cm
    turnOffLEDs(); // turn off all LEDs
    turnOnLEDs(1); // turn on one LED
    buzz(0); // generate buzzer tone
  }else{ // if distance is greater than 200 cm
    turnOffLEDs(); // turn off all LEDs
    noBuzz();  // turn off Piezo Buzzer
  }

  // print distance to serial monitor for debugging
  Serial.print("distance: ");
  Serial.print(distance_cm); // print distance in cm
  Serial.println(" cm");
}

// function to turn on N LEDs
void turnOnLEDs(int n){
  for(int i=0; i<n; i++){ // turn on N LEDs
      digitalWrite(LED_PINS[i], HIGH); // write high signal
  }
  ledState = 1; // update LED state to 1
}

// function to turn off all LEDs
void turnOffLEDs(){
  for(int i=0; i<4; i++){ // turn off all LEDs
      digitalWrite(LED_PINS[i], LOW); // write low signal
  }
  ledState = 0; // update LED state to 0
}

// function to blink LEDs
void blinkLEDs(){
  currentTime = millis(); // get the current time
  if(!ledState && (currentTime - startTime > BLINK_PERIOD)){  // if LED is off and time to blink
    turnOnLEDs(4); // turn on all LEDs
    startTime = millis(); // save the start time using system clock
  }else if(ledState && (currentTime - startTime > BLINK_PERIOD)){ // if LED is on and time to blink
    turnOffLEDs(); // turn off all LEDs
    startTime = currentTime; // reset the start time
  }
}

// function to generate buzzer tone
void buzz(int i){
  tone(BUZZER_PIN, BUZZER_TONES[i], 500); // active buzzer on
    //digitalWrite(BUZZER_PIN, HIGH); // passive buzzer on
}

// function to stop buzzer tone
void noBuzz(){
  noTone(BUZZER_PIN); // active buzzer off
  //digitalWrite(BUZZER_PIN, LOW); // passive buzzer off
}