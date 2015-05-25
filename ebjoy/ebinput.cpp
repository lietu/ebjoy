#include "ebinput.h"

volatile unsigned long last_rotation_timestamp = 0;

EBInput::EBInput() {
    this->rpm = 0;
    this->current_rotations = 0;
    this->prev_second = 255;

    for (uint8_t i = 0; i < EBINPUT_SECONDS; i += 1) {
        this->data[i] = 0;
    }
}

void EBInput::setup(uint8_t pin, int interrupt, int led_pin) {
    this->led_pin = led_pin;
  
    // Set the sensor pin to input mode, and pull it to HIGH level
    // This will make it possible for us to detect when the switch inside the
    // pedals connects it to the ground.
    pinMode(pin, INPUT_PULLUP);
    pinMode(this->led_pin, OUTPUT);
    
    digitalWrite(pin, HIGH);
    digitalWrite(this->led_pin, LOW);

    
    // Listen to the sensor, detect when the signal is connected to the ground
    attachInterrupt(interrupt, pedal_rotation, FALLING);
}

void EBInput::loop(unsigned long time) {
    if (last_rotation_timestamp > 0) {
        this->current_rotations += 1;
        last_rotation_timestamp = 0;
        digitalWrite(this->led_pin, HIGH);
    }

    uint8_t current_second = (time / 1000) % EBINPUT_SECONDS;
    if (current_second != this->prev_second) {
        this->data[this->prev_second] = this->current_rotations;
        this->current_rotations = 0;

        prev_second = current_second;
        this->update_rpm();
        digitalWrite(this->led_pin, LOW);
    }
}

void EBInput::update_rpm(void) {
    uint8_t total = 0;
    for (uint8_t i = 0; i < EBINPUT_SECONDS; i += 1) {
        total += this->data[i];
    }

    this->rpm = (float)total * (float)EBINPUT_MINUTE_DIVISOR;
}

void EBInput::print_debug(void) {
    Serial.print(this->rpm);
    Serial.println(" RPM");
}

void pedal_rotation(void) {
    last_rotation_timestamp = millis();
}
