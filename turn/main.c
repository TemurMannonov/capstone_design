#include <stdio.h>
#include <wiringPi.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define IN1_PIN 1
#define IN2_PIN 4
#define IN3_PIN 5
#define IN4_PIN 6

void initDCMotor();
void goForward();
void goBackward();
void goLeft();
void goRight();
void stopDCMotor();
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

    signal(SIGINT, signalHandler);

    char choice ;
    while(1)
    {  
        printf("Choices:\n");
        printf("w - Forward\n");
        printf("s - Backward\n");
        printf("d - Right\n");
        printf("a - Left\n");
        printf("e - Stop\n");
        printf("Choice:");
        scanf("%c", &choice);

        if (choice == 'w') {
            goForward();
            delay(100);
        } else if (choice == 's') {
            goBackward();
            delay(100);
        } else if (choice == 'd') {
            goRight();
            delay(500);
            goForward();
        } else if (choice == 'a') {
            goLeft();
            delay(500);
            goForward();
        } else if (choice == 'e') {
            stopDCMotor();
        }
    }
   
    return 0;
}

void signalHandler(int signal)
{
    stopDCMotor();
    exit(0);
}

void initDCMotor()
{
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, HIGH);
    digitalWrite(IN3_PIN, HIGH);
    digitalWrite(IN4_PIN, HIGH);
}

void goLeft()
{
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, HIGH);
    digitalWrite(IN3_PIN, HIGH);
    digitalWrite(IN4_PIN, LOW);
}

void goForward()
{
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, HIGH);
    digitalWrite(IN4_PIN, LOW);
}

void goRight()
{
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, LOW);
    digitalWrite(IN4_PIN, HIGH);
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