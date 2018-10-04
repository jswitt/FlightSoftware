/**
 * I2C.cpp handles sending of event messages
 *    between the LORA and MEGA via I2C protocol.
 */


#include "I2C.h"
#include "DATA.h"
#include "Globals.h"
#include <Wire.h>
#include <Arduino.h>


/**
 * Constructor used to reference all other variables & functions.
 */
I2C::I2C()
{
  
}


/**
 * Assigns the proper address to the current micro controller.
 */
void I2C::initialize()
{
    // Predeclaration of method that will be set as a interrupt.
    void receiveEvent(int howMany);
	// Sets the address for the current micro controller.
	// Mega - 0
	// LoRa - 8
	Wire.begin();
}


/**
 * Recieves bytes over I2C Connection. Interrupt method.
 */
void receiveEvent(int howmany)
{
<<<<<<< HEAD
=======
    // New info is being read in. 
    Data.new_data = Data.YES;

    /*
    if(Comm.complete_packet_flag)
    {
    	Comm.to_parse[Comm.i2c_packet.length()];
        Comm.i2c_packet.toCharArray(Comm.to_parse,Comm.i2c_packet.length());
        Serial.print("I2C Packet: ");
        Serial.println(Comm.i2c_packet);
        Comm.first_32 = false;
        Comm.second_32 = false;
        Comm.third_32 = false;
        Comm.i2c_packet = "";
    }

    // This series of conditional checks will make sure that the 3 seperate
    // i2c packets are read in (in order) before letting the mega use the data.
    // They are all acting as flags and are reset upon the start of the next packet.
    if(!Comm.first_32)
    {
    	Comm.complete_packet_flag = false;
        Comm.first_32 = true;
    }
    else if(!Comm.second_32)
    {
        Comm.second_32 = true;
    }
    else if(!Comm.third_32)
    {
        Comm.third_32 = true;
        Comm.complete_packet_flag = true;
    }

    // Checks for data on the wire.
    while(Wire.available())
    {
    	char temp = Wire.read();
        // Concatenates character to large string.
        Comm.i2c_packet += temp;
    }
    */

    int packet_length = 0;
>>>>>>> parent of b8a070a... Made the i2c_receive a usual method that is run prior to parsing. It is not longer an interrupt.
    Comm.i2c_packet = "";
    
    Wire.requestFrom(8, 30);
    
    while(Wire.available())
    {
    	char temp = Wire.read();
      Serial.print(temp);
        // Concatenates character to large string.
        Comm.i2c_packet += temp;
    }
    Serial.println();

    // Checks for proper formatting.
<<<<<<< HEAD
    if(Comm.i2c_packet[0] == '$')
=======
    if(Comm.i2c_packet[0] == '$' && Comm.i2c_packet[packet_length-1] == '$')
>>>>>>> parent of b8a070a... Made the i2c_receive a usual method that is run prior to parsing. It is not longer an interrupt.
    {
      Comm.complete_packet_flag = true;
    	Comm.to_parse[Comm.i2c_packet.length()];
      Serial.print("Packet Length: ");
      Serial.println(packet_length);
    	Comm.i2c_packet.toCharArray(Comm.to_parse,Comm.i2c_packet.length());
    	Serial.print("I2C Packet: ");
    	Serial.println(Comm.i2c_packet);
    }
    else
    {
        Comm.complete_packet_flag = false;
    }
}
