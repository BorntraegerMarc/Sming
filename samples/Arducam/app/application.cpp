#include <user_config.h>
#include <SmingCore/SmingCore.h>
#include <SmingCore/Debug.h>

#include <ArduCamWrapper.h>

#include <Libraries/ArduCam/ArduCAM.h>
#include <Libraries/ArduCAM/ov2640_regs.h>

#include <Libraries/ArduCam/ArduCAMStream.h>
#include <Services/HexDump/HexDump.h>

// If you want, you can define WiFi settings globally in Eclipse Environment Variables
#ifndef WIFI_SSID
#define WIFI_SSID "ti8m-Airport" // Put you SSID and Password here
#define WIFI_PWD "H4ck-An_4pp"
#endif

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

HttpServer server;

ArduCAM myCAM(OV2640, CAM_CS);

ArduCamWrapper arduCamWrapper(&myCAM);

/*
 * default http handler to check if server is up and running
 */
void onIndex(HttpRequest &request, HttpResponse &response) {
	TemplateFileStream *tmpl = new TemplateFileStream("index.html");
	auto &vars = tmpl->variables();
	response.sendTemplate(tmpl); // will be automatically deleted
}

void onFile(HttpRequest &request, HttpResponse &response) {
	String file = request.getPath();
	if (file[0] == '/')
		file = file.substring(1);

	if (file[0] == '.')
		response.forbidden();
	else {
		response.setCache(86400, true); // It's important to use cache for better performance.
		response.sendFile(file);
	}
}

void onCamSetup(HttpRequest &request, HttpResponse &response) {
	String size, type;

	if (request.getRequestMethod() == RequestMethod::POST) {
		type = request.getPostParameter("type");
		debugf("set type %s", type);
		arduCamWrapper.set_type(type);

		size = request.getPostParameter("size");
		debugf("set size %s", size);
		arduCamWrapper.set_size(size);
	}

	response.sendString("OK");
}

/*
 * http request to capture and send an image from the cammera
 * uses actual setting set by ArdCammCommand Handler
 */
void onCapture(HttpRequest &request, HttpResponse &response) {
	Serial.printf("perform onCapture()\r\n");

	// TODO: use request parameters to overwrite camera settings
	// setupCamera(camSettings);
	myCAM.clear_fifo_flag();
	myCAM.write_reg(ARDUCHIP_FRAMES, 0x00);

	// get the picture
	arduCamWrapper.startCapture();

	ArduCAMStream *stream = new ArduCAMStream(&myCAM);

	const char * contentType = arduCamWrapper.getContentType();

	if (stream->dataReady()) {
		response.setHeader("Content Lenght", String(stream->available()));
		response.sendDataStream(stream, contentType);
	}
}

/*
 * start http server
 */
void StartServers() {
	server.listen(80);
	server.addPath("/", onIndex);
	server.addPath("/cam/set", onCamSetup);
	server.addPath("/cam/capture", onCapture);
	server.setDefaultHandler(onFile);

	Serial.println("\r\n=== WEB SERVER STARTED ===");
	Serial.println(WifiStation.getIP());
	Serial.println("==============================\r\n");
}

// Will be called when WiFi station was connected to AP
void connectOk() {
	Serial.println("I'm CONNECTED");
	StartServers();
}

void init() {
	spiffs_mount(); // Mount file system, in order to work with files

	Serial.begin(SERIAL_BAUD_RATE); // 115200 by default
	Serial.systemDebugOutput(true); // Allow debug output to serial

	Debug.setDebug(Serial);

	Serial.systemDebugOutput(true); // Enable debug output to serial
	Serial.commandProcessing(true);

	WifiStation.enable(true);
	WifiStation.config(WIFI_SSID, WIFI_PWD);
	WifiAccessPoint.enable(false);

	// Run our method when station was connected to AP
	WifiStation.waitConnection(connectOk);

	// setup the ArduCAM
	arduCamWrapper.initCam();
}
