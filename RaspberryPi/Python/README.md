# ADS1115
The ADS1115 is a high precision analog-to-digital converter (ADC) with 16-bit resolution. And with A0-A3, 4 ADC ports


## DFRobot_ADS1115.py Library for Raspberry pi
---------------------------------------------------------
Provides an Raspberry pi library to read ADS1115 data over I2C. Use this library to read analog voltage values.
## Table of Contents

* [Installation](#installation)
* [Methods](#methods)
<snippet>
<content>

## Installation

Download and install smbus library on Raspberry pi. Steps to install smbus are provided at:

https://pypi.python.org/pypi/smbus-cffi/0.5.1 Download (or git pull) the code in pi.
The Raspberry pi i2c1 and the board's i2c interface connected.
Run the program:

```cpp

$> python DFRobot_ADS1115.py

```

Run the demo:

```cpp

$> python ADS1115_ReadVoltage.py

```
## Methods

```C++

/*
 * @brief Set the IIC address
 */
def setAddr_ADS1115(self,addr);

/*
 * @brief Sets the gain and input voltage range.
 *        This configures the programmable gain amplifier
 *        ADS1115_REG_CONFIG_PGA_6_144V     = 0x00 # 6.144V range = Gain 2/3
 *        ADS1115_REG_CONFIG_PGA_4_096V     = 0x02 # 4.096V range = Gain 1
 *        ADS1115_REG_CONFIG_PGA_2_048V     = 0x04 # 2.048V range = Gain 2 (default)
 *        ADS1115_REG_CONFIG_PGA_1_024V     = 0x06 # 1.024V range = Gain 4
 *        ADS1115_REG_CONFIG_PGA_0_512V     = 0x08 # 0.512V range = Gain 8
 *        ADS1115_REG_CONFIG_PGA_0_256V     = 0x0A # 0.256V range = Gain 16
 */
def setGain(self,gain);

/*
 * @brief Get the channel you need to enter
 *        For SingleOutput:
 *            0 : AINP = AIN0 and AINN = GND
 *            1 : AINP = AIN1 and AINN = GND
 *            2 : AINP = AIN2 and AINN = GND
 *            3 : AINP = AIN3 and AINN = GND
 *        For Differential Output:
 *            0 : AINP = AIN0 and AINN = AIN1
 *            1 : AINP = AIN0 and AINN = AIN3
 *            2 : AINP = AIN1 and AINN = AIN3
 *            3 : AINP = AIN2 and AINN = AIN3
 */
def setChannel(self);

/*
 * @brief Configuration using a single read
 */
def setSingle(self);

/*
 * @brief Configure as comparator output
 */
def setDifferential(self);

/*
 * @brief Read ADC value
 */
def readValue(self);

```
## Credits

Written by DFRobot_xiaowu, 2018. (Welcome to our [website](https://www.dfrobot.com/))
