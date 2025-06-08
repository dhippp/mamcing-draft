#include <ESP32Servo.h>

#define SERVO_PIN 14

Servo mamcing_servo;

void servo_setup(){
    mamcing_servo.attach(SERVO_PIN);
}

void servo_clockwise_move(){
    mamcing_servo.write(180);
}

void servo_counterclockwise_move(){
    mamcing_servo.write(0);
}

void servo_stop_move(){
    mamcing_servo.write(90);
}
