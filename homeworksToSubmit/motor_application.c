#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define IN1_PIN 1
#define IN2_PIN 4
#define IN3_PIN 5
#define IN4_PIN 6

#define MAX_SPEED 50
#define MIN_SPEED 0

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
void signalHandler(int signal);

int main(void)
{
    if(wiringPiSetup() == -1)
        return 0;
    
    signal(SIGINT, signalHandler);
    initDCMotor();
    
    // Go forward for 2 sec.
    goForward();
    delay(2000);

    // Turn left and go forward for 2 sec and stop.
    goLeft();
    delay(420);
    goForward();
    delay(2000);
    stopDCMotor();

    // Go back for 2 sec
    goBackward();
    delay(2000);

    // Turn right and go forward for 2 sec and stop.
    goRight();
    delay(490);
    goForward();
    delay(2000);
    stopDCMotor();

    // Go forward for 2 sec then make left point turn and stop
    goForward();
    delay(2000);
    goLeft();
    delay(600);
    stopDCMotor();

    // Go back for 2 sec then make right smooth turn and stop
    goBackward();
    delay(2000);
    smoothRight();
    delay(2600);
    stopDCMotor();
   
    return 0;
}

void signalHandler(int signal)
{
    stopDCMotor();
    exit(0);
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

void goRight()
{
    // digitalWrite(IN1_PIN, HIGH);
    // digitalWrite(IN2_PIN, LOW);
    // digitalWrite(IN3_PIN, LOW);
    // digitalWrite(IN4_PIN, HIGH);
    softPwmWrite(IN1_PIN, MAX_SPEED);
    softPwmWrite(IN2_PIN, LOW);
    softPwmWrite(IN3_PIN, LOW);
    softPwmWrite(IN4_PIN, MAX_SPEED);
}

void goLeft()
{
    // digitalWrite(IN1_PIN, LOW);
    // digitalWrite(IN2_PIN, HIGH);
    // digitalWrite(IN3_PIN, HIGH);
    // digitalWrite(IN4_PIN, LOW);
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

void stopDCMotor()
{
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, LOW);
    digitalWrite(IN4_PIN, LOW);
}
