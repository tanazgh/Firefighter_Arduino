#include <BlynkSimpleStream.h>

#define BLYNK_TEMPLATE_ID "TMPL79dGgmOm"
#define BLYNK_DEVICE_NAME "ES"
#define BLYNK_AUTH_TOKEN "mnp5FvnbWhrWYHIHkz_jF0OtZKnNo-c7"
char auth = "mnp5FvnbWhrWYHIHkz_jF0OtZKnNo-c7";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Blynk.begin(Serial, auth);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
}
