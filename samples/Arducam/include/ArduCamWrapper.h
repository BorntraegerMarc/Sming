#include "WString.h"
#include <Libraries/ArduCam/ArduCAM.h>
#include <SmingCore/SmingCore.h>

class ArduCamWrapper {
public:
	ArduCamWrapper(ArduCAM *CAM);
	virtual ~ArduCamWrapper();
	void initCam();
	void startCapture();
	const char * getContentType();
	void set_size(String size);
	void set_type(String type);

private:
	ArduCAM *myCAM;
	uint8 imgType;
	uint8 imgSize;

	void set_format(uint8 type);
};
