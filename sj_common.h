/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "stdio.h"
#include "ofxOsc.h"

/************************************************************
************************************************************/
#define ERROR_MSG(); printf("Error in %s:%d\n", __FILE__, __LINE__);

/************************************************************
enum
************************************************************/
enum{
	BUF_SIZE = 2000,
};

enum{
	// NUM_LEDS = 5,
	NUM_LEDS = 33,
};

enum{
	OSC_DMX_LIGHT,
	OSC_VJ,
	
	NUM_OSC_TARGET,
};


/************************************************************
class
************************************************************/

/**************************************************
**************************************************/
class OSC_SEND{
private:
	char IP[BUF_SIZE];
	int Port;

	ofxOscSender sender;
	
public:
	OSC_SEND(const char* _IP, int _Port)
	{
		if(_Port != -1){
			sprintf(IP, "%s", _IP);
			Port = _Port;
			
			sender.setup(IP, Port);
		}
	}
	
	void sendMessage(ofxOscMessage &message)
	{
		if(Port != -1){
			sender.sendMessage(message);
		}
	}
};

class OSC_RECEIVE{
private:
	int Port;
	ofxOscReceiver	receiver;
	
public:
	OSC_RECEIVE(int _Port)
	{
		if(_Port != -1){
			Port = _Port;
			receiver.setup(Port);
		}
	}
	
	bool hasWaitingMessages()
	{
		if(Port == -1){
			return false;
		}else{
			return receiver.hasWaitingMessages();
		}
	}
	
	bool getNextMessage(ofxOscMessage *msg)
	{
		if(Port == -1){
			return false;
		}else{
			return receiver.getNextMessage(msg);
		}
	}
};

class OSC_TARGET{
private:
public:
	OSC_SEND	OscSend;
	OSC_RECEIVE	OscReceive;
	
	OSC_TARGET(const char* _SendTo_IP, int _SendTo_Port, int _Receive_Port)
	: OscSend(_SendTo_IP, _SendTo_Port), OscReceive(_Receive_Port)
	{
	}
};


/************************************************************
************************************************************/
extern OSC_TARGET OscTarget[];

/************************************************************
************************************************************/
extern void printMessage(const char* message);
extern void fopen_LogFile();
extern void fclose_LogFile();
extern void fprint_debug_Log(char* message);

