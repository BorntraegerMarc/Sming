#include <ArduCamWrapper.h>
#include <Libraries/ArduCam/ArduCAM.h>
#include <Libraries/ArduCAM/ov2640_regs.h>

#define CAM_SCL		5
#define CAM_SDA		4

/*
 * Hardware SPI mode:
 * GND      (GND)         GND
 * VCC      (VCC)         3.3v
 * D0       (CLK)         GPIO14
 * D1       (MOSI)        GPIO13
 * CS       (CS)          GPI015
 * RES      (RESET)       GPIO16
 * DC       (DC)          GPIO2
 */
#define CAM_SCLK 	14  // HW SPI pins - dont change
#define CAM_MOSI 	13
#define CAM_MISO	12

#define CAM_CS   	16	// this pins are free to change

ArduCamWrapper::ArduCamWrapper(ArduCAM *arduCam) {
	myCAM = arduCam;
}

ArduCamWrapper::~ArduCamWrapper() {
}

/*
 * initCam()
 *
 * Initalize I2C, SPI Bus and check if the cammera is there
 * Initialize the camera for JPEG 320x240
 *
 */
void ArduCamWrapper::initCam() {
	uint8_t vid, pid = 0;

	Serial.printf("ArduCAM init!");

	// initialize I2C
	Wire.pins(CAM_SCL, CAM_SDA);
	Wire.begin();

	//Check if the camera module type is OV2640
	myCAM->rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
	myCAM->rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);
	if ((vid != 0x26) || (pid != 0x42)) {
		Serial.println("Can't find OV2640 module!");
		Serial.printf("vid = [%X]  pid = [%X]\n", vid, pid);
	} else
		Serial.println("OV2640 detected");

	// initialize SPI:
	pinMode(CAM_CS, OUTPUT);
	digitalWrite(CAM_CS, HIGH);
	SPI.begin();
	SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));

	//Check if the ArduCAM SPI bus is OK
	myCAM->write_reg(ARDUCHIP_TEST1, 0x55);

	uint8_t temp = myCAM->read_reg(ARDUCHIP_TEST1);
	if (temp != 0x55) {
		Serial.println("SPI interface Error!");
		while (1)
			;
	} else {
		Serial.println("SPI interface OK!");
	}

	// init CAM
	Serial.println("Initialize the OV2640 module");
	myCAM->set_format(JPEG);
	myCAM->InitCAM();
}

void ArduCamWrapper::startCapture() {
	myCAM->clear_fifo_flag();
	myCAM->start_capture();
}

void ArduCamWrapper::set_size(String size) {
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

void ArduCamWrapper::set_type(String type) {
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

const char * ArduCamWrapper::getContentType() {
	switch (imgType) {
	case JPEG:
		return "image/jpeg";
	case BMP:
	default:
		return "image/x-ms-bmp";
	}
}

void ArduCamWrapper::set_format(uint8 type) {
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
