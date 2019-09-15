
#ifndef Ublox_GPS_h
#define Ublox_GPS_h

#include "Arduino.h"

class Ublox_GPS
{
public:

	const unsigned char UBX_HEADER[2] = { 0xB5, 0x62 };

	struct VEL_NED {
	  unsigned char cls = 0x01; //A 1 byte class field follws. 
	  unsigned char id; //A 1 byte ID field defines the message that is to follw
	  unsigned short len; //This is the 16 bit that stores the length of the payload only
	  unsigned long iTOW; // U4 number. GPS millisecond time of the week
	  signed long velN; //north velocity cm/s 
	  signed long velE; //east velocity cm/s 
	  signed long velD; //down velocity cm/s 
	  unsigned long SPD; // 3d dimensional speed cm/s
	  unsigned long gSPD; // Ground (2D) speed cm/s
	  signed long heading; // heading of motion 2-D degress
	  unsigned long sAcc; // speed accuracy estimate
	  unsigned long cAcc; // Course/heading Accuracy Estimate.
	};

	struct POS_LLH {
	  unsigned char cls = 0x01; //A 1 byte class field follws. 
	  unsigned char id; //A 1 byte ID field defines the message that is to follw
	  unsigned short len; //This is the 16 bit that stores the length of the payload only
	  unsigned long iTOW; // U4 number. GPS millisecond time of the week
	  signed long lon; //longitude
	  signed long lat; //latitude
	  signed long height; //height about ellipsoid
	  signed long hMSL; // Height above mean sea level
	  unsigned long hAcc; //Horizontal Accuracy estimate
	  unsigned long vAcc; //Vertical accuracy estimate
	};

	bool readVEL();
	bool readPOS();


	POS_LLH posLLH;
	VEL_NED velNED;

private:

	void calcChecksumPOS(unsigned char* CK);
	void calcChecksumVEL(unsigned char* CK);



};

#endif