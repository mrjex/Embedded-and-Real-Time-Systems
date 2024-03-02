// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 6: Exercise 1 - Task 1
// Task 1: Driving the motor with user specified direction and speed
// Submission code: 8BRU21

// WP 6 Exercise 1 Template DIT 632
// Define pin numbers for encoder and motor control
#define ENCA 2 // Encoder pin A
#define ENCB 3 // Encoder pin B
#define PWM1 5 // Motor control pin 1
#define PWM2 6 // Motor control pin 2
#define MAX_SPEED 255 // Maximum speed

int pos = 0; // Position in ticks
int deg = 0; // Position in degrees

int degtarget = 0; // Target position in degrees

int speed = 0; // Desired motor speed

// Setup function
void setup()
{
    // Initialize serial communication and pin modes
    Serial.begin(9600); // initialize serial port to 9600 baud rate
    pinMode(ENCA, INPUT_PULLUP); // initialize encoder pin A to INPUT_PULLUP
    pinMode(ENCB, INPUT_PULLUP); // initialize encoder pin B to INPUT_PULLUP
    pinMode(PWM1, OUTPUT); // initialize PWM1 pin to OUTPUT
    pinMode(PWM2, OUTPUT); // initialize PWM2 pin to OUTPUT

    // Start motor with a small initial PWM to avoid TinkerCAD bug
    analogWrite(PWM2, 10); // turn motor CCW
    delay(1000); // TinkerCAD bug
    analogWrite(PWM1, 10); // turn motor CW
}

// Loop function
void loop()
{
    // Get speed and direction from serial input
    getSpeedAndDirection();

    // Check if speed is positive or negative
    if (speed > 0){
        analogWrite(PWM2, 0); // turn off motor CCW
        analogWrite(PWM1, speed); // turn motor CW
        delay(1000); // TinkerCAD bug
    }else if(speed < 0){
        analogWrite(PWM1, 0); // turn off motor CW
        analogWrite(PWM2, -speed); // turn motor CCW
        delay(1000); // TinkerCAD bug
    }else{ // if speed is zero, avoid tinkerCAD bug
        analogWrite(PWM2, 10); // turn off motor CW
        delay(1000); // TinkerCAD bug
        analogWrite(PWM1, 10); // turn off motor CCW
    }
}

// Function to get initial speed and direction from user
void getSpeedAndDirection()
{
    int validInput = 0; // Flag to check if input is valid

    // Loop until user gives a valid input for speed (-255 to 255)
    while (!validInput) {
        Serial.print("Please enter the initial speed and direction (-255 to 255): \n");

        // Wait for serial input
        while (!Serial.available());

        // Read speed value
        speed = Serial.parseInt();

        // Check if input is valid (needs to be between -255 and 255)
        if (speed > MAX_SPEED || speed < -MAX_SPEED) { // If input is invalid
            Serial.println("Invalid! Please enter a valid speed and direction (-255 to 255).");
        } else { // If input is valid
            validInput = 1; // Set flag to indicate valid input
            Serial.print("Speed: ");
            Serial.print(speed); // Print initial speed
            if (speed > 0) { // Check direction
                Serial.print(" clockwise"); // Print direction
            } else if (speed < 0) { // Check direction 
                Serial.print(" counterclockwise"); // Print direction
            }
            Serial.print("\n");
        }
        delay(100); // Wait for 0.1 seconds for user to read the message
    }
}