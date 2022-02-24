'''!
  @file demo_comparator_voltage.py
  @brief connect ADS1115 I2C interface with your board (please reference board compatibility)
  @n  Through the serial port to see the voltage difference between the two channels.
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license     The MIT License (MIT)
  @author [luoyufeng](yufeng.luo@dfrobot.com)
  @version  V1.0
  @date  2019-06-19
  @url https://github.com/DFRobot/DFRobot_ADS1115
'''

import sys
sys.path.append('../')
sys.path.append(os.path.dirname(os.path.dirname(os.path.realpath(__file__))))
import time

ADS1115_REG_CONFIG_PGA_6_144V        = 0x00 # 6.144V range = Gain 2/3
ADS1115_REG_CONFIG_PGA_4_096V        = 0x02 # 4.096V range = Gain 1
ADS1115_REG_CONFIG_PGA_2_048V        = 0x04 # 2.048V range = Gain 2 (default)
ADS1115_REG_CONFIG_PGA_1_024V        = 0x06 # 1.024V range = Gain 4
ADS1115_REG_CONFIG_PGA_0_512V        = 0x08 # 0.512V range = Gain 8
ADS1115_REG_CONFIG_PGA_0_256V        = 0x0A # 0.256V range = Gain 16

from DFRobot_ADS1115 import ADS1115
ads1115 = ADS1115()

while True :
    #Set the IIC address
    ads1115.set_addr_ADS1115(0x48)
    #Sets the gain and input voltage range.
    ads1115.set_gain(ADS1115_REG_CONFIG_PGA_6_144V)
    time.sleep(0.8)
    #Get the voltage difference between two channels
    adc = ads1115.comparator_voltage(0)
    print "The voltage difference between A0 and A1 :%d "%(adc['r'])
    time.sleep(0.8)
    adc = ads1115.comparator_voltage(1)
    print "The voltage difference between A0 and A3 :%d "%(adc['r'])
    time.sleep(0.8)
    adc = ads1115.comparator_voltage(2)
    print "The voltage difference between A1 and A3 :%d "%(adc['r'])
    time.sleep(0.8)
    adc = ads1115.comparator_voltage(3)
    print "The voltage difference between A2 and A3 :%d "%(adc['r'])

