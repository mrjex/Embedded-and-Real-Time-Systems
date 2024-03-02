// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 5
// Exercise 2b
// Submission code: 543765

#include "DHT.h" // Including DHT library

#define DHTPIN 12     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

#define PIN_L A4  // Light sensor pin 
#define PIN_R 2 // Red LED pin
#define PIN_Y 3 // Yellow LED pin
#define PIN_G 4 // Green LED pin

const int ANALOG_MAX = 1023; //max value of analog read

const int MAX_LIGHT = 1024; //max value of light sensor (empirical)
const int MIN_LIGHT = 850; //min value of light sensor (empirical)
const int DEG_12 = 12; //12 degrees
const int DEG0 = 0; //0 degrees
const int DEG21 = 21; //21 degrees

const int PERIOD = 1000; //period in ms for reading from DHT sensor

// Enum for the LED states
typedef enum {
  RED = PIN_R, // Red LED pin
  YELLOW = PIN_Y, // Yellow LED pin
  GREEN = PIN_G, // Green LED pin
}Light; // typedef for the LED states

int tempSensor; // Temperature sensor value
int lightSensor; // Light sensor value

DHT dht(DHTPIN, DHTTYPE); // Creating DHT object

float lightValue; // Light value after normalization

Light ledState; // LED state (RED, YELLOW, GREEN) enum

// Setup function - runs once at the beginning of the program
void setup()
{
  Serial.begin(9600); // Starting serial communication
  pinMode(PIN_L, INPUT); // Setting light sensor pin as input

  // Setting LED pins as output
  pinMode(PIN_R, OUTPUT); // Red LED pin
  pinMode(PIN_Y, OUTPUT); // Yellow LED pin
  pinMode(PIN_G, OUTPUT); // Green LED pin

  dht.begin(); // Starting DHT sensor
}

// Loop function - runs repeatedly after the setup function
void loop()
{
  tempSensor = (int) dht.readTemperature(); // Reading temperature from DHT sensor and converting it to integer
  lightSensor = analogRead(PIN_L); // Reading light sensor value
  
  // Normalizing light sensor value
  lightValue = (((float)(lightSensor - MIN_LIGHT))/(float) (MAX_LIGHT - MIN_LIGHT) )* 100.0;
  
  // Setting LED state based on temperature and light sensor values (according to requirements)
  if(lightValue == 0.0){ // 0 light value
    if(tempSensor < DEG_12){ //less than 12 degrees
      ledState = GREEN; // Green LED state
    }else{ //greater than or equal to 12 degrees
      ledState = RED; // Red LED state
    }
  }else if(lightValue > 0.0 && lightValue <=20.0){ //0 to 20  light value
    if(tempSensor >= DEG_12 && tempSensor <= DEG0){ //12 to 0 degrees
      ledState = GREEN; // Green LED state
    }else if(tempSensor >DEG0){ //greater than 0 degrees
      ledState = RED; // Red LED state
    }else{ //less than 12 degrees
      ledState = YELLOW; // Yellow LED state
    }
  }else if(lightValue >20.0 && lightValue <=60.0){ //20 to 60 light value
    if(tempSensor >= DEG0 && tempSensor < DEG21){ //0 to 21 degrees
      ledState = GREEN; // Green LED state
    }else if(tempSensor >=DEG21){ //greater than or equal to 21 degrees
      ledState = RED; // Red LED state
    }else{  //less than 0 degrees
      ledState = YELLOW; // Yellow LED state
    }
  }else{ //60 to 100 light value
    if(tempSensor >= DEG21){ //greater than or equal to 21 degrees
      ledState = GREEN; // Green LED state
    }else{ //less than 21 degrees
      ledState = YELLOW; // Yellow LED state
    }
  }

  // Setting LED state based on the LED state enum
  if(ledState == RED){ // Red LED state
    digitalWrite(PIN_R, HIGH); // Turning on the red LED
    digitalWrite(PIN_Y, LOW); // Turning off the yellow LED
    digitalWrite(PIN_G, LOW); // Turning off the green LED
  }else if(ledState == YELLOW){ // Yellow LED state
    digitalWrite(PIN_Y,HIGH); // Turning on the yellow LED
    digitalWrite(PIN_R, LOW); // Turning off the red LED
    digitalWrite(PIN_G, LOW); // Turning off the green LED
  }else if(ledState == GREEN){ // Green LED state
    digitalWrite(PIN_G, HIGH); // Turning on the green LED
    digitalWrite(PIN_Y,LOW); // Turning off the yellow LED
    digitalWrite(PIN_R, LOW); // Turning off the red LED
  }
  
  
  // Printing temperature, light and LED state values
  Serial.print("Temp: "); // Printing temperature value
  Serial.print(tempSensor); // Printing temperature value
  Serial.print("\n");
  
  Serial.print("Light: "); // Printing light value
  Serial.print(lightValue); // Printing light value
  Serial.print("\n");
  /*
  Serial.print("analog light sensor value: ");
  Serial.print(lightSensor);
  Serial.print("\n");
  */
  Serial.print("LED state: "); // Printing LED state
  Serial.print(ledState); // Printing LED state
  Serial.print("\n");
  

  delay(PERIOD); // Wait for 1 second according to user defined period
}