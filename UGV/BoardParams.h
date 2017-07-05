// Serial port configuration
#define BAUD_RATE    57600

// Motors parameters
#define PIN_PWM_R        5 // Speed control of right motor
#define PIN_PWM_L        6 // Speed control of left motor
#define PIN_MOT_R        4 // Direction control of right motor
#define PIN_MOT_L        7 // Direction control of left motor

#define MIN_PWM         58 // PWM minimum value
#define MAX_PWM        255 // PWM maximum value

// Fuel gauge pins
#define PIN_ALERT        8 // Fuel gauge negated alert pin.

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

// I2C address
#define FUEL_GAUGE_I2C_ADDR           0x55 // B1010101

// I2C commands
#define READ_CONTROL_LOW              0X00
#define READ_CONTROL_HIGH             0X01
#define READ_STATE_OF_CHARGE_LOW      0x02
#define READ_STATE_OF_CHARGE_HIGH     0x03
#define READ_REMAINING_CAPACITY_LOW   0X04
#define READ_REMAINING_CAPACITY_HIGH  0X05
#define READ_VOLTAGE_LOW              0X08
#define READ_VOLTAGE_HIGH             0X09
#define READ_TEMPERATURE_LOW          0X0c
#define READ_TEMPERATURE_HIGH         0X0d
// I2C Subcommands
#define READ_CURRENT_LOW              0X00
#define READ_CURRENT_HIGH             0X18
