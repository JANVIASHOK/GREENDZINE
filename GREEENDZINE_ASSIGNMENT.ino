/*
NAME: JANVI ASHOK K V
DATE: 11/03/2024
DESCRIPTION: Firmware assignment
*/

#include <Arduino.h>
#include <TimerOne.h>

// Defining temperature sensor pin to A0
#define LM35 A0

// Defining onboard LED pin
#define LEDPIN 13

// Variables to store temperature and blink interval
volatile float temperature_celsius;
volatile int blink_interval;

// Function declarations
void check_temperature();
void blink_led();

void setup() 
{
    // Initializing baud rate for serial communication
    Serial.begin(9600);

    // Setting LED pin as output
    pinMode(LEDPIN, OUTPUT);

    // Initializing Timer1 to trigger every 1 millisecond
    Timer1.initialize(1000); 
    Timer1.attachInterrupt(check_temperature); // Attaching check_temperature() function to Timer1 interrupts

    // Start the sTimer1
    Timer1.start();
}

void loop() 
{
    // Empty loop as all tasks are handled by interrupts
}

void check_temperature() 
{
    // Reading the voltage from the LM35 temperature sensor
    int sensor_value = analogRead(LM35);

    // Converting the analog reading from LM35 temperature sensor to degree celsius
    temperature_celsius = (sensor_value * 5.0 / 1024.0) * 100.0; 

    // Printing the temperature to serial monitor
    Serial.print("Temperature: ");
    Serial.print(temperature_celsius);
    Serial.println(" C");

    // Checking if temperature is below 30 degrees Celsius
    if (temperature_celsius < 30) 
    {
        // If condition is true, set blink interval to 250 milliseconds
        blink_interval = 250; 
    } 
    else 
    {
        // Set blink interval to 500 milliseconds
        blink_interval = 500; 
    }

    // Call blinkLED function after blinkInterval and converting milliseconds to microseconds
    Timer1.attachInterrupt(blink_led, blink_interval * 1000); 
}

void blink_led() 
{
    // Toggle the LED state
    digitalWrite(LEDPIN, !digitalRead(LEDPIN));
}
