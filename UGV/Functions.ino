
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
      sending_function_code = ACK_MSG;
      break;
    case MOVE:
      move_robot(incomming_data[0],incomming_data[1]);
      sending_function_code = ACK_MSG;
  }
  publish_data(sending_function_code, 0,output_data);
}



// Publish data functions
void publish_data(char fun_code, unsigned long int len, char* data) {
  char partial_len[2];
  partial_len[0]=(char)(len%256);
  partial_len[1]=(char)((len-partial_len[1])/256);
  
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
     
     
      

// Right and left wheels speed control
void move_robot(unsigned char a,unsigned char b)
{
  boolean right_direction;
  boolean left_direction;
  
//  int i = a;
  if (a<128){
    a *= 2;
    a++;
    a = 255 - a;
    right_direction = true;
  }
  else{
    a -= 128;
    a *= 2;
    a++;
    right_direction = false;
    
  }
  if (b<128){
    b *= 2;
    b++;
    b = 255 - b;
    left_direction = true;
  }    
  else{
    b -= 128;
    b *= 2;
    b++;
    left_direction = false;
    
  }
  analogWrite (PIN_PWM_R,a);      
  digitalWrite(PIN_MOT_R, right_direction);    
  analogWrite (PIN_PWM_L,b);    
  digitalWrite(PIN_MOT_L,  left_direction);
}  




      
    

      

        
