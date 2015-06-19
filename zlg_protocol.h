#ifndef __ZLG_PROTOCOL_H__
#define __ZLG_PROTOCOL_H__

typedef enum ackCmd {
	Allow = 0x01,
	Refuse = 0x00
}ackCmd_t;

typedef enum devTypeCmd {
	endDevice = 0x00,
	routerDevice = 0x01
}devTypeCmd_t;

enum cfg_cmd {
	cmdAckCheckIn = 0x01,
	cmdChangNodeTye = 0x02,
	cmdChangPanidChannel = 0x04,
	cmdAllNodeReset = 0x05,
	cmdLinkTest = 0x06
};

enum sen_cmd {
	cmdSensorCal = 0x00,
};

enum tst_cmd {
	cmdBeepTest = 0x00,
	cmdLedTest = 0x01,
	cmdMotorTest = 0x02
};

enum beep_cmd {
	cmdSilence = 0x00,
	cmdBuzz = 0x01
};

enum motor_cmd {
	cmdStop = 0x00,
	cmdForward = 0x01,
	cmdReverse = 0x02
};

void ackRegisterNetwork(unsigned char *IEEEAddress,unsigned short NetAddress,ackCmd_t cmd);
void changeNodeType(unsigned char *IEEEaddress,devTypeCmd_t deviceType);
void changePanidChannel(unsigned short panid,unsigned short channel);
void resetAllNode(void);
void testLink(void);
void startSensorCalibration(void);
void testBeep(unsigned short DstAddr,unsigned char cmd);
void testLed(unsigned short DstAddr,unsigned char ioLevel);
void testMotor(unsigned short DstAddr,unsigned char cmd);

#endif
