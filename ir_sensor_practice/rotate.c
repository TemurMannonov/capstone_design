#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <signal.h>
#include <stdlib.h>

#define IN1_PIN 1
#define IN2_PIN 4
#define IN3_PIN 5
#define IN4_PIN 6

#define LEFT_TRACER_PIN 10
#define RIGHT_TRACER_PIN 11

#define MAX_SPEED 80
#define MIN_SPEED 0

// Init Line Tracer
void initLineTracer();

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
void rotate();

// Signal handler function
void signalHandler(int signal);

int main(void) {

    if(wiringPiSetup() == -1)
        return 0;

    initDCMotor();
    signal(SIGINT, signalHandler);
    goForward();
    delay(500);
    rotate();
    delay(1500);
    stopDCMotor();
    
    
    return 0;
}

void initLineTracer()
{
    pinMode(LEFT_TRACER_PIN, INPUT);
    pinMode(RIGHT_TRACER_PIN, INPUT);
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
    softPwmWrite(IN1_PIN, LOW);
    softPwmWrite(IN2_PIN, MAX_SPEED);
    softPwmWrite(IN3_PIN, LOW);
    softPwmWrite(IN4_PIN, MAX_SPEED);
}

void goBackwardWithSpeed(int speed)
{
    softPwmWrite(IN1_PIN, LOW);
    softPwmWrite(IN2_PIN, speed);
    softPwmWrite(IN3_PIN, LOW);
    softPwmWrite(IN4_PIN, speed);
}

void goRight()
{
    softPwmWrite(IN1_PIN, MAX_SPEED);
    softPwmWrite(IN2_PIN, LOW);
    softPwmWrite(IN3_PIN, LOW);
    softPwmWrite(IN4_PIN, MAX_SPEED);
}

void goLeft()
{
    softPwmWrite(IN1_PIN, LOW);
    softPwmWrite(IN2_PIN, MAX_SPEED);
    softPwmWrite(IN3_PIN, MAX_SPEED);
    softPwmWrite(IN4_PIN, LOW);
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
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, LOW);
    digitalWrite(IN4_PIN, LOW);
}

void rotate()
{
    softPwmWrite(IN1_PIN, MAX_SPEED);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, MIN_SPEED);
    softPwmWrite(IN4_PIN, MAX_SPEED);
}

void signalHandler(int signal)
{
    stopDCMotor();
    exit(0);
}

