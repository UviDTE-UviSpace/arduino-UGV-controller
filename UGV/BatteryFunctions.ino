/*
  This script contains the ReadBatParam function, which has 4 parameters
  
  - I2C_Command_Low: It is the low byte of the I2C command for
  communicating with the board.
  - I2C_Command_High: It is the high byte of the I2C command for
  communicating with the board.  
  The two first parameters are variables that take the value of
  constants defined in the script BoardParams.h.
  - subcommand: It is a boolean. It only indicates if the battery
  parameter required is the current. The current parameter in the PCB
  is accessed by using subcommands. It is the only parameter that
  UviSpace uses that has to deal with subcommands.
  - *parameter: pointer dereference (*). The function call argument
  assigned to this one has to be a pointer reference (&).That has to be
  done in this way because in C language a function can not return an
  array of data. Instead of doing that, if you work inside the function
  with a pointer, that information is stored properly and you can get it
  outside the function.
*/
void ReadBatParam(unsigned char I2C_Command_Low, unsigned char I2C_Command_High,
                  boolean subcommand, unsigned int *parameter){
  if (subcommand == true){
    // Write Fuel Gauge Address.
    Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
    // Write I2C subcommand.
    Wire.write(READ_CONTROL_LOW);
    Wire.endTransmission();
  }
  // Write Fuel Gauge Address.
  Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
  // Ask for less significative byte.
  Wire.write(I2C_Command_Low);
  Wire.endTransmission();
  // Read requested byte.
  Wire.requestFrom(FUEL_GAUGE_I2C_ADDR, 1);
  parameter[1]= (unsigned int) Wire.read();

  if (subcommand == true){
    // Write Fuel Gauge Address.
    Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
    // Write I2C subcommand.
    Wire.write(READ_CONTROL_HIGH);
    Wire.endTransmission();
  }
  // Write Fuel Gauge Address
  Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
  // Ask for more significative byte.
  Wire.write(I2C_Command_High);
  Wire.endTransmission();
  // Read requested byte.
  Wire.requestFrom(FUEL_GAUGE_I2C_ADDR, 1);
  parameter[0]= (unsigned int) Wire.read();
}


