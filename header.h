//MOTOR Driver PINS
int ENR = 6;
int ENL = 7;
int INR1 =30;
int INR2 =31;
int INL1 =32;
int INL2 =33;

//joystick pins
int joyX = 0; // analogpin
int joyY = 1;
int joySW = 50;

//for blink function
int LED = 2;

//LINE SENSOR PINS
int Line_SL = 10;
int Line_SM = 9;
int Line_SR = 8;


//LINE SENSOR VALUES
int Line_SVL = 0;
int Line_SVM = 0;
int Line_SVR = 0;

// LINE FLAG
int Line_LF = 0;
int Line_MF = 0;
int Line_RF = 0;

//PWM VLUES
int pwm_min = 140;
int pwm_max = 220;

//for line sensing
long int timeStart = 0;

// UltraSonic Pins
#define TRIGGER_PIN_L  37
#define ECHO_PIN_L     36
#define TRIGGER_PIN_R  41
#define ECHO_PIN_R     40
#define TRIGGER_PIN  39  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     38  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 350 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define gotodestination_MAX_SPEED 180
#define gotodestination_kp 5

//Magnetometer
float angleoffset = 6;

//functions
void fowardRobot(int withspeed);
void brakeRobot(void);
void reverseRobot(int withspeed);
float getHeading(void);
int check_Line(void);
int senseline(void);
//void turnRobotAngle1(float goangle, int spd); // to perticular direction in 0-360 degree
void turnRobotAngle(float goangle);
void turnRobot(float angle);// +- angle turn from current position 
float errorang(float goangle);
//void findshortdis1(void);
int findshortdis(void);
void gotodestination(int);
void blinkk(void);
