# DFRobot_ADS1115

* [中文版](./README_CN.md)

The ADS1115 is a high precision analog-to-digital converter (ADC) with 16-bit resolution. And with A0-A3, 4 ADC ports


![产品效果图](../../resources/images/DFR0553.png)

## Product Link（[https://www.dfrobot.com/product-1730.html](https://www.dfrobot.com/product-1730.html)）
    SKU: DFR0553

## Table of Contents
* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary
Provides an Raspberry pi library to read ADS1115 data over I2C. Use this library to read analog voltage values.


## Installation
1. To use this library, first download the library file<br>
```python
sudo git clone https://github.com/DFRobot/DFRobot_ADS1115
```
2. Open and run the routine. To execute a routine demo_x.py, enter python demo_x.py in the command line. For example, to execute the demo_read_voltage.py routine, you need to enter :<br>

```python
python demo_read_voltage.py 
or
python2 demo_read_voltage.py 
```


## Methods

```python
  '''!
    @brief Sets the gain and input voltage range.
    @param gain  This configures the programmable gain amplifier
    @n ADS1115_REG_CONFIG_PGA_6_144V     = 0x00 # 6.144V range = Gain 2/3
    @n ADS1115_REG_CONFIG_PGA_4_096V     = 0x02 # 4.096V range = Gain 1
    @n ADS1115_REG_CONFIG_PGA_2_048V     = 0x04 # 2.048V range = Gain 2
    @n default:
    @n ADS1115_REG_CONFIG_PGA_1_024V     = 0x06 # 1.024V range = Gain 4
    @n ADS1115_REG_CONFIG_PGA_0_512V     = 0x08 # 0.512V range = Gain 8
    @n ADS1115_REG_CONFIG_PGA_0_256V     = 0x0A # 0.256V range = Gain 16
  '''
  def set_gain(self,gain):
		
  '''!
    @brief Sets the IIC address.
    @param addr  7 bits I2C address, the range is 1~127.
  '''	
  def set_addr_ADS1115(self,addr):
		
  '''!
    @brief Select the Channel user want to use from 0-3.
    @param channel  the Channel: 0-3
    @n For Single-ended Output: 
    @n    0 : AINP = AIN0 and AINN = GND
    @n    1 : AINP = AIN1 and AINN = GND
    @n    2 : AINP = AIN2 and AINN = GND
    @n    3 : AINP = AIN3 and AINN = GND
    @n For Differential Output:
    @n    0 : AINP = AIN0 and AINN = AIN1
    @n    1 : AINP = AIN0 and AINN = AIN3
    @n    2 : AINP = AIN1 and AINN = AIN3
    @n    3 : AINP = AIN2 and AINN = AIN3
    @return channel
  '''
  def set_channel(self,channel):
	
  '''!
    @brief Configuration using a single read.
  '''
  def set_single(self):
	
  '''!
    @brief Configure as comparator output.
  '''
  def set_differential(self):

  '''!
    @brief  Read ADC value.
    @return raw  adc
  '''	
  def read_value(self):

  '''!
    @brief Reads the voltage of the specified channel.
    @param channel  the Channel: 0-3
    @n For Single-ended Output: 
    @n    0 : AINP = AIN0 and AINN = GND
    @n    1 : AINP = AIN1 and AINN = GND
    @n    2 : AINP = AIN2 and AINN = GND
    @n    3 : AINP = AIN3 and AINN = GND
    @n For Differential Output:
    @n    0 : AINP = AIN0 and AINN = AIN1
    @n    1 : AINP = AIN0 and AINN = AIN3
    @n    2 : AINP = AIN1 and AINN = AIN3
    @n    3 : AINP = AIN2 and AINN = AIN3
    @return Voltage
  '''
  def read_voltage(self,channel):
		
  '''!
    @brief Sets up the comparator causing the ALERT/RDY pin to assert .
    @param channel  the Channel: 0-3
    @n For Single-ended Output: 
    @n    0 : AINP = AIN0 and AINN = GND
    @n    1 : AINP = AIN1 and AINN = GND
    @n    2 : AINP = AIN2 and AINN = GND
    @n    3 : AINP = AIN3 and AINN = GND
    @n For Differential Output:
    @n    0 : AINP = AIN0 and AINN = AIN1
    @n    1 : AINP = AIN0 and AINN = AIN3
    @n    2 : AINP = AIN1 and AINN = AIN3
    @n    3 : AINP = AIN2 and AINN = AIN3
    @return Voltage
  '''
  def comparator_voltage(self,channel):
		
```

## Compatibility

| 主板         | 通过 | 未通过 | 未测试 | 备注 |
| ------------ | :--: | :----: | :----: | :--: |
| RaspberryPi2 |      |        |   √    |      |
| RaspberryPi3 |      |        |   √    |      |
| RaspberryPi4 |  √   |        |        |      |

* Python 版本

| Python  | 通过 | 未通过 | 未测试 | 备注 |
| ------- | :--: | :----: | :----: | ---- |
| Python2 |  √   |        |        |      |
| Python3 |     |        |    √   |      |

## History

- 2019/06/19 - Version 0.1 released.

## Credits

Written by luoyufeng(yufeng.luo@dfrobot.com), 2018. (Welcome to our [website](https://www.dfrobot.com/))
