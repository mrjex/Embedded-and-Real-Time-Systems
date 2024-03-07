// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 3
// Exercise 2
// Submission code: 2346743

const int DELAY = 100; // initialise a delay variable to 100ms
const int TEMP_SENSOR = A0; // temp sensor is on PIN A0
const int LIGHT_SENSOR = A1; // light sensor is on PIN A1
const int ANALOG_MAX = 1023; // max possible value for analog signals

const int MIN_TEMP = -40; // minimum possible value for temperature (c)
const int MAX_TEMP = 125; // maximum possible value for temperature (c)
const float SENSOR_VOLTAGE = 5.0; // the voltage supplied to the temp sensor

const int MIN_LIGHT = 6; // minimum light sensor value based on this setup
const int MAX_LIGHT = 679; // maximum light sensor value based on this setup

typedef enum {
  RED = 8, // RED LED on pin 8
  YELLOW = 10, // YELLOW LED on pin 10
  GREEN = 9  // GREEN LED on pin 9
} Light; // declare an enum for all types of lights


// declare setup function
void setup()
{
  Serial.begin(9600); // set the rate of transmission to the serial
  pinMode(TEMP_SENSOR, INPUT); // set temperature sensor mode to input
  pinMode(LIGHT_SENSOR, INPUT); // set light sensor mode to input
  pinMode(RED, OUTPUT); // set red light mode to output
  pinMode(YELLOW, OUTPUT); // set red light mode to output
  pinMode(GREEN, OUTPUT); // set red light mode to output

}

void loop() // declare loop function
{

  // set threshold temperature to activate LEDs
  // measure temperature in Celsius
  int light = analogRead(LIGHT_SENSOR); // read analog light value
  int signal = analogRead(TEMP_SENSOR); // read analog temperature value
  
  // convert the signal to volts
  // first map the signal to the voltage provided
  // in this case signal * 5v this will yield the result in millivolts
  // then divide by 1024 to get the result in volts
  float volts = (signal * SENSOR_VOLTAGE) / (ANALOG_MAX + 1); // convert from analog to voltage

  // Translate voltage to temp in celcius
  // 1 - concidering that 500mv are allocated to account for negative numbers, subtract .5v
  // 3 - multiply the value by the scale factor (100 per volt)
  float celsius = (volts - 0.5) * 100;  
  checkLevels(celsius, light); // perform actions based on input values
  delay(DELAY); // delay execution by 100ms
  
}

// declare a functiont turnOn
// this function takes in a light to turn on
// and turns off all remaining lights
void turnOn(int light) {
  
  // set of all lights
  int lights[3] = { RED, YELLOW, GREEN };
  
  // for each light
  for(int i = 0; i < 3; i++) {
    
    // if the light is not the input
    if(lights[i] != light) {
      // turn it off
    	digitalWrite(lights[i], LOW);
    }
  }
  
  // turn on the provided light
  digitalWrite(light, HIGH);
  
}

// takes in input as temperature in celcius and light analog signal
// analyse the provided input and
// turn on / off leds based on the variations
void checkLevels(int temp, int light) {

  // Old approach 
  // calculate the ratio of the light
  // current / max * 100 to get a percentage
  // int ratio = ((float)(light) / MAX_LIGHT) * 100;
  
  // map the value from the range to 0 to 100
  int ratio = map(light, MIN_LIGHT, MAX_LIGHT, 0, 100);
  Serial.println(temp);
  Serial.println(ratio);

  if(ratio == 0) { // if the light ratio is 0%
    if(temp < -12) { // if the temp is below 12
       turnOn(GREEN); // turn on the greed led
    }
    else { // otherwise
       turnOn(RED); // turn on the red led
    }
  }
  
  if(ratio >= 1 && ratio <= 20) { // if the light ratio is between 1% and 20%
    // if the temperature is between -12 and 0
    if(temp >= -12 && temp <=0) { 
       turnOn(GREEN);// turn on the green light
    }
    // if the temperature is less than -12
    if(temp < -12) {
       turnOn(YELLOW); // turn on the yellow light
    }
    // if the temperature is above 0
    if(temp > 0) {
       turnOn(RED); // turn on the red light
    }
  }
  
  // if the light ratio is between 21 and 60%
  if(ratio >= 21 && ratio <= 60) {
    // if the temperature is between 0 and 20 degrees
    if(temp >=0 && temp <=20) {
      // turn on the green light
         turnOn(GREEN);
    }
    // if the temperature is less than 0
    if(temp < 0) {
       turnOn(YELLOW); // turn on the yellow led
    }
    // if the temperature is over 20
    if(temp > 20) {
       turnOn(RED); // turn on the red led
    }
  }
  
  // if the light ratio is between 61 and 100%
  if(ratio >= 61 && ratio <= 100) {
    if(temp >= 21) { // if the temperature is over 21 degrees
		turnOn(GREEN); // turn on the green light
    }
    else { // otherwise the temperature is too low
       turnOn(YELLOW); // turn on the yellow light
    }
  }
  
}