#include "OVR.h"
#include "Kernel/OVR_KeyCodes.h"

using namespace OVR;

class OculusSensor :public NewOverrideBase{
private:
	Ptr<DeviceManager> pManager;
	Ptr<SensorDevice>  pSensor;
	SensorFusion       SFusion;

	bool Quit;
	int ExitCode;
	DWORD reptTime;  // repetition time for sending message from Oculus rift to server

public:
	OculusSensor();
	~OculusSensor();
	bool OnInit(void);
	int Run(void);
	void OnMeasure();
	void OnKey(KeyCode key, int chr, bool down, int modifiers);
	void Exit(int exitcode);
	bool setReptTime(DWORD tm);
};
