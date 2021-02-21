
# ESP32cam IoT plant monitoring system

## Setup
### Requirements
* VS code + platformio

## Usage

## Todo
### Software todo
* [x] Read temp and hum
* [x] Read soil
* [x] Read battery voltage
* [x] Use light sleep
* [x] OTA updates
* [x] Log to tensorboard
* [x] Device attributes log to tb
* [ ] More device attributes?
* [ ] Take picture
* [ ] Log picture to a server
* [ ] More code cleanup

### Hardware todo
* [ ] Design container
* [ ] Prototype container
* [ ] Improve container
## Important Notes
### Hardware notes
* After uploading new software, unpower the device completely, making sure that the voltage regulator discharges. Or else the ADCs wont read correctly.
