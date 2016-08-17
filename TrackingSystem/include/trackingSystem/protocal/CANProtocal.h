#ifndef CAN_PROTOCAL_H
#define CAN_PROTOCAL_H

#include "ComProtocal.h"
#include "ControlCAN.h"
#include "Windows.h"

/*
 @author fangyi zhang
 @date 2016-08-15
 */
//@singleton
class CANProtocal : ComProtocal {
private:
	int deviceType = VCI_USBCAN_E_U;
	int deviceIdx = 0;
	int baudRate = 0x060003;
	int CANIdx = 0;
	int CANStatus = 0;
	int reserved = 0;
	int refType = 0;
	UINT frameId = 0x00;
	int sendType = 0;
	int remoteFlag = 0;
	int externFlag = 0;
	VCI_CAN_OBJ vco[1];

	static CANProtocal* canProtocal;

	CANProtocal();
	/*
	@description: init CAN, ready for data send and receive
	@ret: 0-init success, -1 fail
	*/
	int init();


public:
	static CANProtocal* getInstance();


	/*
	 @description: send data, 
	 @param
	 @param
	 @ret: 
	 */
	//@override
	int send(BYTE* data, BYTE dataLen);
	
	/*
	 @description: receive data,
	 @param
	 @ret
	 */
	//@override
	int receive(BYTE* data, BYTE* dataLen);

	/*
	 @description: close CAN device
	 */
	int close();

	~CANProtocal();
};

#endif