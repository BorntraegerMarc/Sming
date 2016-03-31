#include <ArduCamCommand.h>
#include <Libraries/ArduCam/ArduCAM.h>
#include <Libraries/ArduCAM/ov2640_regs.h>

ArduCamCommand::ArduCamCommand(ArduCAM *CAM) {
	debugf("ArduCamCommand Instantiating");
	myCAM = CAM;
	imgSize = OV2640_320x240;
	imgType = JPEG;
}

ArduCamCommand::~ArduCamCommand() {
}

void ArduCamCommand::set_size(String size) {
	if (size == "160x120") {
		imgSize = OV2640_160x120;
		myCAM->OV2640_set_JPEG_size(OV2640_160x120);
		set_format(JPEG);
	} else if (size == "176x144") {
		imgSize = OV2640_176x144;
		myCAM->OV2640_set_JPEG_size(OV2640_176x144);
		set_format(JPEG);
	} else if (size == "320x240") {
		imgSize = OV2640_320x240;
		myCAM->OV2640_set_JPEG_size(OV2640_320x240);
	} else if (size == "352x288") {
		imgSize = OV2640_352x288;
		myCAM->OV2640_set_JPEG_size(OV2640_352x288);
		set_format(JPEG);
	} else if (size == "640x480") {
		imgSize = OV2640_640x480;
		myCAM->OV2640_set_JPEG_size(OV2640_640x480);
		set_format(JPEG);
	} else if (size == "800x600") {
		imgSize = OV2640_800x600;
		myCAM->OV2640_set_JPEG_size(OV2640_800x600);
		set_format(JPEG);
	} else if (size == "1024x768") {
		imgSize = OV2640_1024x768;
		myCAM->OV2640_set_JPEG_size(OV2640_1024x768);
		set_format(JPEG);
	} else if (size == "1280x1024") {
		imgSize = OV2640_1280x1024;
		myCAM->OV2640_set_JPEG_size(OV2640_1280x1024);
		set_format(JPEG);
	} else if (size == "1600x1200") {
		imgSize = OV2640_1600x1200;
		myCAM->OV2640_set_JPEG_size(OV2640_1600x1200);
		set_format(JPEG);
	} else {
		debugf("ERROR: invalid size definition[%s]\r\n", size);
	}
}

void ArduCamCommand::set_type(String type) {
	if (type == "BMP") {
		myCAM->set_format(BMP);
		if (imgType != BMP) {
			// reset the cam
			myCAM->InitCAM();
			imgType = BMP;
			imgSize = OV2640_320x240;
		}
	} else {
		myCAM->set_format(JPEG);
		// reset the cam
		if (imgType != JPEG) {
			// reset the cam
			myCAM->InitCAM();
			myCAM->OV2640_set_JPEG_size(imgSize);
			imgType = JPEG;
		}
	}
}

void ArduCamCommand::set_format(uint8 type) {
	if (type == BMP) {
		myCAM->set_format(BMP);
		if (imgType != BMP) {
			// reset the cam
			myCAM->InitCAM();
			imgType = BMP;
			imgSize = OV2640_320x240;
		}
	} else {
		myCAM->set_format(JPEG);
		// reset the cam
		if (imgType != JPEG) {
			// reset the cam
			myCAM->InitCAM();
			myCAM->OV2640_set_JPEG_size(imgSize);
			imgType = JPEG;
		}
	}
}

const char * ArduCamCommand::getImageType() {
	switch (imgType) {
	case JPEG:
		return "JPEG";
	case BMP:
	default:
		return "BMP";
	}
}

const char * ArduCamCommand::getContentType() {
	switch (imgType) {
	case JPEG:
		return "image/jpeg";
	case BMP:
	default:
		return "image/x-ms-bmp";
	}
}

const char * ArduCamCommand::getImageSize() {
	switch (imgSize) {
	case OV2640_1600x1200:
		return "1600x1200";
	case OV2640_1280x1024:
		return "1280x1024";
	case OV2640_1024x768:
		return "1024x768";
	case OV2640_800x600:
		return "800x600";
	case OV2640_640x480:
		return "640x480";
	case OV2640_352x288:
		return "352x288";
	case OV2640_320x240:
		return "320x240";
	case OV2640_176x144:
		return "176x144";
	case OV2640_160x120:
		return "160x120";
	default:
		return "320x240";
	}
}

