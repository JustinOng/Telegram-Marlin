#include <ESP8266-Telegram.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

#include <private.h>

#define DSERIAL debug_serial

SoftwareSerial debug_serial(0, 2);

WiFiClientSecure client;

TelegramBot bot(TELEGRAM_TOKEN, client);

void setup() {
  Serial.begin(115200);
  DSERIAL.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WiFiSSID, WiFiPSK);
  DSERIAL.println("Connecting...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    DSERIAL.print(".");
  }

  DSERIAL.println("");
  DSERIAL.println("WiFi connected");
  DSERIAL.println("IP address: ");
  DSERIAL.println(WiFi.localIP());

  bot.set_debug_serial(&DSERIAL);

  /*if (bot.begin()) {
    DSERIAL.println("Bot initialised");
  }
  else {
    DSERIAL.println("Failed to initialise bot!");
    while(1);
  }*/
  DSERIAL.println("Done!");
}

void loop() {
  DSERIAL.println(bot.send_message("298678734", "Hello!"));
  //DSERIAL.println("Hello!");
  delay(5000);
}
