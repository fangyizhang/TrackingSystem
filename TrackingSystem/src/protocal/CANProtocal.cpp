#include "protocal/CANProtocal.h"
#include <iostream>


CANProtocal* CANProtocal::canProtocal = NULL;

CANProtocal::CANProtocal(){
	init();
	vco[0].SendType = sendType;
	vco[0].RemoteFlag = remoteFlag;
	vco[0].ExternFlag = externFlag;
}

CANProtocal* CANProtocal::getInstance(){
	if (canProtocal == NULL)
		canProtocal = new CANProtocal();
	return canProtocal;
}

int CANProtocal::init(){
	//TODO write sysinfo to log file
	// Open device
	if (VCI_OpenDevice(deviceType, deviceIdx, reserved) != STATUS_OK){
		std::cout << "Open CAN device error" << std::endl;
		return -1;
	}
	else {
		std::cout << "Open CAN device success" << std::endl;
	}

	// Set BaudRate 
	if (VCI_SetReference(deviceType, deviceIdx, CANIdx, refType, &baudRate) != STATUS_OK){
		std::cout << "Set bitRate error" << std::endl;
		return -1;
	}
	else{
		std::cout << "Set bitRate success" << std::endl;
	}

	// Init CAN
	VCI_INIT_CONFIG vic;
	vic.Mode = 0;
	if (VCI_InitCAN(deviceType, deviceIdx, CANIdx, &vic) != STATUS_OK){
		std::cout << "Init CAN device error" << std::endl;
		return -1;
	}
	else{
		std::cout << "Init CAN device sucess" << std::endl;
	}

	// Start CAN
	if (VCI_StartCAN(deviceType, deviceIdx, CANIdx) != STATUS_OK){
		std::cout << "Start CAN error" << std::endl;
		return -1;
	}
	else{
		std::cout << "Start CAN success" << std::endl;
	}
	return 0;
}

int CANProtocal::send(BYTE* data, BYTE dataLen){
	vco[0].ID = frameId;
	vco[0].DataLen = dataLen;
	for (int i = 0; i < dataLen; i++){
		vco[0].Data[i] = data[i];
	}
	return VCI_Transmit(deviceType, deviceIdx, CANIdx, vco, 1);
}

int CANProtocal::receive(BYTE* data, BYTE* dataLen){
	DWORD recNum = VCI_GetReceiveNum(deviceType, deviceIdx, CANIdx);
	//TODO
	return 0;
}

int CANProtocal::close(){
	if (VCI_CloseDevice(deviceType, deviceIdx) != STATUS_OK){
		std::cout << "Close device error" << std::endl;
		return -1;
	}
	else{
		std::cout << "Close device success" << std::endl;
	}
	return 0;
}

CANProtocal::~CANProtocal(){
	delete canProtocal;
}