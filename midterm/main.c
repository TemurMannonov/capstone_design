#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <signal.h>
#include <stdlib.h>

// Motor Pins
#define IN1_PIN 1
#define IN2_PIN 4
#define IN3_PIN 5
#define IN4_PIN 6

// Lin Tracer Sensor Pins
#define LEFT_TRACER_PIN 10
#define RIGHT_TRACER_PIN 11

// IR Pins
#define LEFT_IR_PIN 27
#define RIGHT_IR_PIN 26

// Ultrasonic Sensor Pins
#define TRIG_PIN 28
#define ECHO_PIN 29

// Speed
#define MAX_SPEED 50
#define MIN_SPEED 0

// Init Line Tracer Sensors
void initLineTracer();

// Init IR Sensors
void initIR();

// Init Ultrasonic Sensor
void initUltrasonic();

// DC Motor
void initDCMotor();
void goForward();
void goForwardWithSpeed(int speed);
void goBackward();
void goBackwardWithSpeed(int speed);
void goLeft();
void goRight();
void smoothLeft();
void smoothRight();
void stopDCMotor();

// Get distance function
int getDistance();

// Signal handler function
void signalHandler(int signal);

// Helper functions
void byPassObstacle();
void park();
void goBackFromPark();

int main(void) {

    if(wiringPiSetup() == -1)
        return 0;

    int leftTracer, rightTracer;
    int LValue, RValue;

    initDCMotor();
    initIR();
    initLineTracer();
    signal(SIGINT, signalHandler);

    while (1) {
        LValue = digitalRead(LEFT_IR_PIN);
        RValue = digitalRead(RIGHT_IR_PIN);

        if (LValue == 0 || RValue == 0) {
            byPassObstacle();
            park();
            goBackFromPark();
            byPassObstacle();
        }

        leftTracer = digitalRead(LEFT_TRACER_PIN);
        rightTracer = digitalRead(RIGHT_TRACER_PIN);
        
        if (leftTracer == 1 && rightTracer == 0) {
            goLeft();
            delay(20);
        } else if (rightTracer == 1 && leftTracer == 0) {
            goRight();
            delay(20);
        } else if (rightTracer == 1 && leftTracer == 1) {
            goForward();
        } else if (rightTracer == 0 && leftTracer == 0) {          
            goForward();
        }
    }
    
    return 0;
}

void initLineTracer()
{
    pinMode(LEFT_TRACER_PIN, INPUT);
    pinMode(RIGHT_TRACER_PIN, INPUT);
}

void initIR()
{
    pinMode(LEFT_IR_PIN, INPUT);
    pinMode(RIGHT_IR_PIN, INPUT);
}

void initUltrasonic()
{
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

void initDCMotor()
{
    pinMode(IN1_PIN, SOFT_PWM_OUTPUT);
    pinMode(IN2_PIN, SOFT_PWM_OUTPUT);
    pinMode(IN3_PIN, SOFT_PWM_OUTPUT);
    pinMode(IN4_PIN, SOFT_PWM_OUTPUT);

    softPwmCreate(IN1_PIN, MIN_SPEED, MAX_SPEED);
    softPwmCreate(IN2_PIN, MIN_SPEED, MAX_SPEED);
    softPwmCreate(IN3_PIN, MIN_SPEED, MAX_SPEED);
    softPwmCreate(IN4_PIN, MIN_SPEED, MAX_SPEED);
}

void goForward()
{
    softPwmWrite(IN1_PIN, MAX_SPEED);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, MAX_SPEED);
    softPwmWrite(IN4_PIN, MIN_SPEED);
}

void goForwardWithSpeed(int speed)
{
    softPwmWrite(IN1_PIN, speed);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, speed);
    softPwmWrite(IN4_PIN, MIN_SPEED);
}
void goBackward()
{
    softPwmWrite(IN1_PIN, MIN_SPEED);
    softPwmWrite(IN2_PIN, MAX_SPEED);
    softPwmWrite(IN3_PIN, MIN_SPEED);
    softPwmWrite(IN4_PIN, MAX_SPEED);
}

void goBackwardWithSpeed(int speed)
{
    softPwmWrite(IN1_PIN, MIN_SPEED);
    softPwmWrite(IN2_PIN, speed);
    softPwmWrite(IN3_PIN, MIN_SPEED);
    softPwmWrite(IN4_PIN, speed);
}

void goRight()
{
    softPwmWrite(IN1_PIN, MAX_SPEED);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, MIN_SPEED);
    softPwmWrite(IN4_PIN, MAX_SPEED);
}

void goLeft()
{
    softPwmWrite(IN1_PIN, MIN_SPEED);
    softPwmWrite(IN2_PIN, MAX_SPEED);
    softPwmWrite(IN3_PIN, MAX_SPEED);
    softPwmWrite(IN4_PIN, MIN_SPEED);
}

void smoothLeft()
{
    softPwmWrite(IN1_PIN, MAX_SPEED/8);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, MAX_SPEED);
    softPwmWrite(IN4_PIN, MIN_SPEED);
}

void smoothRight()
{
    softPwmWrite(IN1_PIN, MAX_SPEED);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, MAX_SPEED/8);
    softPwmWrite(IN4_PIN, MIN_SPEED);
}

void stopDCMotor()
{
    softPwmStop(IN1_PIN);
    softPwmStop(IN2_PIN);
    softPwmStop(IN3_PIN);
    softPwmStop(IN4_PIN);
}

int getDistance()
{
    int start_time=0, end_time=0;
    float distance=0;

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    while (digitalRead(ECHO_PIN) == 0);
        start_time = micros();
    while (digitalRead(ECHO_PIN) == 1);
        end_time = micros();

    distance = (end_time - start_time) / 29. / 2.;
    return (int)distance;
}

void signalHandler(int signal)
{
    stopDCMotor();
    exit(0);
}


void byPassObstacle()
{
    
    // goBackward();
    // delay(300);
    // goRight();
    // delay(500);
    // goForward();
    // delay(500);
    // goLeft();
	// delay(500);
    // goForward();
    // delay(2000);
    // goLeft();
    // delay(500);
    // goForward();
    // delay(500);
    // goRight();
    // delay(500);
    // goForward();

    int LValue, RValue;
    int leftTracer, rightTracer;
    goBackward();
    delay(300);
    goRight();
    delay(500);
    goForward();

    // Go forward till the line
    while (1) {
        leftTracer = digitalRead(LEFT_TRACER_PIN);
        rightTracer = digitalRead(RIGHT_TRACER_PIN);
        
        if (leftTracer == 1 || rightTracer == 1) {
            goBackward();
            delay(100);
            break;
        } 
    }

    goLeft();
    delay(500);
    goForward();

    // Go forward till the second line
    while (1) {
        leftTracer = digitalRead(LEFT_TRACER_PIN);
        rightTracer = digitalRead(RIGHT_TRACER_PIN);
        
        if (leftTracer == 1 || rightTracer == 1) {
            goBackward();
            delay(100);
        } 
    }

    goLeft();
    delay(500);
    goForward();
    delay(500);
    goRight();
    delay(500);
    goForward();
}

void park()
{
    int LValue, RValue;
    int leftTracer, rightTracer;
    
    goForward();

    // Go forward till the line
    while (1) {
        leftTracer = digitalRead(LEFT_TRACER_PIN);
        rightTracer = digitalRead(RIGHT_TRACER_PIN);
        
        if (leftTracer == 1 || rightTracer == 1) {
            goBackward();
            delay(100);
            break;
        } 
    }

    goLeft();
    delay(500);
    goForward();

    // Go forward till the second line
    while (1) {
        leftTracer = digitalRead(LEFT_TRACER_PIN);
        rightTracer = digitalRead(RIGHT_TRACER_PIN);
        
        if (leftTracer == 1 || rightTracer == 1) {
            stopDCMotor();
            initDCMotor();
            delay(500);
        } 
    }
}

void goBackFromPark()
{
    int LValue, RValue;
    int leftTracer, rightTracer;
    
    goBackward();
    delay(1000);
    goLeft();
    delay(500);
    goForward();

    // Go forward till the obstacle
    while (1) {
        LValue = digitalRead(LEFT_IR_PIN);
        RValue = digitalRead(RIGHT_IR_PIN);

        if (LValue == 0 || RValue == 0) {
            break;
        }
    }
}

