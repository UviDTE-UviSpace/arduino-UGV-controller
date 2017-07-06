// Read State of Charge of the battery.
void ReadBatParam(unsigned char I2C_Command_Low, unsigned char I2C_Command_High,
                            boolean subcommand, unsigned int *parameter){
  if (subcommand == true){
    // Writting Fuel Gauge Address.
    Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
    // Writting I2C subcommand.
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


