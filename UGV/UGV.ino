/* 
 UGV(v2.1) program, from the Smart Sensors project for Arduino RoMeo 
 Sets the board as a slave and enables communications through serial port. Move the motors
 according to the master's orders 
 
 Components:
 * Serial port: Communication is based on the protocol SerMesProtocol specified in the doc.
 The program was tested using ZigBee protocol (IEEE 802.15.4 based)
 * Outputs: 2 Motors conected to pins 4-5 and 6-7 respectively. First pin for power control
 and second pin for direction control 
  
 Subroutines and functions:
 * loop: main function of the program. The board will be constantly hearing for incoming messages
 on serial port. When a message is received, its validity is checked and data is extracted. Finally, 
 the data is passed to process_message() function
 * process_message: Function which takes the processed data and analyzes it, deciding which function
 to call afterwards, and passing it the necessary values. Finally, after the action is completed, it
 calls publish_data
 * publish_data: Function which answers the master through the serial port. 
 * move_robot: This function receives 2 bytes of data, 1 for each motor. It resizes the bytes and 
 obtains the direction and module of the motors' speed

 This version was created 20th September 2016
 Author: Javier Lopez Randulfe
 company: Universidade de Vigo
 email: javier.randulfe@uvigo.es
*/

// Robot control program and parameters:
#include "BoardParams.h"

// I2C Library
#include <Wire.h> 

void setup(void) { 
  // Motor pins:
  pinMode(PIN_PWM_R, OUTPUT);
  pinMode(PIN_PWM_L, OUTPUT);
  pinMode(PIN_MOT_R, OUTPUT);
  pinMode(PIN_MOT_L, OUTPUT);
  // Debug LED:
  pinMode(13, OUTPUT);      
  Serial.begin(BAUD_RATE);    // Set Baud Rate
  
  Wire.begin();			 	        // Join I2C bus
    
}

// Auxiliar subroutines declaration
void move_robot(unsigned char a,unsigned char b);
void process_message(char raw_data[]);
void publish_data(char fun_code, unsigned long int len, char* data);
void readSOC();

// Variables definition
unsigned long int j = 0;
char buffer[30];
char id_slave = ID_SLAVE;
char id_master = ID_MASTER;
unsigned long int length; 
unsigned char fun_code;

char etx = ETX;
char stx = STX;

// I2C function variables
unsigned int soc[2];
unsigned int remaining_capacity_low, remaining_capacity_high;
unsigned int voltage_low, voltage_high;
unsigned int current_low, current_high;
unsigned int temperature_low, temperature_high;


// Main loop (communications)
void loop(void) 
{
  // LED indicates board waiting for transmission
  digitalWrite(13, HIGH);
  if (Serial.available()) 
  {
    digitalWrite(13, LOW);
    buffer[0] = Serial.read();
    if (buffer[0]==stx)
    {
      for (j=1; j < 6; j++)
      {
        while (! Serial.available()) {}
        buffer[j] = Serial.read();
      }
      id_slave= buffer[1];
      id_master= buffer[2];
      fun_code = buffer[5];
      length = 256*((long int)buffer[4])+((long int)buffer[3]); 
      char data[length];
      for (j=6; j < length+6; j++)
      {
        while (! Serial.available()) {}
        buffer[j] = Serial.read();
        data[j-6] = buffer[j];
      }
      while (! Serial.available()) {}
      buffer[length+6] = Serial.read();
      if (buffer[length+6]==ETX)
      {       
        Serial.flush();
        process_message(data, fun_code, soc);
      }  
    }
  }
  readSOC();
}
