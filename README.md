# Using Tasmota Firmware in your DIY IoT Project

If you are working on your own ESP8266/ESP32 DIY project trying to build an IoT device and integrate it into your Smart Home system, chances are that you need to solve a number of common problems:
* Network connectivity over WiFi
* MQTT support
* Web interface
* OTA firmware update
* Debug/Logging
* Integration into Home Automation system
* Support for sensor/device/protocol
* etc.

Usually such problems solved one by one using third-party libraries. Often the project grows into a huge, hardly manageable collection of components found to be incompatible with each other.

I have been doing such projects in various ways, until I found an approach quickly leading to a successful result with minimum effort, which is described in this repository.

## Alternative firmware

Selecting components for my Home Automation system I always prefer devices supported by [Tasmota](https://github.com/arendst/Tasmota). As defined by its author Tasmota is 

```
Alternative firmware for ESP8266 and ESP32 based devices  
with easy configuration using webUI, OTA updates,  
automation using timers or rules,  
expandability and entirely local control over  
MQTT, HTTP, Serial or KNX.
```

My original use of Tasmota was limited to re-flashing ESP8266/ESP32 based devices. Backed with Tasmota a device turns into a new one - with a plethora of new functions, supported sensors, powered with handy web interface, OTA, Console, easy configuration and compatibility with a number of Home Automation ecosystems. All that becomes available on a local network with plain browser, leaving apart annoying "native" mobile apps with their suspicious cloud servers.

It is not always possible to find a ready-to-use device serving my purpose. Starting a DIY project is often necessary. And here Tasmota comes handy again. Instead of adding libraries to your own code to support common functions, it is possible to add your custom code to Tasmota. That greatly simplifies DIY projects resulting in a solid solution.

In my DIY projects, I use [M5Stick-C](https://docs.m5stack.com/en/core/m5stickc) or [Wemos D1 mini](https://www.wemos.cc/en/latest/d1/d1_mini_3.1.0.html) with [PlatformIO](https://platformio.org/) as a development environment. Tasmota better suits ESP8266 based devices, but ESP32 device support is constantly improving. Adding your own hardware support to Tasmota is not covered in [documentation](https://tasmota.github.io/docs). This repository aims to offer an easy to start design template with useful instructions for making your own integration into Tasmota firmware.

Tasmota comes in several [firmware variants](https://tasmota.github.io/docs/Firmware-Builds/#firmware-variants). The option I use is `tasmota-lite`, which has all needed components included with minimal sensor/features support. If any extra sensor/feature is required, it is possible to add more modules to a [custom build](https://tasmota.github.io/docs/Compile-your-build/#customize-your-build).

## Setting up development environment

To start with, you need to install PlatformIO to your system. The installation and use of your favorite code editor or IDE is [well described](https://tasmota.github.io/docs/Compile-your-build/#compiling-tools). Then you need to clone Tasmota development or stable (preferred) branch to your local system. The process of making a custom Tasmota build is [well covered](https://tasmota.github.io/docs/Compile-your-build/#customize-your-build) too. In short, you need to create the following configuration files:

* Copy `platformio_override_sample.ini` to `platformio_override.ini` file in the project root folder
	- comment out `tasmota` and uncomment `tasmota-lite` build target in `platformio/default_envs` section
	- find and uncomment your board type name in `env` section, for Wemos D1 mini it is `esp8266_4M2M`
	- add a correct serial port name used for flashing your board as `upload_port` parameter
	- optionally use proper `upload_speed`
	- if any custom lib is used, its name needs to be mentioned in `lib_deps`
* Copy `user_config_override_sample.h` to `user_config_override.h` in `/tasmota` folder
	- Uncomment parameter section and enter your own info for:
		- WiFi/MQTT Broker **credentials**, MQTT Broker **host** and project **name**
	- Use `#define` statement to include your custom Tasmota integration

Examples of config files are included in this repository.


## Add your code to Tasmota

To add a support for your own hardware to Tasmota you need to create a driver. The code is provided in a file `tasmota/xdrv_xxxx.ino`. For custom integration the driver numbering from 100 to 128 is available. Every driver shoud have a unique number. This repository includes 2 examples: a bare minimum code template `xdrv_100_my_project_minimal.ino`
and a template with custom commands `xdrv_101_my_project_with_commands.ino`. The latter includes an example of sending a MQTT message.

Example 3 is added to adopt suggestions of the Tasmota developer as indicated in [this discussion](https://github.com/arendst/Tasmota/discussions/14205). It makes dynamic allocation of required large-size buffers and more advanced way of addind driver in Tasmota.

Another example is available in a separate repository: [Tasmota Nexus 433 MHz to MQTT Gateway for Home Assistant](https://github.com/phpcoder/tasmota-nexus-mqtt).

To compile any of your custom drivers use the corresponding `#define` statement as shown in `user_config_override.h`. To build and upload your custom Tasmota firmware use a command:

```
pio run --target upload && pio device monitor
```

Provided with your correct WiFi credentials upon successful upload, Tasmota with your bare minimum code allows you to connect to your device web interface with a browser and see your debug messages in its Console. Even without WiFi credentials your Tasmota powered device will show up as a WiFi hotspot which makes possible to configure all needed parameters.



## Links

* [Tasmota](https://github.com/arendst/Tasmota) - Alternative firmware for ESP8266 and ESP32 based devices.
* [PlatformIO](https://platformio.org/) - Professional collaborative platform for embedded development.
* [M5StickC](https://docs.m5stack.com/en/core/m5stickc) - ESP32 based mini controller.
* [Wemos D1 mini](https://www.wemos.cc/en/latest/d1/d1_mini_3.1.0.html) - A mini wifi board with 4MB flash based on ESP-8266EX.
