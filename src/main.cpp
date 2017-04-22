#include <ESP8266-Telegram.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

#include <private.h>

#define DSERIAL Serial

//SoftwareSerial debug_serial(0, 2);

WiFiClientSecure client;

TelegramBot bot(TELEGRAM_TOKEN, client);

uint32_t parseUint32_t(Stream &stream) {
  uint32_t val = 0;
  int c = '0';

  bool found_digit = false;

  while(c >= '0' && c <= '9') {
    while(!stream.available());
    c = stream.read();

    if (c >= '0' && c <= '9') {
      found_digit = true;

      val = val * 10 + (c - '0');
    }
    else {
      if (found_digit) {
        return val;
      }
    }
  }
}

void setup() {
  Serial1.begin(115200);
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

  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");

  bot.set_debug_serial(&DSERIAL);

  DSERIAL.println("Setup done!");
}

void loop() {
  static uint8_t count = 0;
  static uint32_t message_id = 0;

  uint32_t cur_bytes = 0, total_bytes = 0;

  if (message_id == 0) {
    message_id = bot.send_message(TARGET_CHAT_ID, "Starting...");
    return;
  }

  Serial1.println("M27");
  /*if (Serial1.find("SD printing byte ")) {
    cur_bytes = parseUint32_t(Serial1);
    total_bytes = parseUint32_t(Serial1);
  }*/

  Serial1.println("M105");
  String tmp_response = Serial.readString();


  bot.edit_message(TARGET_CHAT_ID, message_id, tmp_response);
}
