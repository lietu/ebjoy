#ifndef EBINPUT_H
#define EBINPUT_H

#include <Arduino.h>

// How many seconds of data do we store, 60 must be divisible by this
#define EBINPUT_SECONDS 5
// How many times do those seconds fit in a minute
#define EBINPUT_MINUTE_DIVISOR 12

void pedal_rotation(void);

class EBInput {

    public:
        /**
         * Dummy constructor, does nothing, initialize later with .setup()
         */
        EBInput(void);

        /**
         * Initialize object for use if created with dummy constructor
         * param[in] The sensor pin
         * param[in] The interrupt to listen to
         * param[in] The pin with a led on it
         */
        void setup(uint8_t, int, int);

        void loop(unsigned long);

        void print_debug(void);
        unsigned long rpm;

    protected:
    	void update_rpm(void);

        int led_pin;
    	uint8_t current_rotations;
    	uint8_t prev_second;
    	uint8_t data[EBINPUT_SECONDS];
};

#endif
