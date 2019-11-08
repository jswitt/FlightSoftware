/****LIBRARIES****/
#include <RH_RF95.h>
#include <TinyGPSPlus.h>
#include <Arduino.h>

#include "Globals.h"
#include "DATA.h"
#include "GPS.h"
#include "I2C.h"
#include "RADIO.h"


/*****CONSTRUCTORS*****/
DATA Data;
GPS Gps;
I2C Comm;
RADIO Radio;

// Directs the radio object to focus on two specific ports.
RH_RF95 rf95(Radio.RFM95_CS, Radio.RFM95_INT);
// Creates an instance of the gps class from TinyGPSPlus.
TinyGPSPlus gps;


/**
 * INITIALIZES ALL REQUIRED PERIPHIALS AND DEPENDENCIES.
 */
void setup()
{
    // Creates a serial communication line between the arduino and the serial port 
    // found under 'Tools' -> 'Serial Monitor'
    Serial.begin(115200);
    // Initializes the Inter-Intergrated Circuit (I^2C) protocol.
    Comm.initialize();
    // Initializes the Radio.
    Radio.initialize();
    // Bootup has happened. Set flags.
    //Data.node_reset = 1;
    //Data.system_boot_complete = false;
    // Configures LEDs and the sd card.
    Data.initialize();
    // Configure LEDs.
    //pinMode(Data.OPERATIONAL_LED, OUTPUT);
    //pinMode(Data.ERROR_LED, OUTPUT);
    //pinMode(Data.RECEIVE_LED, OUTPUT);
    //digitalWrite(Data.ERROR_LED, LOW);
}


/**
 * MAIN PROGRAM CODE.
 */
void loop()
{
    // Verbosity Check. 
    Serial.println("...");
    // Monitors for a powercycle.
    //system_boot();
    // Turns OPERATIONAL_LED on/off.
    //system_led();
    // Reads in a new NMEA sentence.
    Gps.manager();
    // Communicates with the Mega to check for certain events happening
    // throughout the system.
    Comm.manager();
    // Responsible for grabbing all of the craft's current information, 
    // turning that data into an array, and transmitting the array via radio.
    // Also reads incoming network packets.
    Radio.manager();
    // Responsible for the health of the system and logging data to onboard storage.
    //Data.manager();
}


/**
 * Flag management during and after boot process.
 */
void system_boot()
{
    // For the first # seconds of boot.
    if((millis() - Data.startup_timer >= 3000) && !Data.system_boot_complete)
    {
        // System has now been operating for # seconds.
        Data.node_reset = 0;
        // Adjust flag.
        Data.system_boot_complete = true;
    }
}


/**
 * Non-blocking alternating timer to turn the OPERATIONAL_LED on/off at intervals of 1/2 second.
 */
void system_led()
{
    if(millis() - Data.ext_led_timer >= 300)
    {
        Data.ext_led_timer = millis();
        // Turns external LED off.
        if(Data.external_led)
        {
            Data.external_led = false;
            //digitalWrite(Data.OPERATIONAL_LED, LOW);
        }
        // Turns external LED on.
        else
        {
            Data.external_led = true;
            //digitalWrite(Data.OPERATIONAL_LED, HIGH);
        }
    }
}
