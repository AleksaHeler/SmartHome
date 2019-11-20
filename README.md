# SmartHome
This is an experimet for making an infrastructure for logging and displaying data on home server.

## Contents
 - [Server](#server)
 - [Devices](#devices)
 - [How to set up](#how-to-set-up)
   - [Server](#how-to-set-up)
   - [NodeMCU](#nodemcu)
 - [How to boot RasPi from USB](#how-to-boot-raspi-from-usb-instead-of-an-sd-card)
 - [Links](#links)


## Server
For the server I used a Raspberry Pi 3 B+, which is easy to set up and let it work 24/7. Following instructions from [this](https://www.youtube.com/watch?v=a6mjt8tWUws) YouTube video by Andreas Spiess, where he uses [IOTstack](https://github.com/gcgarner/IOTstack) by Graham Garner, it was pretty easy to set up the Raspberry Pi with docker and install containters:
- Mosquitto as MQTT broker
- NodeRed for parsing data
- InfluxDB as timeseries database
- Grafana for displaying all data nicely.

TODO: better explain every program
TODO: explain domain


## Devices
As I currently have only one NodeMCU, I used it to connect with an array of sensors and to publish readings frequently to the local server. Code can be found in [NodeMCU/src](NodeMCU/src)


## How to set up
### Server
Lets start with a fresh install of [Raspbian](https://www.raspberrypi.org/downloads/raspbian/) Raspbian Buster with desktop (without recommended software). To burn it to the SD I used [Etcher](https://www.balena.io/etcher/). After the first boot and setup we do:
```
apt-get update
apt-get upgrade
```
Then we can download the [IOTstack](https://github.com/gcgarner/IOTstack#download-the-project) by follow these couple of lines in the link, and after chainging into the directory 'IOTstack' we start the menu.sh script
```
./menu.sh
``` 
and select the option to install Docker. After it is done, we start the menu one more time and this time select the option to build stack. Here we select Portainer, NodeRed, InfluxDB, Grafana and Eclipse-Mosquitto. Then the docker compose file is created which will tell Docker what to install. To install it we use the command
```
docker-compose up -d
```
TODO: optional ./menu.sh -> miscellaneous commands -> disable swap and install log2ram
After it is done, we should be able to connect to Raspberry Pi using browser to see if the containers started. To find the IP address use the command:
```
hostname -I
```
In my case it is 192.168.1.7. Then in the browser type 192.168.1.7:1880 to connect to NodeRed, or port 3000 for Grafana or 9000 for Portainer. Since InfluxDB has no web interface, we have to connect to the terminal inside the container:
```
docker exec -it influxdb /bin/dash
```
After that we can type influxdb to start the program.

By this point everything should be installed and working, so the next step would be to set up and connect everything.
TODO: explain how


### NodeMCU
Code can be found in [NodeMCU/src](NodeMCU/src). Brief explanation:
- First connect to wifi
- Connects to all sensors
- If required time has passed:
	- read all sensors
	- format string with all data
	- publish the string to topic 'devices'
	
## How to boot RasPi from USB instead of an SD card
So I had a problem with sd card, it just got fried. It was pretty old and slow anyway, and I didn't have any other at that time, and I also didn't want to go buy a new one. So I researched a bit and found a way to boot the Raspberry Pi to USB without having an SD card.

It seems to only work on Pi3B+, but I don't have other boards to try it out. It's not exatly true that you don't need an SD card, it is needed to boot up the Pi just once for one-time configuration. I used an SD card from my phone, I just made a backup of it and formated it, installed raspbian, did what was needed, then formated it again and got everything back as it was.


## Links
- People
	- [Andreas Spiess](https://www.youtube.com/channel/UCu7_D0o48KbfhpEohoP7YSQ)
	- [Graham Garner](https://github.com/gcgarner)
- Videos
	- [Raspberry Pi Server based on Docker](https://www.youtube.com/watch?v=a6mjt8tWUws)
- Repositories
	- [IOTstack](https://github.com/gcgarner/IOTstack)
