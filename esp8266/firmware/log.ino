void serial_init(int baudrate) {
    Serial.begin(baudrate);
}

// function to write formatted text as serial output
void serial_printf(const char *fmt, ...) {
    char buf[256];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    Serial.print(buf);
}
