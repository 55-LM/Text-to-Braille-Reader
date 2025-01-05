#include "Arduino.h"

// Pin Definitions
#define PULLPUSHSOLENOIDLARGE_1_PIN_COIL1	2
#define PULLPUSHSOLENOIDLARGE_2_PIN_COIL1	3
#define PULLPUSHSOLENOIDLARGE_3_PIN_COIL1	4
#define PULLPUSHSOLENOIDLARGE_4_PIN_COIL1	5
#define PULLPUSHSOLENOIDLARGE_5_PIN_COIL1	6
#define PULLPUSHSOLENOIDLARGE_6_PIN_COIL1	7

// Vars for testing
const int timeout = 10000;    // 10 Sec timeout
char menuOption = 0;
long time0;

// Setup 
void setup() 
{
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect
    Serial.println("start");
    
    pinMode(PULLPUSHSOLENOIDLARGE_1_PIN_COIL1, OUTPUT);
    pinMode(PULLPUSHSOLENOIDLARGE_2_PIN_COIL1, OUTPUT);
    pinMode(PULLPUSHSOLENOIDLARGE_3_PIN_COIL1, OUTPUT);
    pinMode(PULLPUSHSOLENOIDLARGE_4_PIN_COIL1, OUTPUT);
    pinMode(PULLPUSHSOLENOIDLARGE_5_PIN_COIL1, OUTPUT);
    pinMode(PULLPUSHSOLENOIDLARGE_6_PIN_COIL1, OUTPUT);
    menuOption = menu();
    
}

// Main logic circuit logic
void loop() 
{ 
    if(menuOption == '1') {
    // Push-Pull Solenoid #1 
    digitalWrite(PULLPUSHSOLENOIDLARGE_1_PIN_COIL1, HIGH); //Turn Solenoid on. 
    delay(1000);  //waits 1000 milliseconds (1 sec). change the value for longer or shorter delay in milliseconds.
    digitalWrite(PULLPUSHSOLENOIDLARGE_1_PIN_COIL1, LOW); //Turn Solenoid off. 
    delay(1000);  //waits 1000 milliseconds (1 sec). change the value for longer or shorter delay in milliseconds.
    }
    else if(menuOption == '2') {
    // Push-Pull Solenoid #2 - Test Code
    digitalWrite(PULLPUSHSOLENOIDLARGE_2_PIN_COIL1, HIGH); //Turn Solenoid on. 
    delay(1000);  //waits 1000 milliseconds (1 sec). change the value for longer or shorter delay in milliseconds.
    digitalWrite(PULLPUSHSOLENOIDLARGE_2_PIN_COIL1, LOW); //Turn Solenoid off. 
    delay(1000);  //waits 1000 milliseconds (1 sec). change the value for longer or shorter delay in milliseconds.
    }
    else if(menuOption == '3') {
    // Push-Pull Solenoid #3 - Test Code
    digitalWrite(PULLPUSHSOLENOIDLARGE_3_PIN_COIL1, HIGH); 
    delay(1000);  
    digitalWrite(PULLPUSHSOLENOIDLARGE_3_PIN_COIL1, LOW);  
    delay(1000);  
    }
    else if(menuOption == '4') {
    // Push-Pull Solenoid #4 - Test Code
    digitalWrite(PULLPUSHSOLENOIDLARGE_4_PIN_COIL1, HIGH); 
    delay(1000);  
    digitalWrite(PULLPUSHSOLENOIDLARGE_4_PIN_COIL1, LOW); 
    delay(1000);  
    }
    else if(menuOption == '5') {
    // Push-Pull Solenoid #5 - Test Code
    digitalWrite(PULLPUSHSOLENOIDLARGE_5_PIN_COIL1, HIGH); 
    delay(1000);  
    digitalWrite(PULLPUSHSOLENOIDLARGE_5_PIN_COIL1, LOW);  
    delay(1000);  
    }
    else if(menuOption == '6') {
    // Push-Pull Solenoid #6 - Test Code
    digitalWrite(PULLPUSHSOLENOIDLARGE_6_PIN_COIL1, HIGH); 
    delay(1000);  
    digitalWrite(PULLPUSHSOLENOIDLARGE_6_PIN_COIL1, LOW); 
    delay(1000);  
    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }  
}

// Menu function for selecting the components to be tested
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) Push-Pull Solenoid #1"));
    Serial.println(F("(2) Push-Pull Solenoid #2"));
    Serial.println(F("(3) Push-Pull Solenoid #3"));
    Serial.println(F("(4) Push-Pull Solenoid #4"));
    Serial.println(F("(5) Push-Pull Solenoid #5"));
    Serial.println(F("(6) Push-Pull Solenoid #6"));
    Serial.println(F("(menu) press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor 
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {  
        if(c == '1') 
    			Serial.println(F("Now Testing Push-Pull Solenoid #1"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing Push-Pull Solenoid #2"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing Push-Pull Solenoid #3"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing Push-Pull Solenoid #4"));
    		else if(c == '5') 
    			Serial.println(F("Now Testing Push-Pull Solenoid #5"));
    		else if(c == '6') 
    			Serial.println(F("Now Testing Push-Pull Solenoid #6"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}