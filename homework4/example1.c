#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <signal.h>
#include <softPwm.h>

#define IN1_PIN 1
#define IN2_PIN 4
#define IN3_PIN 5
#define IN4_PIN 6

#define MAX_SPEED 50
#define MIN_SPEED 0

#define TRIG_PIN 28
#define ECHO_PIN 29

void initDCMotor();
void goForward();
void stopDCMotor();
void rotate();
int getDistance();
void signalHandler(int signal);

int main(void)
{
    if(wiringPiSetup() == -1){
        return 0;
    }

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    signal(SIGINT, signalHandler);
    initDCMotor();

    int distance;
    while(1)
    {
        distance = getDistance();
	    printf("Distance %dcm\n", distance);
        if(distance < 30) {
            stopDCMotor();
            delay(200);
            rotate();
            delay(900);
            goForward();
            delay(2000);
            stopDCMotor();
            break;
        } else {
            goForward();
        }
    }

    return 0;
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

void rotate()
{
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, LOW);
    digitalWrite(IN4_PIN, HIGH);
}

void goForward()
{
    softPwmWrite(IN1_PIN, MAX_SPEED);
    softPwmWrite(IN2_PIN, LOW);
    softPwmWrite(IN3_PIN, MAX_SPEED);
    softPwmWrite(IN4_PIN, LOW);
}

void stopDCMotor()
{
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, LOW);
    digitalWrite(IN4_PIN, LOW);
}

void signalHandler(int signal)
{
    stopDCMotor();
    exit(0);
}


int getDistance()
{
    int start_time=0, end_time=0;
    float distance=0;

    digitalWrite(TRIG_PIN, LOW);
    delay(500);
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

