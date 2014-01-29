// OculusRiftSensorOnly.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>

#include "OculusSensor.h"

// MAIN function
int _tmain(int argc, _TCHAR* argv[]){
	bool sysFlg;
	int stat;
	OVR::System::Init(OVR::Log::ConfigureDefaultLog(OVR::LogMask_All));
	OculusSensor *mainObj = new OculusSensor;
	sysFlg = mainObj->OnInit();
	if (!sysFlg){
		printf_s("Error occured in initialization process.\n");
		return 1;
	}
	else{
		printf_s("Initialization has been done.\n");
	}

	sysFlg = mainObj->setReptTime(10);
	if (sysFlg){
		printf_s("Recieving sensor data from OculusRift...\n");
		stat = mainObj->Run();
	}

	delete mainObj;
	OVR::System::Destroy();
	return 0;
}
