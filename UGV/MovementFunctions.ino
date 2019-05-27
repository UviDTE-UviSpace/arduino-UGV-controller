#include "config.h"

#ifdef LEGOUGV
/*
 * Function in charge of generating the movement of the LEGO UGV
 * 
 * Params: m_accelerate: speed target of the traction engine received from the main controller, values from 0 to 127 are interpreted as 
 *         going backwards and values from 128 to 255 going foward
 *         m_turn: angle target of the servomotor received from the main controller, values from 0 to 127 are interpreted as turning left 
 *         and values from 128 to 255 are interpreted as turning right  
 * 
 * The params are then rescalated to fit all the possible values of the PWM
 */

void move_ugv(unsigned char m_accelerate, unsigned char m_turn){
  
  bool orientation_m;
  bool direction_m;
  //Go backwards
  if (m_accelerate <= 127){
    if (m_accelerate <0){
      m_accelerate = 0;
      }
      m_accelerate = m_accelerate * 2;
      m_accelerate = 255 - m_accelerate;
      direction_m = true;
    }
  //Go foward
  else{
    if (m_accelerate > 255){
      m_accelerate = 255;
      }
      m_accelerate= (m_accelerate * 2) - 255;
      direction_m = false;
      }
  //Turn Left
  if (m_turn <= 127){
      if (m_turn <0){
          m_turn = 255;
      }
      m_turn = m_turn * 2;
      m_turn = 255 - m_turn;
      orientation_m = false;
    }
  //Turn Right  
  else{
    if (m_turn > 255){
      m_turn = 255;
      }
      m_turn= (m_turn * 2) - 255;
      orientation_m = true;
    }
  
  digitalWrite(servomotorLeftRight,orientation_m);
  analogWrite(servoPWM,m_turn);
  digitalWrite(TractDirectionControl,direction_m);
  analogWrite(TractSpeedControl,m_accelerate);
}
#else

/*
  Function: move_ugv
  --------------------

  Right and left wheels speed control.
  Values from 0 to 127 are interpreted as reverse direction.
  Values from 128 to 255 are interpreted as direct direction.

  Once the direction is checked, the output has to be rescaled
  to [0..255], as it is the full range of the output.
*/
void move_ugv(unsigned char m_right, unsigned char m_left)
{
  boolean right_direction;
  boolean left_direction;
  // Reverse direction
  if (m_right < 128){
    if (m_right < 0){
      m_right = 0;
    }
    m_right *= 2;
    m_right++;
    m_right = 255 - m_right;
    right_direction = true;
  }
  // Direct direction
  else{
    if (m_right > 255){
      m_right = 255;
    }
    m_right -= 128;
    m_right *= 2;
    m_right++;
    right_direction = false;

  }
  if (m_left < 128){
    if (m_left < 0){
      m_left = 0;
    }
    m_left *= 2;
    m_left++;
    m_left = 255 - m_left;
    left_direction = true;
  }
  else{
    if (m_left > 255){
      m_left = 255;
    }
    m_left -= 128;
    m_left *= 2;
    m_left++;
    left_direction = false;
  }
  // Send the values to the corresponding pins.
  analogWrite (PIN_PWM_R, m_right);
  digitalWrite(PIN_MOT_R, right_direction);
  analogWrite (PIN_PWM_L, m_left);
  digitalWrite(PIN_MOT_L, left_direction);
}

#endif
/*
 * Function for stop the movement of the movement of the UGV
 * (Not used at the moment)
 */
void stop_m(){
  analogWrite (5, 0);
  digitalWrite(7, false);
  analogWrite (6, 0);
  digitalWrite(4, false);
  }
/*
 * Function to initialize the motor settings 
 */
  
void setup_motors(){
  
  pinMode(TractSpeedControl, OUTPUT);
  pinMode(TractDirectionControl, OUTPUT);
  pinMode(servomotorLeftRight, OUTPUT);
  pinMode(servoPWM, OUTPUT);
  
  pinMode(PIN_PWM_R, OUTPUT);
  pinMode(PIN_PWM_L, OUTPUT);
  pinMode(PIN_MOT_R, OUTPUT);
  pinMode(PIN_MOT_L, OUTPUT);
  
  }
