# Raspberry-Pi-as-Bluetooth-Hub

In this project, I demonstrate a very simple IoT system that connects sensors and actuators to the cloud using a AWS for the Cloud Services, a TI LaunchPad Evaluation Module as host microcontroller for the sensors, and Raspberry Pi as Internet Gateway.

The block diagram of the demo system is shown below:

![block-diagram](https://github.com/nacansino/Raspberry-Pi-as-Bluetooth-Hub/blob/master/docs/images/block-diagram.png?raw=true)

## Goal of the Project
This demonstration isn't targeted to do anything useful but just to demonstrate how other developers can connect local devices to the Internet and to already-available cloud services like AWS.

The idea of Internet of Things is to give things life and intelligence by connecting them to the Internet.
There are plenty of reports and publications such as [this](https://www.hindawi.com/journals/jece/2017/9324035/), [this](https://www.researchgate.net/figure/The-layered-architectures-of-IoT-three-four-and-five-layers_fig6_327272757), and [this](https://www.iotsense.io/blog/the-layers-of-iot/), but I'd like to make things simple and to just model the system with three main parts.

### Parts of an IoT System (with analogy to the human body)
- Sensors and Actuators - think of this as the senses and the limbs of the system
- Gateway - think of this as the nervous system that transmit signals to and from the brain
- Hub - think of this as the brain of the system that does the processing of the signals from the senses, and responsible for making the intelligent decisions for action to be realized by the limbs

The hub can be located locally or in the cloud, but in this demo we will use a cloud service.
While it is true that [connection to cloud is not necessary](https://www.iotforall.com/what-is-the-cloud/), my opinion is that utilizing the power of the cloud enables the users and developers to focus more on specific problems in their applications instead of spending their time architecting their own data collection and analysis pipeline.

## Materials Used:
| Component                   | Part Number     | Manufacturer      |
|-----------------------------|-----------------|-------------------|
| Bluetooth Module            | HM-19           | DSD-Tech          |
| Sensor Host Microcontroller | MSP-EXP432P401R | Texas Instruments |
| IoT Gateway                 | RPI-3B          | Raspberry Pi      |

I used existing components in my inventory to illustrate how one can connect their own devices to the cloud via AWS IoT SDK.

In contrast to devices that are running on tap power supplies, devices that only run on batteries have very low power requirement. 
One of the attractive protocols for low-power application is Bluetooth Low Energy, so I think this demonstration is a realistic framework that a developer may set-up in a local setting. Other most-commonly used close-proximity protocols are [Zwave](https://www.z-wave.com/) and [Zigbee](https://zigbeealliance.org/) but those are outside the scope of the project.

## Sensors:
| Component                   | Part Number     | Manufacturer      |
|-----------------------------|-----------------|-------------------|
