#include "config.ipp"

#define  INFO(fmt, ...) serial_printf("[ INFO] " fmt, ##__VA_ARGS__);
#define  WARN(fmt, ...) serial_printf("[ WARN] " fmt, ##__VA_ARGS__);
#define ERROR(fmt, ...) serial_printf("[ERROR] " fmt, ##__VA_ARGS__);

void setup() {
    serial_init(9600);
    wifi_init();
    rfid_init_readers();
}

void loop() {
    uint8_t reader; uint32_t uid;
    if (!rfid_read_card(&uid, &reader)) return;
    INFO("new card read: %u:%u\n", reader, uid)

    if (!wifi_check_connectivity()) {
        WARN("not connected to wifi\n");
        wifi_connect_loop();
        return;
    }

    INFO("access: %d\n", wifi_request_access(uid, reader));
}

