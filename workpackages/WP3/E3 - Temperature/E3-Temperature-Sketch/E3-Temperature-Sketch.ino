// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 3
// Exercise 3
// Submission code: 2346743

const int temperaturePin = A0; // Declare a constant variable for the analog pin

void setup() // setup: Run only once when program starts
{
  Serial.begin(9600); // Start Serial to enable printing of values
}

void loop() // loop: Reiterate for as long as the program runs
{ 
  int temperatureValue = analogRead(temperaturePin); // Read the value from the temperature sensor
 
  // Convert the analog reading to volate
  float voltage = temperatureValue * 4.68; // 5k volt / 1024
  temperatureValue = (voltage - 500) / 10; // Perform formula to retrieve the cellsius equivalent of the analog reading
  
  Serial.println(temperatureValue); // Print the cellsius value
  delay(100); // Set an arbitrary delay to make execution smooth
  
  /*
  	NOTE: The multimeter is connected through wires and automatically
    deals with the temperature and voltage. By connecting its negative
    end to 'GND' and positive end to the temperature sensor's 'Vout',
    (which the analog pin also is connected to), the desired value
    is displayed on its screen.
  */
}