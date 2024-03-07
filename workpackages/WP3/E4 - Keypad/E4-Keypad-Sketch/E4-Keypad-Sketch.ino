// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 3
// Exercise 4
// Submission code: 2346743

#include <Keypad.h> // Include the keypad library

const byte rows = 4; // Number of rows
const byte columns = 4; // Number of columns

byte rowPins[rows] = {11, 10, 9, 8}; // The pins for each row
byte columnPins[columns] = {7, 6, 5, 4}; // The pins for each column

// The keypad grid containing all char values for each button (4x4)
char keysGrid[rows][columns] =
{
  {'1', '2', '3', 'A'}, // First row
  {'4', '5', '6', 'B'}, // Second row
  {'7', '8', '9', 'C'}, // Third row
  {'*', '0', '#', 'D'} // Fourth row
};

// Create an instance of 'Keypad' with the predefined grid and pins
Keypad keyboard = Keypad(makeKeymap(keysGrid), rowPins, columnPins, rows, columns);

void setup() // setup: Run only once when program starts
{
  Serial.begin(9600); // Start serial for printing
}

void loop() // loop: Reiterate for as long as the program runs
{
  char pressedKey = keyboard.getKey(); // Continiously read if any key was inputted by the user
  
  if (pressedKey != NO_KEY) // If a key was pressed
  {
    Serial.println(pressedKey); // Print the key that was pressed
  }
}