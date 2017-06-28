
// Select function and call corresponding subroutine
void process_message(char raw_data[]){
  char incomming_data[length];
  char output_data[length];
  char sending_function_code;
  int message_length;
  for (j=0; j < length; j++){
    incomming_data[j]=raw_data[j];
  }
  switch (fun_code){
    case READY :
      // Sends back an acknowledge message.
      sending_function_code = ACK_MSG;
      message_length = 0;
      break;
    case MOVE:
      // Writes to the motors the speed values and direction.
      // After that, sends back an acknowledge message.
      move_robot(incomming_data[0],incomming_data[1]);
      sending_function_code = ACK_MSG;
      message_length = 0;
      break;
    case GET_SOC:
      // Sends the state of charge
      sending_function_code = SOC_MSG;
      message_length = 2;
      char output_data[message_length];
      for (j=0; j < 2; j++){
        output_data[j]=soc[j];
      }
      break;
  }
  publish_data(sending_function_code, message_length, output_data);
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
void publish_data(char fun_code, int len, char* data) {
  char partial_len[2];
  // Less significative byte.
  partial_len[1] = (char)(len%256);
  // Most significative byte.
  partial_len[0] = 0;
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
  // Low significative byte
  soc[1]= Wire.read();

  Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
  Wire.write(READ_STATE_OF_CHARGE_HIGH);
  Wire.endTransmission();

  Wire.requestFrom(FUEL_GAUGE_I2C_ADDR,1);
  // High significative byte
  soc[0] = Wire.read();  
}
