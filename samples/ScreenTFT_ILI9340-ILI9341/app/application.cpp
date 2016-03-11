#include <user_config.h>
#include <SmingCore/SmingCore.h>
#include <Libraries/Adafruit_ILI9340/Adafruit_ILI9341.h>

// If you want, you can define WiFi settings globally in Eclipse Environment Variables
#ifndef WIFI_SSID
	#define WIFI_SSID "PleaseEnterSSID" // Put you SSID and Password here
	#define WIFI_PWD "PleaseEnterPass"
#endif

/*
Pinout:
MISO GPIO12
MOSI GPIO13
CLK GPIO14
CS GPIO15
DC GPIO5
RST GPIO4
*/
int8_t CS = 15;
int8_t DC = 5;
int8_t RST = 4;

Adafruit_ILI9341 tft(15, 5, 4);

Timer guiTimer;
Timer DemoScreenTimer;
float p = 3.1415926;
uint32_t startTime;

int r=0;

int ara=4,yerara=15;
int u1=100;
int u2=320-(u1+ara);
int s1=0;
int s2=(u1+ara);
int p1=50;


int g=28;
int y=90;
int satir=6;

String lists[]={"a","b","c","d","e","f"};

void basicGui()
{
	tft.setTextSize(1);

	tft.setRotation(1);

	tft.setTextSize(3);
	tft.fillRect(s1,0,u1*2,48,ILI9341_OLIVE);
	tft.setCursor(15,15);
	tft.println("Sming");
	tft.setTextSize(2);
	tft.fillRect((u1*2)+ara,0,318-(u1*2),48,ILI9341_RED);
		for(int a=0;a<satir;a++)
		{
				tft.setTextColor(ILI9341_GREEN);
				tft.fillRect(s1,p1,u1,g,ILI9341_DARKCYAN);
				tft.setCursor(s1+yerara,p1+6);
				tft.setTextColor(ILI9341_WHITE);
				tft.println(lists[a]);
				tft.fillRect(s2,p1,u2,g,ILI9341_DARKCYAN);
				tft.setCursor(s2+yerara,p1+6);
				tft.println(r);
				p1+=g+4;
		}
		p1=50;
		r++;

}

void testdrawtext(const char text[], uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void tftPrintTest1() {
  tft.setTextWrap(false);
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(1);
  tft.println("Hello Sming!");
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);
  tft.println("Hello Sming!");
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(3);
  tft.println("Hello Sming!");
  tft.setTextColor(ILI9341_BLUE);
  tft.setTextSize(4);
  tft.print(1234.567);
}

void tftPrintTest2() {
  tft.setCursor(0, 0);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(0);
  tft.println("Hello Sming!");
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_GREEN);
  tft.print(p, 6);
  tft.println(" Want pi?");
  tft.println(" ");
  tft.print(8675309, HEX); // print 8,675,309 out in HEX!
  tft.println(" Print HEX!");
  tft.println(" ");
  tft.setTextColor(ILI9341_WHITE);
  tft.println("Sketch has been");
  tft.println("running for: ");
  tft.setTextColor(ILI9341_MAGENTA);
  tft.print(millis() / 1000);
  tft.setTextColor(ILI9341_WHITE);
  tft.print(" seconds.");
}

void testlines(uint16_t color) {
  tft.fillScreen(ILI9341_BLACK);

  WDT.enable(false);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, 0, x, tft.height()-1, color);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, 0, tft.width()-1, y, color);
  }

  tft.fillScreen(ILI9341_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, 0, x, tft.height()-1, color);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, 0, 0, y, color);
  }
  WDT.enable(true);


  // TODO: drawing from all 4 corners does kick in a watchdog reboot !
  /*

  tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, tft.height()-1, x, 0, color);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, tft.height()-1, tft.width()-1, y, color);
  }

  tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, x, 0, color);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, 0, y, color);
  }
  */
}

void testfastlines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ILI9341_BLACK);
  for (int16_t y=0; y < tft.height(); y+=5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x=0; x < tft.width(); x+=5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}

void testdrawrects(uint16_t color) {
  tft.fillScreen(ILI9341_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ILI9341_BLACK);
  for (int16_t x=tft.width()-1; x > 6; x-=6) {
    tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
    WDT.alive();
  }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < tft.width(); x+=radius*2) {
    for (int16_t y=radius; y < tft.height(); y+=radius*2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < tft.width()+radius; x+=radius*2) {
    for (int16_t y=0; y < tft.height()+radius; y+=radius*2) {
      tft.drawCircle(x, y, radius, color);
    }
  }
}

void testroundrects() {
  tft.fillScreen(ILI9341_BLACK);
  int color = 100;
  int i;
  int t;
  for(t = 0 ; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = tft.width()-2;
    int h = tft.height()-2;
    for(i = 0 ; i <= 16; i+=1) {
      tft.drawRoundRect(x, y, w, h, 5, color);
      x+=2;
      y+=3;
      w-=4;
      h-=6;
      color+=1100;
    }
    color+=100;
  }
}

void testtriangles() {
  tft.fillScreen(ILI9341_BLACK);
  int color = 0xF800;
  int t;
  int w = tft.width()/2;
  int x = tft.height()-1;
  int y = 0;
  int z = tft.width();
  for(t = 0 ; t <= 15; t+=1) {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
}

void mediabuttons() {
  // play
  tft.fillScreen(ILI9341_BLACK);
  tft.fillRoundRect(25, 10, 78, 60, 8, ILI9341_WHITE);
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ILI9341_RED);
  delay(500);
  // pause
  tft.fillRoundRect(25, 90, 78, 60, 8, ILI9341_WHITE);
  tft.fillRoundRect(39, 98, 20, 45, 5, ILI9341_GREEN);
  tft.fillRoundRect(69, 98, 20, 45, 5, ILI9341_GREEN);
  delay(500);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ILI9341_BLUE);
  delay(50);
  // pause color
  tft.fillRoundRect(39, 98, 20, 45, 5, ILI9341_RED);
  tft.fillRoundRect(69, 98, 20, 45, 5, ILI9341_RED);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ILI9341_GREEN);
}

//void screen13() {
//	startTime = millis();
//	debugf("screen13: bmpDraw rotaton %d ms", millis() - startTime);
//	tft.fillScreen(ILI9341_BLACK); // Clear display
//	tft.setRotation(tft.getRotation() + 1); // Inc rotation 90 degrees
//	for (uint8_t i = 0; i < 4; i++)    // Draw 4 parrots
//		bmpDraw(tft, "sming.bmp", tft.width() / 4 * i, tft.height() / 4 * i);
//}

//void screen12() {
//	startTime = millis();
//	bmpDraw(tft, "sming.bmp", 0, 0);
//	debugf("screen12: bmpDraw %d ms", millis() - startTime);
////	DemoScreenTimer.initializeMs(2000, screen13).start(FALSE);
//}

void screen11() {
	startTime = millis();
	mediabuttons();
	debugf("screen11: mediabuttons %d ms", millis() - startTime);
//	DemoScreenTimer.initializeMs(1000, screen12).start(FALSE);
}

void screen10() {
	startTime = millis();
	testtriangles();
	debugf("screen10: testtriangles %d ms", millis() - startTime);
	DemoScreenTimer.initializeMs(1000, screen11).start(FALSE);
}

void screen9() {
	startTime = millis();
	testroundrects();
	debugf("screen9: testroundrects %d ms", millis() - startTime);
	DemoScreenTimer.initializeMs(1000, screen10).start(FALSE);
}

void screen8() {
	startTime = millis();
	tft.fillScreen(ILI9341_BLACK);
	testfillcircles(10, ILI9341_BLUE);
	testdrawcircles(10, ILI9341_WHITE);
	debugf("screen8: testfillcircles %d ms", millis() - startTime);
	DemoScreenTimer.initializeMs(1000, screen9).start(FALSE);
}

void screen7() {
	startTime = millis();
	testfillrects(ILI9341_YELLOW, ILI9341_MAGENTA);
	debugf("screen7: testfillrects %d ms", millis() - startTime);
	DemoScreenTimer.initializeMs(1000, screen8).start(FALSE);
}

void screen6() {
	startTime = millis();
	testdrawrects(ILI9341_GREEN);
	debugf("screen6: testdrawrects %d ms", millis() - startTime);
	DemoScreenTimer.initializeMs(1000, screen7).start(FALSE);
}

void screen5() {
	startTime = millis();
	  // optimized lines
	testfastlines(ILI9341_RED, ILI9341_BLUE);
	debugf("screen5: testfastlines %d ms", millis() - startTime);
	DemoScreenTimer.initializeMs(1000, screen6).start(FALSE);
}

void screen4() {
	startTime = millis();
	// line draw test
	testlines(ILI9341_YELLOW);
	debugf("screen4: testlines %d ms", millis() - startTime);
	DemoScreenTimer.initializeMs(1000, screen5).start(FALSE);
}

void screen3() {
	startTime = millis();
	tftPrintTest2();
	debugf("screen3: tftPrintTest2 %d ms", millis() - startTime);
	DemoScreenTimer.initializeMs(1000, screen4).start(FALSE);
}

void screen2() {
	startTime = millis();
	tftPrintTest1();
	debugf("screen2: tftPrintTest1 %d ms", millis() - startTime);
	DemoScreenTimer.initializeMs(1000, screen3).start(FALSE);
}

void screen1() {
	startTime = millis();
    // large block of text
    tft.fillScreen(ILI9341_BLACK);
    testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", ILI9341_WHITE);
	debugf("screen1: testdrawtext %d ms", millis() - startTime);
	DemoScreenTimer.initializeMs(1000, screen2).start(FALSE);
}


void init()
{
	Serial.begin(SERIAL_BAUD_RATE); // 115200 by default
	Serial.systemDebugOutput(true); // Allow debug output to serial
	//WifiStation.config(WIFI_SSID, WIFI_PWD);
	WifiStation.enable(false);
	WifiAccessPoint.enable(false);
	//	delay(2000);
	Serial.println("Display start");

	// text display tests
	tft.begin();
//	tft.fillScreen(0);
//	tft.setRotation(1);
//	tft.setTextSize(2);
//
//	tft.setTextColor(ILI9341_GREEN);
//	tft.setCursor(0,0);
//	tft.setCursor(60,60);
//	tft.println("Sming  Framework");
//	tft.setTextColor(ILI9341_WHITE,ILI9341_BLACK); // text
//	tft.setCursor(60,75);
//	tft.println("              v1.1");
//	tft.setTextColor(ILI9341_CYAN);
//	tft.setCursor(60,90);
//	tft.println("ili9340-40C-41 ");
//	tft.setCursor(60,125);
//	tft.println("M.Bozkurt");
//	delay(500);
//	tft.fillScreen(0);
//	guiTimer.initializeMs(1000, basicGui).start();
//	//runTest();

	tft.fillScreen(ILI9341_BLACK);
	startTime = millis() - startTime;

	debugf("Initialized in %d ms\n", startTime);

	DemoScreenTimer.initializeMs(500, screen1).start(FALSE);


}
