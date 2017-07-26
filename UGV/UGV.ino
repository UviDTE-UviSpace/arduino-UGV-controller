/* 
 UGV program, from UviSpace project for Arduino RoMeo

 Sets the board as a slave and enables communications through serial
 port. Move the motors according to the master's orders

 Components:
 * Serial port: Communication based on the protocol SerMesProtocol
specified in the docs. The program has been tested using XBEE protocol
(IEEE 802.15.4 based).
 * I2C wires: These port allows to communicate with external devices
 using the I2C protocol. It uses 2 wires, one for the clock
 synchronization signal and the other one for sending serial data.
 * Outputs: 2 Motors conected to pins 4-5 and 6-7 respectively.
 The first pin is for power control and the second one is for direction
 control.
  
 Subroutines and functions:
 * loop: main function of the program. The board will be constantly
 listening for incoming messages on the serial port. When a message is
 received, its validity is checked and data is extracted. Finally, the
 data is passed to the process_message() function.
 * process_message: Function which takes the processed data and
 analyzes it, deciding which function to call afterwards, and passing it
 the necessary values. Finally, after the action is completed, it calls
 publish_data.
 * publish_data: Function which answers the master request through the
 serial port.
 * move_robot: This function receives 2 bytes of data, 1 for each motor.
 It resizes the bytes and  obtains the direction and module of the
 motors' speeds.
*/
// I2C Library
#include <Wire.h>
// Robot control program and parameters
#include "BoardParams.h"


void setup(void) { 
  // Motor pins.
  pinMode(PIN_PWM_R, OUTPUT);
  pinMode(PIN_PWM_L, OUTPUT);
  pinMode(PIN_MOT_R, OUTPUT);
  pinMode(PIN_MOT_L, OUTPUT);
  // Debug LED.
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(BAUD_RATE);
  // Joing I2C bus.
  Wire.begin();
  delay(400);
}

// Auxiliar subroutines declaration
void move_robot(unsigned char a,unsigned char b);
void process_message(char raw_data[]);
void publish_data(char fun_code, unsigned long int len, char* data);

// Iterations counter
unsigned int it_counter = 0;

// I2C function variables
unsigned int soc[2];
unsigned int voltage[2];
unsigned int remaining_capacity[2];
unsigned int temperature[2];
unsigned int current[2];
boolean I2C_state;


// Main loop (communications)
void loop(void) 
{
  // Variables definition
  unsigned long int length;
  unsigned char fun_code;
  char id_slave = ID_SLAVE;
  char id_master = ID_MASTER;
  char etx = ETX;
  char stx = STX;
  char buffer[30];
  int j;
  
  // LED indicates that board is waiting for transmission
  digitalWrite(PIN_LED, HIGH);
  if (Serial.available())
  {
    digitalWrite(PIN_LED, LOW);
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
        process_message(data, fun_code, length);
      }
    }
  }
  /* In each different iteration cycle, a different parameter is
  required in order to space operations over time and reduce the
  cycle time*/
  if (it_counter == 0){
    I2C_state = ReadBatParam(READ_STATE_OF_CHARGE_LOW, READ_STATE_OF_CHARGE_HIGH,
                 false, &soc[0]);
    if (I2C_state == true){
      it_counter ++;
    }
  }
  else if (it_counter == 1){
    it_counter ++;
    ReadBatParam(READ_VOLTAGE_LOW, READ_VOLTAGE_HIGH,
                 false, &voltage[0]);
  }
  else if (it_counter == 2){
    it_counter ++;
    ReadBatParam(READ_CAPACITY_LOW, READ_CAPACITY_HIGH,
                 false, &remaining_capacity[0]);
  }
  else if (it_counter == 3){
    it_counter ++;
    ReadBatParam(READ_TEMPERATURE_LOW, READ_TEMPERATURE_HIGH,
                 false, &temperature[0]);
  }
  else if (it_counter == 4){
    it_counter = 0;
    ReadBatParam(READ_CURRENT_LOW, READ_CURRENT_HIGH,
                 true, &current[0]);
  }
}
