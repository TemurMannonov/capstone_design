#include <stdio.h>
#include <wiringPi.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define TRIG_PIN 28
#define ECHO_PIN 29

#define IN1_PIN 1
#define IN2_PIN 4
#define IN3_PIN 5
#define IN4_PIN 6

void initDCMotor();
void stopDCMotor();
void goForward();
int getDistance();
void signalHandler(int signal);

int main(void)
{
    if(wiringPiSetup() == -1)
        return 0;
    
    pinMode(IN1_PIN, OUTPUT);
    pinMode(IN2_PIN, OUTPUT);
    pinMode(IN3_PIN, OUTPUT);
    pinMode(IN4_PIN, OUTPUT);

    initDCMotor();
    
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    
    signal(SIGINT, signalHandler);

    while(1)
    {  
        printf("Distance %dcm\n", getDistance());
        if (getDistance() < 20) {
            stopDCMotor();
        } else {
            goForward();
        }
    }
    
    return 0;
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

void initDCMotor()
{
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, HIGH);
    digitalWrite(IN3_PIN, HIGH);
    digitalWrite(IN4_PIN, HIGH);
}

void stopDCMotor()
{
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, LOW);
    digitalWrite(IN4_PIN, LOW);
}

void goForward()
{
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, HIGH);
    digitalWrite(IN4_PIN, LOW);
}