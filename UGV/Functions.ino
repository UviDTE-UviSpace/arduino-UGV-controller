
// Select function and call corresponding subroutine
void process_message(char raw_data[]){
  char incomming_data[length];
  char output_data[length];
  char sending_function_code;
  for (j=0; j < length; j++){
    incomming_data[j]=raw_data[j];
  }
  switch (fun_code){
    case READY :
      // Sends back an acknowledge message.
      sending_function_code = ACK_MSG;
      break;
    case MOVE:
      // Writes to the motors the speed values and direction.
      // After that, sends back an acknowledge message.
      move_robot(incomming_data[0],incomming_data[1]);
      sending_function_code = ACK_MSG;
      break;
  }
  publish_data(sending_function_code, 0,output_data);
}


/*
 * Function: move_robot
 * --------------------
 * Right and left wheels speed control.
 * Values from 0 to 127 are interpreted as reverse direction.
 * Values from 128 to 255 are interpreted as direct direction.
 *
 * Once the direction is checked, the output has to be rescaled 
 * to [0..255], as it is the full range of the output.
*/
void move_robot(unsigned char a,unsigned char b)
{
  boolean right_direction;
  boolean left_direction;
  // Reverse direction
  if (a<128){
    if (a<0){
      a = 0;
    }
    a *= 2;
    a++;
    a = 255 - a;
    right_direction = true;
  }
  // Direct direction
  else{
    if (a>255){
      a = 255;
    }
    a -= 128;
    a *= 2;
    a++;
    right_direction = false;
    
  }
  if (b<128){
    if (b<0){
      b = 0;
    }      
    b *= 2;
    b++;
    b = 255 - b;
    left_direction = true;
  }    
  else{
    if (b>255){
      b = 255;
    }
    b -= 128;
    b *= 2;
    b++;
    left_direction = false;
  }
  // Send the values to the corresponding pins.
  analogWrite (PIN_PWM_R,a);      
  digitalWrite(PIN_MOT_R, right_direction);    
  analogWrite (PIN_PWM_L,b);    
  digitalWrite(PIN_MOT_L,  left_direction);
}  


// Publish data functions
void publish_data(char fun_code, unsigned long int len, char* data) {
  char partial_len[2];
  partial_len[0]=(char)(len%256);
  partial_len[1]=(char)((len-partial_len[1])/256);
  // Sends through serial port the message bytes.
  Serial.print(stx);
  Serial.print(id_master);
  Serial.print(id_slave);
  Serial.print(partial_len[0]);
  Serial.print(partial_len[1]);
  Serial.print(fun_code);
  for (unsigned long int j=0; j<len;j++){
    Serial.print(data[j]);
  }   
  Serial.print(etx);  
}

//Read State of Charge of the battery
void readSOC(){
  Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);        //writting standar command
  Wire.write(READ_STATE_OF_CHARGE_LOW);
  Wire.endTransmission();

  Wire.requestFrom(FUEL_GAUGE_I2C_ADDR,1);            //taking its value

  soc_low = Wire.read();

  Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
  Wire.write(READ_STATE_OF_CHARGE_HIGH);
  Wire.endTransmission();

  Wire.requestFrom(FUEL_GAUGE_I2C_ADDR,1);

  soc_high = Wire.read();
  
  //unsigned int soc_high1 = soc_high << 8;

  soc = soc_high + soc_low;
  
  Serial.print("Battery State of Charge is ");
  Serial.print(soc);
  Serial.print(" %.");
  Serial.print("\r\n");
}

//void readRemainingCapacity(){
//  Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
//  Wire.write(READ_REMAINING_CAPACITY_LOW);
//  Wire.endTransmission();
//
//  Wire.requestFrom(FUEL_GAUGE_I2C_ADDR,1);
//
//  remaining_capacity_low = Wire.read();
//
//  Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
//  Wire.write(READ_REMAINING_CAPACITY_HIGH);
//  Wire.endTransmission();
//
//  Wire.requestFrom(FUEL_GAUGE_I2C_ADDR,1);
//
//  remaining_capacity_high = Wire.read();
//
//  unsigned int remaining_capacity_high1 = remaining_capacity_high << 8;
//
//  remaining_capacity = remaining_capacity_high1 + remaining_capacity_low;
//}

//void readVoltage(){
//  Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
//  Wire.write(READ_VOLTAGE_LOW);
//  Wire.endTransmission();
//
//  Wire.requestFrom(FUEL_GAUGE_I2C_ADDR,1);
//
//  voltage_low = Wire.read();
//
//  Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
//  Wire.write(READ_VOLTAGE_HIGH);
//  Wire.endTransmission();
//
//  Wire.requestFrom(FUEL_GAUGE_I2C_ADDR,1);
//
//  voltage_high = Wire.read();
//
//  //unsigned int voltage_high1 = voltage_high << 8;
//
//  voltage = voltage_high + voltage_low;
//}

//void readCurrent(){
//  Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
//  Wire.write(READ_CONTROL_LOW);
//  Wire.endTransmission();
//
//  Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
//  Wire.write(READ_CURRENT_LOW);
//  Wire.endTransmission();
//  
//
//  Wire.requestFrom(FUEL_GAUGE_I2C_ADDR,1);
//
//  current_low = Wire.read();
//
//  Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
//  Wire.write(READ_CONTROL_HIGH);
//  Wire.endTransmission();
//
//  Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
//  Wire.write(READ_CURRENT_HIGH);
//  Wire.endTransmission();
//  
//
//  Wire.requestFrom(FUEL_GAUGE_I2C_ADDR,1);
//
//  current_high = Wire.read();
//  
//  unsigned int current_high1 = current_high << 8;
//
//  current = current_high1 + current_low;  
//}

// void readTemperature(){
  // Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);        //writting standar command
  // Wire.write(READ_TEMPERATURE_LOW);
  // Wire.endTransmission();

  // Wire.requestFrom(FUEL_GAUGE_I2C_ADDR,1);            //taking its value

  // temperature_low = Wire.read();

  // Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
  // Wire.write(READ_TEMPERATURE_HIGH);
  // Wire.endTransmission();

  // Wire.requestFrom(FUEL_GAUGE_I2C_ADDR,1);

  // temperature_high = Wire.read();

  // unsigned int temperature_high1 = temperature_high << 8;

  // temperature = temperature_high1 + temperature_low;

  // temperature = 0.1 * temperature;
  // temperature = temperature - 273.15;
// }


