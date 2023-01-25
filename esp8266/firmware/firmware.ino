#include "config.ipp"

void setup() {
    // TODO: init serial comm properly
    Serial.begin(9600);
    // TODO: init wifi
    wifi_init();
    // TODO: init rfid readers
    rfid_init_readers();
}

void loop() {
    uint8_t reader; uint32_t uid;
    if (!rfid_read_card(&uid, &reader)) return;

    Serial.print(reader); Serial.print(":uid:"); Serial.println(uid);

    // if (WiFi.status() == WL_CONNECTED) {
    //     char request_body[20];
    //     WiFiClient client;
    //     HTTPClient http;

    //     http.begin(client, i == 0 ? LOGIN_REMOTE_ADDR : EXIT_REMOTE_ADDR);
    //     http.addHeader("Content-Type", "application/json");

    //     snprintf(request_body, sizeof(request_body), "{\"uid\": %zu}", uid);
    //     Serial.print("reader: "); Serial.print(i);
    //     Serial.print(" request_body: "); Serial.print(request_body);
    //     int http_code = http.POST(request_body);
    // }
}
