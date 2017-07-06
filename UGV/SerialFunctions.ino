
// Select function and call corresponding subroutine
void process_message(char raw_data[], unsigned char fun_code ){
  char incomming_data[length];
  char *output_data;
  char sending_function_code;
  int message_length;
  int j;
  int k;
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
	sending_function_code = SOC_MSG;
	message_length = 4;
    output_data = get_bat_param(soc);
  }
  else if (fun_code == GET_V){
    sending_function_code = V_MSG;
    message_length = 4;
    output_data = get_bat_param(voltage);
  }
  else if (fun_code == GET_R_CAP){
    sending_function_code = R_CAP_MSG;
    message_length = 4;
    output_data = get_bat_param(remaining_capacity);
  }
  else if (fun_code == GET_TEMP){
    sending_function_code = TEMP_MSG;
    message_length = 4;
    output_data = get_bat_param(temperature);
  }
  else if (fun_code == GET_CURR){
    sending_function_code = CURR_MSG;
    message_length = 4;
    output_data = get_bat_param(current);
  }
  publish_data(sending_function_code, message_length, &output_data[0]);
}

/*
 * Function: move_robot
 * --------------------
 *
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
void publish_data(char fun_code, int len, char *data) {
  char partial_len[2];
  int j;
  // Less significative byte.
  partial_len[1] = (char) len;
  // Most significative byte.
  partial_len[0] = (char) (len >> 8);
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

char *get_bat_param(unsigned int parameter[]){
      char *output_data;
	  output_data = (char*) malloc(2*sizeof(unsigned int));
      int k = 0;
      // Each parameter element has 2 bytes, thus each one has to be written
      // on 2 chars.
      for (j=0; j < 2; j++){
        output_data[k] = 0xFF00 & parameter[j] >> 8;
        output_data[k+1] = 0x00FF & parameter[j];
        k += 2;
      }
	return output_data;
}

