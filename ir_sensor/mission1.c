#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <signal.h>
#include <stdlib.h>

#define IN1_PIN 1
#define IN2_PIN 4
#define IN3_PIN 5
#define IN4_PIN 6

#define LEFT_IR_PIN 27
#define RIGHT_IR_PIN 26

void initIR()
{
    pinMode(LEFT_IR_PIN, INPUT);
    pinMode(RIGHT_IR_PIN, INPUT);
}

int main(void){
    if(wiringPiSetup() == -1)
    return 0;
    
    int LValue, RValue;
    initIR();
    
    while (1) {
        LValue = digitalRead(LEFT_IR_PIN);
        RValue = digitalRead(RIGHT_IR_PIN);
        if(LValue == 1 && RValue == 0 ) {
            printf("Right\n");
        }else if (LValue == 0 && RValue == 1) {
            printf("Left\n");
        }else if(LValue == 0 && RValue == 0){
            printf("Both\n");
        }else if(LValue == 1 && RValue == 1){
            printf("No\n");
        }
    }
}