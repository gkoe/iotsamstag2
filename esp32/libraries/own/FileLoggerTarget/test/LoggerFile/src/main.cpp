#include <Arduino.h>
#include <Logger.h>
#include <SPIFFS.h>
#include <FileLoggerTarget.h>
#include <ThingTime.h>
#include <HttpServer.h>

void handleRootTest() {
	String message = "Number of args received:";
	message += HttpServer.args();           //Get number of parameters
	message += "\n";                            //Add a new line
	for (int i = 0; i < HttpServer.args(); i++) {
		message += "Arg " + (String)i +  ": ";   //Include the current iteration value
		message += HttpServer.argName(i) + ": ";     //Get the name of the parameter
		message += HttpServer.arg(i) + "\n";              //Get the value of the parameter
	} 
	HttpServer.send( 200, "text/html",message);       //Response to the HTTP request
}

int logLevel = 0;
LoggerTarget* flg;

void setup() {
	Serial.begin(115200);
	Logger.init("test");
  flg = new FileLoggerTarget("test", 0, 100);
  Logger.addLoggerTarget(flg);
  ThingTime.setNtpTimeSubscriber();
  HttpServer.init();
	HttpServer.on("/", handleRootTest);
}

int readFile = 1;
void loop() {
	delay(1000);
  Logger.info("Main-Loop", "Logtest Level: 0");
  Logger.debug("Main-Loop", "Logtest Level: 1");
  Logger.exception("Main-Loop", "Logtest Level: 2");
  Logger.error("Main-Loop", "Logtest Level: 3");
  Logger.fatalerror("Main-Loop", "Logtest Level: 4");
  Logger.nolog("Main-Loop", "Logtest Level: 5");
  if(logLevel == LOG_LEVEL_NOLOG){
      logLevel = LOG_LEVEL_INFO;
      flg->setType(logLevel);
      Serial.println("");
  } else {
      logLevel++;
      flg->setType(logLevel);
  }
}
