// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 2
// Exercise 1
// Submission code: 755350

#include <Servo.h> // include the Servo library

const byte TICK_RATE = 156; // trigger every 156 ticks (10ms)
// can be calculated via the formula
// TickRate = (ms * 10^6) / (prescaler * 62.5)

const byte MOTOR_PIN = A5; // define the motor pin as a constant A5
Servo servo_A5; // define Servo

int iDegrees = 180; // set the initial degrees to 180

int ms = 0; // set the milliseconds counter to 0
int seconds = 0; // set the seconds counter to 0

// define the interrupt for compA
ISR(TIMER2_COMPA_vect) {
  OCR2A += TICK_RATE; // Set the next comparison point to next tick
  ms += 10; // increment the seconds by 0.1
}

// define the setup function
void setup()
{

  // start the serial stream
  Serial.begin(9600);

  cli(); // disable interrupts
  
  TCCR2A = 0b00000000; // initialise TCCR2A register
  TCCR2B = 0b00000111; // set the prescaler to 1024
  OCR2A =  TICK_RATE;  // run every 10 ms
  TIMSK2 = 0b00000010; // set compare match A interrupt
  
  // attach the servo
  servo_A5.attach(MOTOR_PIN);
  
  // write the servo initially to 180
  servo_A5.write(iDegrees);
  
  sei(); // enable interrupts

}

// define the loop function
void loop()
{

  // if the ms surpassed 1000ms
  if(ms >= 1000) {
    ms = 0; // reset the ms counter to 0
    seconds++; // increment the seconds by 1
    // if the current degrees are 0 reset back to 180
    // otherwise decrement by 1 degree
    iDegrees = iDegrees == 0 ? 180 : iDegrees-1;
    // write the degrees to the motor
    servo_A5.write(iDegrees);
    
    //print the seconds
    Serial.println(seconds);
  }
  
}

// function to calculate the ticks based a delay in ms
// and a prescaler (64, 1024)
int calculateDelay(int ms, int prescaler) {
	return (ms * 1E6) / (prescaler * 62.5);
}

