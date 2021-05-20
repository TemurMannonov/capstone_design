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
void goForwardWithSpeed(int speed);
void goBackward();
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
            printf("Stop");
            stopDCMotor();
            delay(200);
            printf("Rotate");
            rotate();
            delay(900);
            goForward();
            delay(2000);
            stopDCMotor();
            break;
        }else{
            goForwardWithSpeed(35);
        }
    }

    return 0;
}

void initDCMotor()
{
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, HIGH);
    digitalWrite(IN3_PIN, HIGH);
    digitalWrite(IN4_PIN, HIGH);
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
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, HIGH);
    digitalWrite(IN4_PIN, LOW);
}


void goBackward()
{
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, HIGH);
    digitalWrite(IN3_PIN, LOW);
    digitalWrite(IN4_PIN, HIGH);
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

void goForwardWithSpeed(int speed)
{
    softPwmWrite(IN1_PIN, speed);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, speed);
    softPwmWrite(IN4_PIN, MIN_SPEED);
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

