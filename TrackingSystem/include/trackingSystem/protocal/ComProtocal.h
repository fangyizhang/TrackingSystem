#ifndef COM_PROTOCAL_H
#define COM_PROTOCAL_H
#include "Windows.h"
/*

*/
class ComProtocal{
	virtual int send(BYTE* data, BYTE dataLen) = 0;
	virtual int receive(BYTE* data, BYTE* dataLen) = 0;
};

#endif