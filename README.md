#OSC Bridge
This is an application that can recieve OSC (udp) messages and forward them to devices that allow control via tcp.

## Features

## Tested Device List

## TODO
+ Implement a web based interface
+ Compile for ARM
+ Build distributible SD Card version with linux kernel for Raspbery Pi (standalone device)
+ Remove dependency on QT (make optional)
+ Add support for serial devices
+ Add a way of viewing responses from devices
+ Make settings persistent

## Useage
+ Compile and run
+ Select port and hit start server
+ Add a device
+ Select device and hit connect
+ Once connected, send an OSC Message to the app on the selected port formatted in the following way:
	````/device/<device name>/message "message to be sent to device"````
+ Newlines can be sent to devices by including ````\n```` in the message
