
// Select function and call corresponding subroutine
void process_message(char raw_data[], unsigned char fun_code,
                     unsigned int soc[2]){
  char incomming_data[length];
  unsigned int *output_data;
  char sending_function_code;
  int message_length;
  int j;
  for (j=0; j < length; j++){
    incomming_data[j]=raw_data[j];
  }
  if (fun_code == READY){
      // Sends back an acknowledge message.
      sending_function_code = ACK_MSG;
      message_length = 0;
  }
  else if (fun_code == MOVE){
      // Writes to the motors the speed values and direction.
      // After that, sends back an acknowledge message.
      move_robot(incomming_data[0],incomming_data[1]);
      sending_function_code = ACK_MSG;
      message_length = 0;
  }
  else if (fun_code == GET_SOC){
      // Sends the state of charge
      sending_function_code = SOC_MSG;
      message_length = 2;
      output_data = (unsigned int*) malloc(2*sizeof(soc[0]));
      for (j=0; j < message_length; j++){
        output_data[j]=soc[j];
      }
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
void publish_data(char fun_code, int len, unsigned int *data) {
  char partial_len[2];
  int j;
  // Less significative byte.
  partial_len[1] = (char)(len%256);
  // Most significative byte.
  partial_len[0] = (len-partial_len[1]) / 256;
  // Sends through serial port the message bytes.
  Serial.print(stx);
  Serial.print(id_master);
  Serial.print(id_slave);
  Serial.print(partial_len[0]);
  Serial.print(partial_len[1]);
  Serial.print(fun_code);
  for (j=0; j<len;j++){
    Serial.print(data[j]);
  }   
  Serial.print(etx);  
}

//Read State of Charge of the battery
void readSOC(){
  // Writting standar command.
  Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
  // Ask for less significative byte.
  Wire.write(READ_STATE_OF_CHARGE_LOW);
  Wire.endTransmission();
  // Read requested byte.
  Wire.requestFrom(FUEL_GAUGE_I2C_ADDR,1);
  soc[1]= Wire.read();
  // Writting standar command.
  Wire.beginTransmission(FUEL_GAUGE_I2C_ADDR);
  // Ask for more significative byte.
  Wire.write(READ_STATE_OF_CHARGE_HIGH);
  Wire.endTransmission();
  // Read requested byte.
  Wire.requestFrom(FUEL_GAUGE_I2C_ADDR,1);
  soc[0]= Wire.read();
}
