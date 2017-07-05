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

// Function that gets the State Of Charge of the battery.
void getSOC() {
boolean subcommand = false;
ReadBatParam(READ_STATE_OF_CHARGE_LOW,
             READ_STATE_OF_CHARGE_HIGH, subcommand, &soc[0]);
}

// Function that gets the voltage of the battery.
void getVoltage() {
boolean subcommand = false;
ReadBatParam(READ_VOLTAGE_LOW, READ_VOLTAGE_HIGH, subcommand, &voltage[0]);
}

// Function that gets the remaining capacity of the battery.
void getRemainingCapacity() {
boolean subcommand = false;
ReadBatParam(READ_REMAINING_CAPACITY_LOW, READ_REMAINING_CAPACITY_HIGH,
             subcommand, &remaining_capacity[0]);
}

// Function that gets the temperature of the battery.
void getTemperature() {
boolean subcommand = false;
ReadBatParam(READ_TEMPERATURE_LOW, READ_TEMPERATURE_HIGH, 
                           subcommand, &temperature[0]);
}

// Function that gets the instant current of the battery.
void getCurrent() {
boolean subcommand = true;
ReadBatParam(READ_CURRENT_LOW, READ_CURRENT_HIGH, subcommand, &current[0]);
}
