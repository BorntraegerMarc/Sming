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
