#include <stdio.h>
#include <wiringPi.h>

#define LEFT_TRACER_PIN 10
#define RIGHT_TRACER_PIN 11

void initLineTracer()
{
    pinMode(LEFT_TRACER_PIN, INPUT);
    pinMode(RIGHT_TRACER_PIN, INPUT);
}

int main(void){
    
    if(wiringPiSetup() == -1)
        return 0;
    
    int leftTracer, rightTracer;
    initLineTracer();
    
    while (1) {
        leftTracer = digitalRead(LEFT_TRACER_PIN);
        rightTracer = digitalRead(RIGHT_TRACER_PIN);
        
        if (leftTracer == 0 && rightTracer == 1) {
            printf("Left\n");
        } else if (rightTracer ==0 && leftTracer == 1) {
            printf("Right\n");
        } else if (rightTracer == 0 && leftTracer == 0) {
            printf("Both\n");
        } else if (rightTracer == 1 && leftTracer == 1) {
            printf("No\n");
        }
    }
    
    return 0;

}