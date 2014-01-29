// OculusSensorTest.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>

#include "OculusSensor.h"

OculusSensor::OculusSensor() :
Quit(0),
reptTime(10),
ExitCode(1){
}

OculusSensor::~OculusSensor(){
	pSensor.Clear();
	pManager.Clear();
}

// Initialization of OculusRift
bool OculusSensor::OnInit(){
	pManager = *DeviceManager::Create();

	DeviceEnumerator<SensorDevice> isensor = pManager->EnumerateDevices<SensorDevice>();
	DeviceEnumerator<SensorDevice> oculusSensor;

	while (isensor){
		DeviceInfo di;
		if (isensor.GetDeviceInfo(&di)){
			if (strstr(di.ProductName, "Tracker")){
				if (!oculusSensor)
					oculusSensor = isensor;
			}
		}

		isensor.Next();
	}

	if (oculusSensor){
		pSensor = *oculusSensor.CreateDevice();
		if (pSensor)
			pSensor->SetRange(SensorRange(4 * 9.81f, 8 * Math<float>::Pi, 1.0f), true);
	}

	oculusSensor.Clear();

	if (pSensor)
		SFusion.AttachToSensor(pSensor);

	return true;
}

// Running procedure
int OculusSensor::Run(){
	printf_s("tracking OculusRift's sensors...\n");

	while (!Quit){
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			if (msg.message == WM_QUIT) this->Exit(0);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else{
			this->OnMeasure();  // measure and sending data
		}
		Sleep(reptTime);
	}

	return ExitCode;
}

// set repetition time
bool OculusSensor::setReptTime(DWORD tm){
	reptTime = tm;
	return true;
}


// Display positional variables measured by OculusRift
void OculusSensor::OnMeasure(){
	Quatf q = SFusion.GetOrientation();
	Vector3f downVector(0.0f, -1.0f, 0.0f);
	Vector3f val = q.Rotate(downVector);
	float dispval = RadToDegree(downVector.Angle(val));
	printf("DownAngle[deg.] %f \r", dispval);
}

// Keyboard input selecter for control of this app.
void OculusSensor::OnKey(KeyCode key, int chr, bool down, int modifiers){
	OVR_UNUSED2(chr, modifiers);

	switch (key){
	case Key_Q:
		if (!down)
			this->Exit(0);
		break;
	default:
		break;
	}
}

// Exit call
void OculusSensor::Exit(int exitcode){
	Quit = true;
	ExitCode = exitcode;
}
