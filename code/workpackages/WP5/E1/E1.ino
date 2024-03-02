// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 5
// Exercise 1
// Submission code: 543765

/*
  This program blinks pin 13 LED of Arduino
  Uno and activates another LED when a button
  is pressed. 
*/
#define PIN13 13 //LED shines when pressing
#define PIN8 8 //LED blinks every 1 sec
#define PIN2 2 //Button sensor input
#define blinkingDelay 1000 // Delay for the LED to blink (ms)

int startTime; // Initialize the variable that stores the starting time of the current blinking animation
int currentTime; // Declare the continiously updating variable that represents the current time
int blinkState; // Create variable that decides whether or not the blinking LED is turned off/on

void setup() // setup: Run only once when program starts
{
  // Set input to read whether the button is pressed or not
  pinMode(PIN2, INPUT);
 
  
  /*
  	  Set these pins to output since we want the Arduino Uno
      to produce output (make the LEDs shine)
  */
  pinMode(PIN13, OUTPUT);
  pinMode(PIN8, OUTPUT);
  
  startTime = millis(); //Initialize timer
  
  /*
  	Initialize blinking LED to high.
  */
  digitalWrite(PIN8, HIGH); // Make the LED shine
  blinkState = 1; // Register its current state as an integer
}

void loop() // loop: Reiterate for as long as the program runs
{
  currentTime = millis(); // Continiously update the variable to sync it with the current time

  // Only make the LED shine if the second pin recieves input
  if (digitalRead(PIN2) == 1)
  {
    digitalWrite(PIN13, HIGH); // Make the LED shine
  }
  else // The LED shall not shine if no input from button is registered
  {
    digitalWrite(PIN13, LOW); // Turn off LED
  }
  
  if(currentTime - startTime > blinkingDelay){ // If the time since the last blinking animation exceed predefined delay
    startTime = currentTime; // Set the new time to measure the animation to the current time
    digitalWrite(PIN8, !blinkState); // Toggle LED shining state with the variable
    blinkState = !blinkState; // Switch between 0 and 1 (LOW, HIGH)
  }
   
  delay(50); // To smooth execution
}