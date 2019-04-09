
// Select function and call corresponding subroutine
void process_message(char raw_data[], unsigned char fun_code, unsigned long int length_msg){
  char incomming_data[length_msg];
  char* output_data;
  char sending_function_code;
  int data_length;
  int j;
  int k;
  for (j=0; j<length_msg; j++){
    incomming_data[j] = raw_data[j];
  }
  if (fun_code == READY){
    // Sends back an acknowledge message.
    sending_function_code = ACK_MSG;
    data_length = 0;
  }
  else if (fun_code == MOVE){
    // Writes to the motors the speed values and direction.
    // After that, sends back an acknowledge message.
    move_ugv(incomming_data[0],incomming_data[1]);
    sending_function_code = ACK_MSG;
    data_length = 0;
  }
  else if (fun_code == GET_SOC){
    if (I2C_state == false){
      sending_function_code = BAT_ERR;
      data_length = 0;
    }
    else{
      sending_function_code = SOC_MSG;
      data_length = 1;
      output_data = (char*)(&soc);
    }
  }
  else if (fun_code == GET_V){
    if (I2C_state == false){
      sending_function_code = BAT_ERR;
      data_length = 0;
    }
    else{
      sending_function_code = V_MSG;
      data_length = 2;
      output_data = (char*)(&voltage);
    }
  }
  else if (fun_code == GET_R_CAP){
    if (I2C_state == false){
      sending_function_code = BAT_ERR;
      data_length = 0;
    }
    else{
      sending_function_code = R_CAP_MSG;
      data_length = 2;
      output_data = (char*)(&remaining_capacity);
    }
  }
  else if (fun_code == GET_TEMP){
    if (I2C_state == false){
      sending_function_code = BAT_ERR;
      data_length = 0;
    }
    else{
      sending_function_code = TEMP_MSG;
      data_length = 2;
      output_data = (char*)(&temperature);
    }
  }
  else if (fun_code == GET_CURR){
    if (I2C_state == false){
      sending_function_code = BAT_ERR;
      data_length = 0;
    }
    else{
      sending_function_code = CURR_MSG;
      data_length = 2;
      output_data = (char*)(&current);
    }
  }
  publish_data(sending_function_code, data_length, output_data);
}



// Publish data functions
void publish_data(char fun_code, int len, char *data) {
  char partial_len[2];
  char id_slave = ID_SLAVE;
  char id_master = ID_MASTER;
  char etx = ETX;
  char stx = STX;
  int j;
  // Less significative byte.
  partial_len[1] = (char)len;
  // Most significative byte.
  partial_len[0] = (char)(len >> 8);
  // Sends through serial port the message bytes.
  Serial.print(stx);
  Serial.print(id_master);
  Serial.print(id_slave);
  Serial.print(partial_len[0]);
  Serial.print(partial_len[1]);
  Serial.print(fun_code);
  for (j=0; j<len; j++){
    Serial.print(data[j]);
  }
  Serial.print(etx);
}
