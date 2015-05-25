/*
 * Configuration
 *
 * Most of the things you want to change should be in this section.
 * If you need to change anything outside of this, you're on your own.
 */

// You'll want to change these if you are using another pin on your Arduino
// Keep in mind that not all pins are able to get interrupts
// For Teensy 3.1 I had to put both SENSOR_PIN and INTERRUPT as 2
// For Arduino (nano) to get the data I had to use SENSOR_PIN 2, INTERRUPT 0
#define SENSOR_PIN 2
#define INTERRUPT 2
#define LED_PIN 13

// Use this to control the range of the Z-axis output. The lower the MAX_RPM the less
// you have to pedal for max output.
#define MAX_RPM 150

// Set to true if you want to see debugging messages in your serial terminal
#define DEBUG true
#define DEBUG_INTERVAL 3000 /* msec */
#define DEBUG_BAUD 9600

/*
 * End configuration
 */


#include "ebinput.h"
#include "joutput.h"

EBInput input;
JOutput output;

static unsigned long last_debug = 0;


void setup(void)
{
    if (DEBUG) {
        Serial.begin(DEBUG_BAUD);
        Serial.println("Fitness bike JoyStick booting up.");
        Serial.println();
        last_debug = millis();
    }

    input.setup(SENSOR_PIN, INTERRUPT, LED_PIN);
    output.setup(MAX_RPM);
}

void loop(void)
{
    unsigned long time = millis();
    
    input.loop(time);
    output.set_rpm(input.rpm);
    
    if(DEBUG && (last_debug + DEBUG_INTERVAL) < time)
    {
        input.print_debug();
        output.print_debug();
        last_debug = time;
    }
}
