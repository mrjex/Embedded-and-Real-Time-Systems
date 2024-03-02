// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 3
// Exercise 3
// Submission code: 2346743

const byte nR = 4; // Number of rows
const byte nC = 4; // Number of columns

byte rowPins[nR] = {11, 10, 9, 8}; // Pins for all rows
byte columnPins[nC] = {7, 6, 5, 4}; // Pins for all columns

// The keypad grid containing all char values for each button (4x4)
char keyGrid[nR][nC] =
{
  {'1', '2', '3', 'A'}, // First row
  {'4', '5', '6', 'B'}, // Second row
  {'7', '8', '9', 'C'}, // Third row
  {'*', '0', '#', 'D'} // Fourth row
};

void setup() // setup: Run only once when program starts
{
  Serial.begin(9600); // Start serial to enable printing
  
  /*
  	Define pin modes for all rows and columns
  */
  for (int i = 0; i < nR; i++) // Iterate through the length of rows and columns
  {
    pinMode(rowPins[i], OUTPUT); // Set row-pins to output
    pinMode(columnPins[i], INPUT); // Set column-pins to input
  }
}

void loop() // loop: Reiterate for as long as the program runs
{
  	// Iterate through each row
    for (int i = 0; i < nR; i++)
    {
        digitalWrite(rowPins[i], LOW); // Deactivate current row
      
      	// Iterate through each column
        for (int j = 0; j < nC; j++)
        {
          	/*
            	If the current column is deactivated,
                it implies that it is synced with the
                row that was interacted with.
            */
            if (digitalRead(columnPins[j]) == LOW)
            {
              Serial.println(keyGrid[i][j]); // Print selected key
              delay(1000); // Delay for 1 second only if a button is pressed
            }
        }
        digitalWrite(rowPins[i], HIGH); // Activate row again
    }  
}