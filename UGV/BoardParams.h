// Serial port configuration
#define BAUD_RATE    57600

// Motors parameters
#define PIN_PWM_R        5 // Speed control of right motor
#define PIN_PWM_L        6 // Speed control of left motor
#define PIN_MOT_R        4 // Direction control of right motor
#define PIN_MOT_L        7 // Direction control of left motor

#define MIN_PWM         58 // PWM minimum value
#define MAX_PWM        255 // PWM maximum value

// Comm protocol constants
#define ID_SLAVE  0x01
#define ID_MASTER 0x02
#define STX    0x02
#define ETX    0x03

// Function codes from PC
#define READY   0X04
#define MOVE  0X05

// Function codes from RoMeo
#define ACK_MSG  0X01
