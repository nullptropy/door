CC     = arduino-cli
FQBN   = esp8266:esp8266:nodemcu
CONF   = ./.arduino-cli.yaml
PORT   = /dev/ttyUSB0
SKETCH = firmware

init:
	$(CC) core install esp8266:esp8266 --config-file $(CONF)

compile:
	$(CC) compile --fqbn $(FQBN) $(SKETCH)

upload:
	$(CC) upload -p $(PORT) --fqbn $(FQBN) $(SKETCH)

run: compile upload

.PHONY: init compile upload run
