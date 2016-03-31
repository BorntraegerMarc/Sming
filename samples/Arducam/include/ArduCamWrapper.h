#include "WString.h"
#include <Libraries/ArduCam/ArduCAM.h>
#include <SmingCore/SmingCore.h>

class ArduCamWrapper {
public:
	ArduCamWrapper(ArduCAM *CAM);
	virtual ~ArduCamWrapper();
	void initCam();
	void startCapture();
private:
	ArduCAM *myCAM;
};
