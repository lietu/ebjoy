#ifndef JOUTPUT_H
#define JOUTPUT_H

#include <Arduino.h>

#define JOY_REST 512
#define Z_MAX 1023
#define Z_RANGE 511

class JOutput {

    public:
        /**
         * Dummy constructor, does nothing, initialize later with .setup()
         */
        JOutput(void);

        /**
         * Initialize object for use if created with dummy constructor
         * param[in] The sensor pin
         * param[in] The interrupt to listen to
         * param[in] The pin with a led on it
         */
        void setup(unsigned long);

        void set_rpm(unsigned long);
        
        void print_debug(void);
        
    protected:
        unsigned long max_rpm;
        unsigned long value;
};

#endif
