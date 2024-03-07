// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 6: Exercise 1 - Task 2 && Task 3
// Task 2: Reading the encoder with interrupt
// Task 3: Implementing a position controller
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

int kp = 5;    // Proportional constant for controller (tuning parameter)
int u_out = 0; // Output of controller

int e = 0; // Error
int a = 0; // A-encoder signal
int b = 0; // B-encoder signal

// Setup function
void setup()
{
    // Initialize serial communication and pin modes
    Serial.begin(9600); // initialize serial port to 9600 baud rate
    pinMode(ENCA, INPUT_PULLUP); // initialize encoder pin A to INPUT_PULLUP
    pinMode(ENCB, INPUT_PULLUP); // initialize encoder pin B to INPUT_PULLUP
    pinMode(PWM1, OUTPUT); // initialize PWM1 pin to OUTPUT
    pinMode(PWM2, OUTPUT); // initialize PWM2 pin to OUTPUT

    // Attach ENCA pin interrupt for encoder reading, trigger on rising edge
    attachInterrupt(digitalPinToInterrupt(ENCA), ISR_readEncoder, RISING);

    // Start motor with a small initial PWM to avoid TinkerCAD bug
    analogWrite(PWM2, 10); // turn motor CCW
    delay(1000); // TinkerCAD bug
    analogWrite(PWM1, 10); // turn motor CW
}

// Loop function
void loop()
{
    analogWrite(PWM1, 10); // turn motor CW
    delay(1000); // TinkerCAD bug
    analogWrite(PWM2, 10); // turn motor CCW

    // Check for complete rotation
    if (pos > 2299) { // 2299 ticks is one full rotation
        deg = deg - 359; // 359 degrees is one full rotation
        pos = pos - 2299; // 2299 ticks is one full rotation
    }
    if (pos < 0) { // negative ticks, convert to positive
        deg = 359 + deg; // 359 degrees is one full rotation
        pos = 2299 + pos; // 2299 ticks is one full rotation
    }

    // Get desired position from user input
    degtarget = getInput();
  
  	//Calculate error
    e = degtarget - deg;

    // Control loop until error is zero
    while (e)
    {
        Serial.print("Error value: ");
        Serial.println(e); // print the error value
        Serial.print("\n");

        // Map position to degrees
        deg = map(pos, 0, 2299, 0, 359);

        // Calculate action based on error
        speed = getAction(e);

        // Control motor direction and speed
        // Rotating clockwise
        if(speed >= 0){
        	if (speed > 100) // motor does not react with too low inputs
          	speed = 100; // limit maximum speed
          analogWrite(PWM2, 0); // turn off motor CCW
          analogWrite(PWM1, speed); // turn on motor CW
  	    }
    
        // Rotating counter-clockwise
  	    else{
        	if (-speed > 100) // motor does not react with too low inputs
          	speed = -100; // limit maximum speed
          analogWrite(PWM1, 0); // turn off motor CW
          analogWrite(PWM2, -speed); // turn on motor CCW
        }

        // Update error
        e = degtarget - deg;
    }
  	// Print the error value (should be zero!)
  	Serial.print("Error value: ");
    Serial.println(e); // print the error value
  
  	// Print current position
    Serial.print("The current position (relative) is: ");
    Serial.println(deg); // print the current position in degrees
    Serial.print("\n");
}

// Function to get desired position from user input
int getInput()
{
  	pos=0; // Reset position, since we are starting from a new position
  	deg=0; // Reset degrees, since we are starting from a new position

    int ready = 0; // Flag to check if input is ready
    char buf[8]; // Buffer to store input
    int input = -1; // Desired position

    Serial.print("Please enter the desired position: \n");

    // Wait for serial input
    while (!ready)
    {
        ready = Serial.readBytes(buf, 8); // Read input
        input = atoi(&buf[0]); // Convert input to integer
    }

    return input; // Return desired position
}

// Function to calculate action based on error
int getAction(int error)
{
    // Proportional control: calculate action based on error
    u_out = kp * error;

    // Limit action within acceptable range
    if (u_out > 254) { // limit maximum speed
        return MAX_SPEED; // return maximum speed
    } else if (u_out < -254) { // limit minimum speed
        return -MAX_SPEED; // return minimum speed
    } else { // return calculated speed
        return u_out; // return calculated speed
    }
}

// Interrupt service routine to read encoder signals
void ISR_readEncoder()
{
    // read encoder B signal
    b = digitalRead(ENCB);

    // Update position after trigger on rising edge of A
    b>0 ? pos-- : pos++; // B is high -> CCW, if B is low -> CW
}