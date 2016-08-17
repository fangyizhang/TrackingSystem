#include <iostream>
#include <fstream>
#include "json/json.h"
#include "protocal/CANProtocal.h"
using namespace std;

int main(){
	CANProtocal* canProtocal = CANProtocal::getInstance();
	Json::Value root;
	Json::Reader reader;
	ifstream istream("configure/can.json");
	if (reader.parse(istream, root)){
		cout << "can configure file error!" << endl;
	}
	cout << root.get("deviceType", 20).asInt() << endl;
	cout << root.get("deviceIdx", 0).asInt() << endl;
	cout << root.get("baudRate", 0x060003).asInt() << endl;
	getchar();
	canProtocal->close();
	return 0;
}