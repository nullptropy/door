CMD    = arduino-cli --config-file ./.arduino-cli.yaml
FQBN   = esp8266:esp8266:nodemcu
PORT   = /dev/ttyUSB0
SKETCH = firmware

init:
	$(CMD) core update-index
	$(CMD) core install esp8266:esp8266
	$(CMD) lib install "MFRC522"

compile:
	$(CMD) compile --fqbn $(FQBN) $(SKETCH)

upload:
	$(CMD) upload -p $(PORT) --fqbn $(FQBN) $(SKETCH)

monitor:
	$(CMD) monitor -p $(PORT) --fqbn $(FQBN)

run: compile upload monitor

.PHONY: init compile upload run
