void readRemainingCapacity(){
  Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
  Wire.write(READ_REMAINING_CAPACITY_LOW);
  Wire.endTransmission();

  Wire.requestFrom(FUEL_GAUGE_I2C_ADDR,1);

  remaining_capacity_low = Wire.read();

  Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
  Wire.write(READ_REMAINING_CAPACITY_HIGH);
  Wire.endTransmission();

  Wire.requestFrom(FUEL_GAUGE_I2C_ADDR,1);

  remaining_capacity_high = Wire.read();

  unsigned int remaining_capacity_high1 = remaining_capacity_high << 8;

  remaining_capacity = remaining_capacity_high1 + remaining_capacity_low;
}

void readVoltage(){
  Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
  Wire.write(READ_VOLTAGE_LOW);
  Wire.endTransmission();

  Wire.requestFrom(FUEL_GAUGE_I2C_ADDR,1);

  voltage_low = Wire.read();

  Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
  Wire.write(READ_VOLTAGE_HIGH);
  Wire.endTransmission();

  Wire.requestFrom(FUEL_GAUGE_I2C_ADDR,1);

  voltage_high = Wire.read();

  //unsigned int voltage_high1 = voltage_high << 8;

  voltage = voltage_high + voltage_low;
}

void readCurrent(){
  Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
  Wire.write(READ_CONTROL_LOW);
  Wire.endTransmission();

  Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
  Wire.write(READ_CURRENT_LOW);
  Wire.endTransmission();
  

  Wire.requestFrom(FUEL_GAUGE_I2C_ADDR,1);

  current_low = Wire.read();

  Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
  Wire.write(READ_CONTROL_HIGH);
  Wire.endTransmission();

  Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
  Wire.write(READ_CURRENT_HIGH);
  Wire.endTransmission();
  

  Wire.requestFrom(FUEL_GAUGE_I2C_ADDR,1);

  current_high = Wire.read();
  
  unsigned int current_high1 = current_high << 8;

  current = current_high1 + current_low;  
}

 void readTemperature(){
   Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);        //writting standar command
   Wire.write(READ_TEMPERATURE_LOW);
   Wire.endTransmission();
   Wire.requestFrom(FUEL_GAUGE_I2C_ADDR,1);            //taking its value

   temperature_low = Wire.read();

   Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
   Wire.write(READ_TEMPERATURE_HIGH);
   Wire.endTransmission();

   Wire.requestFrom(FUEL_GAUGE_I2C_ADDR,1);
  
   temperature_high = Wire.read();

   unsigned int temperature_high1 = temperature_high << 8;

   temperature = temperature_high1 + temperature_low;

   temperature = 0.1 * temperature;
   temperature = temperature - 273.15;
 }

