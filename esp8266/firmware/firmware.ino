#include "config.ipp"

// function to write formatted text as serial output
void printfs(const char *fmt, ...);

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
    printfs("[INFO] new card read: %u:%u\n", reader, uid)

    if (!wifi_check_connectivity()) {
        printfs("[WARN] not connected to wifi\n");
        wifi_connect_loop();
        return;
    }

    printfs("[INFO] access: %d\n", wifi_request_access(uid, reader));
}

// function to write formatted text as serial output
void printfs(const char *fmt, ...) {
    char buf[256];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    Serial.print(buf);
}
