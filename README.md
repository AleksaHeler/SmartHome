# SmartHome
This is an experimet for making an infrastructure for logging and displaying data on home server.

## Server
For the server I used a Raspberry Pi 3 B+, which is easy to set up and let it work 24/7. Following instructions from [this](https://www.youtube.com/watch?v=a6mjt8tWUws) YouTube video by Andreas Spiess, where he uses [IOTstack](https://github.com/gcgarner/IOTstack) by Graham Garner, it was pretty easy to set up the Raspberry Pi with docker and install containters:
- Mosquitto as MQTT broker
- NodeRed for parsing data
- InfluxDB as timeseries database
- Grafana for displaying all data nicely.

TODO: better explain every program

## Devices
As I currently have only one NodeMCU, I used it to connect with an array of sensors and to publish readings frequently to the local server. TODO: explain the code

## How to set up
TODO

## Links
- People
	- [Andreas Spiess](https://www.youtube.com/channel/UCu7_D0o48KbfhpEohoP7YSQ)
	- [Graham Garner](https://github.com/gcgarner)
- Videos
	- [Raspberry Pi Server based on Docker](https://www.youtube.com/watch?v=a6mjt8tWUws)
- Repositories
	- [IOTstack](https://github.com/gcgarner/IOTstack)
