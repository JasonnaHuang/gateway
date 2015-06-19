#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart_raw.h"
#include "zlg_protocol.h"
#include "zlg_cmd.h"
#include "serial.h"

void ackRegisterNetwork(unsigned char *IEEEAddress,unsigned short NetAddress,ackCmd_t cmd)
{
	int i;
	char wbuf[14];
	char str1[10];
    char str2[10];
	unsigned char *ieeeAddress = IEEEAddress;
	wbuf[0] = 'C';
	wbuf[1] = 'F';
	wbuf[2] = 'G';	
	wbuf[3] = cmdAckCheckIn;	
	strncpy(&wbuf[4],(const char *)ieeeAddress,8);
	wbuf[11] = cmd;
	wbuf[12] = NetAddress >> 8;
	wbuf[13] = NetAddress;
	
	set_temporary_cast_mode(unicast);
	WriteComPort((unsigned char *)wbuf, 14);

	strcpy(str1,"");
    for(i = 0;i < 8;i++)
    {
        sprintf(str2,"%02x",*((const char *)ieeeAddress)&0x0ff);
        strcat(str1,str2);
		ieeeAddress ++;
    }
	if(cmd == Allow)
		printf("have ack 0x%s allocate local address is 0x%04x allow...\r\n",str1,NetAddress);
	else
		printf("have ack 0x%s allocate local address is 0x%04x refuse...\r\n",str1,NetAddress);
}

void changeNodeType(unsigned char *IEEEaddress,devTypeCmd_t deviceType)
{
	int i;
	char wbuf[14];
	char str1[10];
    char str2[10];
	unsigned char *ieeeAddress = IEEEaddress;
	wbuf[0] = 'C';
	wbuf[1] = 'F';
	wbuf[2] = 'G';	
	wbuf[3] = cmdChangNodeTye;
	strncpy(&wbuf[4],(const char *)ieeeAddress,8);
	wbuf[11] = deviceType;
	
	set_temporary_cast_mode(unicast);
	WriteComPort((unsigned char *)wbuf, 12);
	
	strcpy(str1,""); 
    for(i = 0;i < 8;i++)
    {
        sprintf(str2,"%02x",*((const char *)ieeeAddress)&0x0ff);
        strcat(str1,str2);
		ieeeAddress ++;
    }
	if(deviceType == endDevice)
		printf("have changed 0x%s deviceType : endDevice...\r\n",str1);
	else
		printf("have changed 0x%s deviceType : routerDevice...\r\n",str1);
}

void changePanidChannel(unsigned short panid,unsigned short channel)
{
	char wbuf[8];
	
	wbuf[0] = 'C';
	wbuf[1] = 'F';
	wbuf[2] = 'G';
	wbuf[3] = cmdChangPanidChannel;
	wbuf[4] = panid >> 8;
	wbuf[5] = panid;
	wbuf[6] = channel >> 8;
	wbuf[7] = channel;
	
	set_temporary_cast_mode(broadcast);
	WriteComPort((unsigned char *)wbuf, 8);
	
	printf("have changed all node's panid to 0x%04x,channel to %d...\r\n",panid,channel);	
}

void resetAllNode(void)
{
	char wbuf[4];
	
	wbuf[0] = 'C';
	wbuf[1] = 'F';
	wbuf[2] = 'G';
	wbuf[3] = cmdAllNodeReset;
	
	set_temporary_cast_mode(broadcast);
	WriteComPort((unsigned char *)wbuf, 4);
	
	printf("have reset all node...\r\n");
}

void testLink(void)
{
	unsigned char wbuf[4];
	
	wbuf[0] = 'C';
	wbuf[1] = 'F';
	wbuf[2] = 'G';
	wbuf[3] = cmdLinkTest;
	
	set_temporary_cast_mode(unicast);
	WriteComPort( wbuf, 4);
	
	printf("taking link test...\r\n");
}

void startSensorCalibration(void)
{
	unsigned char wbuf[4];
	
	wbuf[0] = 'S';
	wbuf[1] = 'E';
	wbuf[2] = 'N';
	wbuf[3] = cmdSensorCal;
	
	set_temporary_cast_mode(broadcast);
	WriteComPort(wbuf, 4);
	
	printf("taking sensor calibration...\r\n"); 
}

void testBeep(unsigned short DstAddr,unsigned char cmd)
{
	unsigned char wbuf[5];
	
	wbuf[0] = 'T';
	wbuf[1] = 'S';
	wbuf[2] = 'T';
	wbuf[3] = cmdBeepTest;
	wbuf[4] = cmd;
	
	set_temporary_DestAddr(DstAddr);
	set_temporary_cast_mode(unicast);
	WriteComPort(wbuf, 5);
	
	if(cmd == cmdSilence)
		printf("beep start to silence...\r\n");
	else
		printf("beep start to buzzing...\r\n");
}

void testLed(unsigned short DstAddr,unsigned char ioLevel)
{
	unsigned char wbuf[5];
	
	wbuf[0] = 'T';
	wbuf[1] = 'S';
	wbuf[2] = 'T';
	wbuf[3] = cmdLedTest;
	wbuf[4] = ioLevel;
	
	set_temporary_DestAddr(DstAddr);
	set_temporary_cast_mode(unicast);
	WriteComPort(wbuf, 5);
	
	printf("led value is : 0x%02x\r\n",ioLevel);
}

void testMotor(unsigned short DstAddr,unsigned char cmd)
{
	unsigned char wbuf[5];
	
	wbuf[0] = 'T';
	wbuf[1] = 'S';
	wbuf[2] = 'T';
	wbuf[3] = cmdLedTest;
	wbuf[4] = cmd;
	
	set_temporary_DestAddr(DstAddr);
	set_temporary_cast_mode(unicast);
	WriteComPort(wbuf, 5);
	
	switch(cmd)
	{
		case cmdStop:
			printf("motor is stop...\r\n");
		break;
		case cmdForward:
			printf("motor is forwarding...\r\n");
		break;
		case cmdReverse:
			printf("motor is reversing...\r\n");
		break;
		default:
			printf("cmd is error...\r\n");
		break;
	}
}