#include "joutput.h"

JOutput::JOutput() {
    this->max_rpm = 1;
    this->value = 0;
}

void JOutput::setup(unsigned long max_rpm) {
    if (max_rpm > 0) {
        this->max_rpm = max_rpm;
    }
    
}

void JOutput::set_rpm(unsigned long rpm) {
    this->value = JOY_REST + ((Z_RANGE * ((rpm * 1000) / this->max_rpm)) / 1000);
    Joystick.Z(this->value);
    Joystick.X(JOY_REST);
    Joystick.Y(JOY_REST);
    Joystick.Zrotate(JOY_REST);
    Joystick.sliderLeft(JOY_REST);
    Joystick.sliderRight(JOY_REST);
    Joystick.hat(-1);
}

void JOutput::print_debug(void) {
    Serial.print("Joystick Z: ");
    Serial.println(this->value);
}
