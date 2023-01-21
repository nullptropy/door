CC     = arduino-cli
FQBN   = esp8266:esp8266:nodemcu
CONF   = ./.arduino-cli.yaml
PORT   = /dev/ttyUSB0
SKETCH = firmware

init:
	$(CC) core update-index --config-file $(CONF)
	$(CC) core install esp8266:esp8266 --config-file $(CONF)

compile:
	$(CC) compile --fqbn $(FQBN) $(SKETCH) --config-file $(CONF)

upload:
	$(CC) upload -p $(PORT) --fqbn $(FQBN) $(SKETCH) --config-file $(CONF)

run: compile upload

.PHONY: init compile upload run
