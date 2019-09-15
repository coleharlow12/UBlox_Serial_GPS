/* 
	Ublox_GPS.cpp - Library for reading binary data from a ublox gps system. 
	As configued this librarys is capable of reading and storing the information
	 within the VELNED and POSLLH messages on the Ublox gps. 

	 Created by Cole Harlow, Novemeber 19 2018

	 Released into the public domain. 
*/ 

#include "Arduino.h"
#include "Ublox_GPS.h"

//Quick note we neeed to make sure that we are using the correct serial port in the library. 
bool Ublox_GPS::readVEL(){
  static int fpos = 0;
  static unsigned char checksumV[2];
  const int payloadSizeV = sizeof(VEL_NED);

  while ( Serial.available() ) {
    //reads in a byte of data while there is data on the serial port
    byte c = Serial.read();
    //if fpos is less than t then we are just reading the header of the UBX message so we make sure we match the message
    if ( fpos < 2 ) {
      if ( c == UBX_HEADER[fpos] )
      {
        fpos++;
      }
      //If the message does not match then we have to reset fpos and restart building our message. 
      else
        fpos = 0;
    }

    // Once we are past the header we can just start storing the data into one of the data structures
    else {
      //If the position fpos minus two is less than our payload size then we are just going to store the data in our structure.
      if ( (fpos-2) < payloadSizeV )
        ((byte*)(&velNED))[fpos-2] = c;

        //This statement makes sure that we are reading the velocity message and not the position message
        if ((fpos-2) == 1)
        {
          if(c!=18){ fpos = 0;}
        }

      fpos++;
      //There has to be one
      if ( fpos == (payloadSizeV+2) ) {
        calcChecksumVEL(checksumV);
      }
      else if ( fpos == (payloadSizeV+3) ) {
        if ( c != checksumV[0] )
          fpos = 0;
      }
      else if ( fpos == (payloadSizeV+4) ) {
        fpos = 0;
        if ( c == checksumV[1] ) {
          return true;
        }
      }
      else if ( fpos > (payloadSizeV+4) ) {
        fpos = 0;
      }
    }
  }
  return false;
}

bool Ublox_GPS::readPOS(){
  static int fpos = 0;
  static unsigned char checksum[2];
  const int payloadSize = sizeof(POS_LLH);

  while ( Serial.available() ) {
    //reads in a byte of data while there is data on the serial port
    byte c = Serial.read();
    //if fpos is less than t then we are just reading the header of the UBX message so we make sure we match the message
    if ( fpos < 2 ) {
      if ( c == UBX_HEADER[fpos] )
        fpos++;
      //If the message does not match then we have to reset fpos and restart building our message. 
      else
      
        fpos = 0;
    }
    // Once we are past the header we can just start storing the data into one of the data structures
    else {
      //If the position fpos minus two is less than our payload size then we are just going to store the data in our structure.
      if ( (fpos-2) < payloadSize )
        ((byte*)(&posLLH))[fpos-2] = c;

      fpos++;
      //There has to be one
      if ( fpos == (payloadSize+2) ) {
        calcChecksumPOS(checksum);
      }
      else if ( fpos == (payloadSize+3) ) {
        if ( c != checksum[0] )
          fpos = 0;
      }
      else if ( fpos == (payloadSize+4) ) {
        fpos = 0;
        if ( c == checksum[1] ) {
          return true;
        }
      }
      else if ( fpos > (payloadSize+4) ) {
        fpos = 0;
      }
    }
  }
  return false;
}

//The checksums should be combined into one function at some point in the near future.  
//Just pass along a pointer to the message potentially. Right now the messages are set up in some what of restrictive way. 

void Ublox_GPS::calcChecksumPOS(unsigned char* CK) {
  //http://www.cplusplus.com/reference/cstring/memset/
  //This section must set CK to [0,0]
  memset(CK, 0, 2);
  for (int i = 0; i < (int)sizeof(posLLH); i++) {
    CK[0] += ((unsigned char*)(&posLLH))[i];
    CK[1] += CK[0];
  }
}

void Ublox_GPS::calcChecksumVEL(unsigned char* CK){
  //http://www.cplusplus.com/reference/cstring/memset/
  memset(CK, 0, 2);
  for (int i = 0; i < (int)sizeof(VEL_NED); i++) {
    CK[0] += ((unsigned char*)(&velNED))[i];
    CK[1] += CK[0];
  }
}