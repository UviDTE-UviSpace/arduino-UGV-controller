// Serial port configuration
#define BAUD_RATE    57600

// Motors parameters
#define PIN_PWM_R        5 // Speed control of right motor
#define PIN_PWM_L        6 // Speed control of left motor
#define PIN_MOT_R        4 // Direction control of right motor
#define PIN_MOT_L        7 // Direction control of left motor

/*
 * Traction Engine
 */
#define TractSpeedControl  5 //Pin number 5 generates the PWM which controls the speed of the vehicle
#define TractDirectionControl  4 //Pin number 4 controls the direction High -> Foward, Low -> Backwards !!!!!!!!!!!!!!! Revisar 
 
/*
 * Servomotor
 */
#define servomotorLeftRight  7       //Pin number 7 controls the direction of the turn Low -> Left, High -> Right   !!!!!!!!!!!!!!! Revisar 
#define servoPWM           6       //Pin number 6 controls the angle of turn (if it's set to 0 it will go to the central position)   


#define MIN_PWM         58 // PWM minimum value
#define MAX_PWM        255 // PWM maximum value

// Debug LED
#define PIN_LED			 13

// Warning LED
#define WRNG_LED     10

// Power hold
#define PWR_HOLD     12

// Comm protocol constants
#define ID_SLAVE  	  0x01
#define ID_MASTER  	  0x01
#define STX    		  0x02
#define ETX      	  0x03

// Function codes from PC
#define READY   	  0X04
#define MOVE  		  0X05
#define GET_SOC  	  0X06
#define GET_V		  0X07
#define GET_R_CAP	  0X08
#define GET_TEMP	  0X09
#define GET_CURR	  0X0A

// Function codes from RoMeo
#define ACK_MSG   0X01
#define SOC_MSG   0x02
#define V_MSG	  0X03
#define R_CAP_MSG 0X04
#define TEMP_MSG  0X05
#define CURR_MSG  0X06
#define BAT_ERR   0x07

// I2C address (B1010101)
#define FUEL_GAUGE_I2C_ADDR           0x55

// I2C commands
#define READ_CONTROL_LOW              0X00
#define READ_CONTROL_HIGH             0X01
#define READ_STATE_OF_CHARGE          0x02
#define READ_MAX_ERROR                0x03
#define READ_CAPACITY_LOW             0X04
#define READ_CAPACITY_HIGH            0X05
#define READ_VOLTAGE_LOW              0X08
#define READ_VOLTAGE_HIGH             0X09
#define READ_TEMPERATURE_LOW          0X0c
#define READ_TEMPERATURE_HIGH         0X0d
#define READ_CURRENT_LOW              0X10
#define READ_CURRENT_HIGH             0X11
