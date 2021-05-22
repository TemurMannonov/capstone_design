#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

//motor pins
#define IN1_PIN 1
#define IN4_PIN 4
#define IN5_PIN 5
#define IN6_PIN 6

//IR sensor pins
#define LEFT_IR_PIN 27
#define RIGHT_IR_PIN 26

//Ultrasonic pins
#define TRIG_PIN 28
#define ECHO_PIN 29

// motor constants
#define MAX_SPEED 80
#define MIN_SPEED 0
#define SLOW 35

//Line tracer pins
#define LEFT_TRACER_PIN 10
#define RIGHT_TRACER_PIN 11

//Movement functions
void goForwardFast();
void goForwardSlow();
void goBackward();
void stopDCMotor();
void initDCMotor();
void goRight();
void goLeft();

//Ultrasonic functions
int getDistance();

//IR functions
void pinsIn();
int main(void)
{
    if(wiringPiSetup() == -1){
        return 0;
    }
    initDCMotor();
    int LValue, RValue, leftTracer, rightTracer;
    pinsIn();
    int counter =7;
    while (counter>0) {
        LValue = digitalRead(LEFT_IR_PIN);
        RValue = digitalRead(RIGHT_IR_PIN);
        leftTracer = digitalRead(LEFT_TRACER_PIN);
        rightTracer = digitalRead(RIGHT_TRACER_PIN);
        if( LValue ==1 && RValue ==1){
            if(leftTracer ==0 && rightTracer ==1){
                goRight();
                delay(25);
            } else if(leftTracer==1 && rightTracer ==0){
                goLeft();
                delay(25);
            } else if(rightTracer == 1 && leftTracer ==1){
                if(counter == 4){
                    stopDCMotor();
                    initDCMotor();
                    printf("Third Point! ");
                    counter --;
                    goRight();
                    delay(1750);
                } else{
                    counter--;
                    delay(500); // I put this delay so that tracer pins will not read simultaneously one line as several lines
                }
            }
            goForwardSlow();
            delay(1);
        } else {
            printf("Obstacle!\n");
            stopDCMotor();
            initDCMotor();
            }
        }

    stopDCMotor();
    printf("Finish line - Jasur Salimov u1610094!\n" );
    return 0;
}
void pinsIn(){
    //IR
    pinMode(LEFT_IR_PIN, INPUT);
    pinMode(RIGHT_IR_PIN, INPUT);
    //Tracer pin
    pinMode(LEFT_TRACER_PIN, INPUT);
    pinMode(RIGHT_TRACER_PIN, INPUT);
}

void initDCMotor()
{
    pinMode(IN1_PIN, SOFT_PWM_OUTPUT);
    pinMode(IN4_PIN, SOFT_PWM_OUTPUT);
    pinMode(IN5_PIN, SOFT_PWM_OUTPUT);
    pinMode(IN6_PIN, SOFT_PWM_OUTPUT);
    softPwmCreate(IN1_PIN, MIN_SPEED, MAX_SPEED);
    softPwmCreate(IN4_PIN, MIN_SPEED, MAX_SPEED);
    softPwmCreate(IN5_PIN, MIN_SPEED, MAX_SPEED);
    softPwmCreate(IN6_PIN, MIN_SPEED, MAX_SPEED);
}

void goForwardFast()
{
    softPwmWrite(IN1_PIN, MAX_SPEED);
    softPwmWrite(IN4_PIN, MIN_SPEED);
    softPwmWrite(IN5_PIN, MAX_SPEED);
    softPwmWrite(IN6_PIN, MIN_SPEED);
    printf("Forward Fast\n");
}

void goForwardSlow()
{
    softPwmWrite(IN1_PIN, 27);
    softPwmWrite(IN4_PIN, MIN_SPEED);
    softPwmWrite(IN5_PIN, 27);
    softPwmWrite(IN6_PIN, MIN_SPEED);
}

void goBackward()
{
    softPwmWrite(IN1_PIN, MIN_SPEED);
    softPwmWrite(IN4_PIN, MAX_SPEED);
    softPwmWrite(IN5_PIN, MIN_SPEED);
    softPwmWrite(IN6_PIN, MAX_SPEED);
    printf("Backward\n");
}

void stopDCMotor()
{
    softPwmStop(IN1_PIN);
    softPwmStop(IN4_PIN);
    softPwmStop(IN5_PIN);
    softPwmStop(IN6_PIN);
    printf("Stop\n");
}

void goRight()
{
    softPwmWrite(IN1_PIN, MAX_SPEED);
    softPwmWrite(IN4_PIN, MIN_SPEED);
    softPwmWrite(IN5_PIN, MIN_SPEED);
    softPwmWrite(IN6_PIN, MAX_SPEED);
}

void goLeft()
{
    softPwmWrite(IN1_PIN, MIN_SPEED);
    softPwmWrite(IN4_PIN, MAX_SPEED);
    softPwmWrite(IN5_PIN, MAX_SPEED);
    softPwmWrite(IN6_PIN, MIN_SPEED);
}