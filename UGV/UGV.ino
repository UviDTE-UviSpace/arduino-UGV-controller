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
 * move_ugv: This function receives 2 bytes of data, 1 for each motor.
 It resizes the bytes and  obtains the direction and module of the
 motors' speeds.
*/
// I2C Library
#include <Wire.h>
// Robot control program and parameters
#include "BoardParams.h"


void setup(void) {
  // Arduino mantains board power throw the relay
  digitalWrite(PWR_HOLD, HIGH);
  //Motors
  setup_motors();
  // Debug LED.
  pinMode(PIN_LED, OUTPUT);
  // Warning LED.
  pinMode(WRNG_LED, OUTPUT);
  // Power hold signal
  pinMode(PWR_HOLD, OUTPUT);
  Serial.begin(BAUD_RATE);
  // Joing I2C bus.
  Wire.begin();
  delay(400);
}

// Auxiliar subroutines declaration
void move_ugv(unsigned char a,unsigned char b);
void process_message(char raw_data[]);
void publish_data(char fun_code, unsigned long int len, char* data);

// Iterations counter
unsigned int it_counter = 0;

// Pushbutton
#define SW2 7
int val = 0;

// I2C function variables
unsigned char soc;
unsigned int voltage;
unsigned int remaining_capacity;
unsigned int temperature;
unsigned int current;
boolean I2C_state;


// Main loop (communications)
void loop(void)
{
  // Variables definition
  unsigned long int length_msg;
  unsigned char fun_code;
  char id_slave = ID_SLAVE;
  char id_master = ID_MASTER;
  char etx = ETX;
  char stx = STX;
  char buffer_msg[30];
  int j;

  // LED indicates that board is waiting for transmission
  digitalWrite(PIN_LED, HIGH);
  
  // Test the WRNG_LED wirings
//  digitalWrite(WRNG_LED, HIGH);
//  digitalWrite(PWR_HOLD, HIGH);
  //testing switch
//  val = analogRead (SW2);
//  if (val < 160){
//    Serial.println("Robot die");
//  }
//  Serial.println(val);

  // Switch off the UGV if Arduino Romeo Switch2 is pressed 
  val = analogRead (SW2);
  if ((val < 160) && (val > 50)){
    digitalWrite(PWR_HOLD, LOW);
    //Serial.println("Robot die");
  }

  // Listen serial port 
  if (Serial.available())
  {
    digitalWrite(PIN_LED, LOW);
    buffer_msg[0] = Serial.read();
    if (buffer_msg[0]==stx)
    {
      for (j=1; j < 6; j++)
      {
        while (! Serial.available()) {}
        buffer_msg[j] = Serial.read();
      }
      id_slave= buffer_msg[1];
      id_master= buffer_msg[2];
      fun_code = buffer_msg[5];
      length_msg = 256*((long int)buffer_msg[4])+((long int)buffer_msg[3]);
      char data[length_msg];
      for (j=6; j < length_msg+6; j++)
      {
        while (! Serial.available()) {}
        buffer_msg[j] = Serial.read();
        data[j-6] = buffer_msg[j];
      }
      while (! Serial.available()) {}
      buffer_msg[length_msg+6] = Serial.read();
      if (buffer_msg[length_msg+6]==ETX)
      {
        Serial.flush();
        process_message(data, fun_code, length_msg);
      }
    }
  }  
  
  /* In each different iteration cycle, a different parameter is
  required in order to space operations over time and reduce the
  cycle time*/
  if (it_counter == 0){
    I2C_state = ReadBatParam1(READ_STATE_OF_CHARGE, &soc ) ;
    //check if the SOC level is in range. If true, put on the corresponding PWR_HOLD signal
    //Serial.println(soc);
  }
  else if (it_counter == 1){
    I2C_state = ReadBatParam2(READ_VOLTAGE_LOW, READ_VOLTAGE_HIGH, &voltage);
  }
  else if (it_counter == 2){
    I2C_state = ReadBatParam2(READ_CAPACITY_LOW, READ_CAPACITY_HIGH, &remaining_capacity);
  }
  else if (it_counter == 3){
    I2C_state = ReadBatParam2(READ_TEMPERATURE_LOW, READ_TEMPERATURE_HIGH, &temperature);
  }
  else if (it_counter == 4){
    I2C_state = ReadBatParam2(READ_CURRENT_LOW, READ_CURRENT_HIGH, &current);
  }
  it_counter ++;
  if (it_counter == 5){
    it_counter = 0;
  }
}
