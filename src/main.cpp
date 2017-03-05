
#include <FS.h> //this needs to be first, or it all crashes and burns...
#include "functions/PrintFunction.h"
#include "functions/CountFunction.h"
#include "Metal.h"


#define TRIGGER_PIN 0


Metal* metal = new Metal(2);
auto countFunction = new CountFunction("count");
auto sayFunction = new PrintFunction("print", &Serial);


void setup() {

  pinMode(TRIGGER_PIN, INPUT);
  Serial.begin(9600);

  Serial << "Metal put functions";
  metal->put(sayFunction);
  metal->put(countFunction);

  Serial << "Metal init wifi Manager";
  metal->initWifiManager();
  metal->execute("print:Hello World!");

}

void loop() {
  if ( digitalRead(TRIGGER_PIN) == LOW ) {
      metal->startConfigPortal();
  }
}
