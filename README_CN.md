# DFRobot_ADS1115

* [English Version](./README.md)

ADS1115 16位AD转换模块可对模拟量信号进行精确的采集与转换，通过这款AD模块，树莓派主控板就能非常方便的使用种类丰富的Gravity系列模拟量传感器，测量各类信号，感知这个世界。

![产品效果图](./resources/images/DFR0553.png) 


## 产品链接（[https://www.dfrobot.com.cn/goods-1734.html](https://www.dfrobot.com.cn/goods-1734.html)）
    SKU: DFR0553
   
## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性)
* [历史](#历史)
* [创作者](#创作者)

## 概述

提供一个Arduino库去通过IIC接口读取 ADS1115 传感器的模拟电压数据。

## 库安装

这里有2种安装方法：
1. 使用此库前，请首先下载库文件，将其粘贴到\Arduino\libraries目录中，然后打开examples文件夹并在该文件夹中运行演示。
2. 直接在Arduino软件库管理中搜索下载 DFRobot_ADS1115 库

## 方法

```C++
 /**
  * @fn DFRobot_ADS1115
  * @brief DFRobot_ADS1115构造函数
  * @param pWire TwoWire类对象指针
  */
  DFRobot_ADS1115(TwoWire *pWire);

  /**
   * @fn setAddr_ADS1115
   * @brief 设置I2C地址
   * @param i2cAddress: 7位I2C地址，范围： 1~127.
   */
  void setAddr_ADS1115(uint8_t i2cAddress);

  /**
   * @fn init
   * @brief 初始化ADS1115设备
   */
  void init(void);

  /**
   * @fn checkADS1115C
   * @brief 检测ads1115传感器是否连接
   * @return 连接状态:
   * @retval true  已连接
   * @retval false 未连接
   */
  bool checkADS1115();

  /**
   * @fn setCompQue
   * @brief  设置比较队列并失能
   * @n 执行2个功能 ：
   * @n 它可以禁用比较器功能并将 ALERT/RDY 引脚置于高电平状态。 
   * @n 它还可以控制超过阈值上限或下限的连续转换次数，然后再将 ALERT/RDY 引脚置为有效。
   * @param value  eADSCompLat_t枚举变量
   * @n eCOMPQUE_ONE
   * @n eCOMPQUE_TWO
   * @n eCOMPQUE_FOUR
   * @n eCOMPQUE_NONE
   */
  void setCompQue(eADSCompQue_t value);

  /**
   * @fn setCompLat
   * @brief  设置锁存比较器。
   * @n 这控制 ALERT/RDY 引脚是在断言后锁存还是在转换处于上限和下限阈值的余量内时清除。
   * @param value  eADSCompLat_t枚举变量
   * @n eCOMPLAT_NONLAT
   * @n eCOMPLAT_LATCH  
   */
  void setCompLat(eADSCompLat_t value);

  /**
   * @fn setCompMode
   * @brief  设置比较器极性。 这控制 ALERT/RDY 引脚的极性
   * @param value  eADSCompPol_t枚举变量
   * @n eCOMPPOL_LOW
   * @n eCOMPPOL_HIGH  
   */
  void setCompPol(eADSCompPol_t value);

  /**
   * @fn setCompMode
   * @brief 设置比较器模式。这控制比较器的操作模式。
   * @param value  eADSCompMode_t枚举变量
   * @n eCOMPMODE_TRAD
   * @n eCOMPMODE_WINDOW  
   */
  void setCompMode(eADSCompMode_t value);

  /**
   * @fn setRate
   * @brief 设置日期速率。 这控制数据速率设置。
   * @param value eADSRate_t枚举变量
   * @n eRATE_8     8 SPS
   * @n eRATE_16    16 SPS
   * @n eRATE_32    32 SPS
   * @n eRATE_64    64 SPS
   * @n eRATE_128   128 SPS (default) 
   * @n eRATE_250   250 SPS
   * @n eRATE_475   475 SPS
   * @n eRATE_860   860 SPS
   */
  void setRate(eADSRate_t value);

  /**
   * @fn setMode
   * @brief 设置设备操作模式。 这控制了 ADS1115 的当前操作模式
   * @param value  eADSMode_t 枚举变量
   * @n eMODE_CONTIN
   * @n eMODE_SINGLE  
   */
  void setMode(eADSMode_t value);

  /**
   * @fn setGain
   * @brief 设置增益和输入电压范围。这将配置可编程增益放大器
   * @param value  eADSGain_t枚举变量
   * @n eGAIN_TWOTHIRDS      ADC 范围: 0~6.144V (1 bit = 0.1875mV)
   * @n eGAIN_ONE            ADC 范围: 0~4.096V (1 bit = 0.125mV)
   * @n eGAIN_TWO            ADC 范围: 0~2.048V (1 bit = 0.0625mV)
   * @n eGAIN_FOUR           ADC 范围: 0~1.024V (1 bit = 0.03125mV)
   * @n eGAIN_EIGHT          ADC 范围: 0~0.512V (1 bit = 0.015625mV)
   * @n eGAIN_SIXTEEN        ADC 范围: 0~0.256V (1 bit = 0.0078125mV)
   */
  void setGain(eADSGain_t value);

  /**
   * @fn setMux
   * @brief 设置多路复用器
   * @param value  eADSMux_t枚举变量
   * @n eADSMUX_1      多路复用器 1
   * @n eADSMUX_2      多路复用器 2
   * @n eADSMUX_3      多路复用器 3
   * @n eADSMUX_4      多路复用器 4
   * @n eADSMUX_5      多路复用器 5
   * @n eADSMUX_6      多路复用器 6
   * @n eADSMUX_7      多路复用器 7
   * @n eADSMUX_8      多路复用器 8
   */
  void setMux(eADSMux_t value);

  /**
   * @fn setOSMode
   * @brief 将操作状态/单次转换设置为开始。这决定了设备的运行状态。
   * @param value  eADSOSMode_t枚举变量   
   * @n eOSMODE_SINGLE
   * @n eOSMODE_BUSY
   * @n eOSMODE_NOTBUSY
   */
  void setOSMode(eADSOSMode_t value);

  /**
   * @fn readVoltage
   * @brief 读取指定通道的电压
   * @param  channel   MCU的模拟通道
   * @return 电压
   */
  uint16_t readVoltage(uint8_t channel);

  /**
   * @fn comparatorVoltage
   * @brief 当 ADC 值超过指定的上限或下限阈值时，设置比较器导致 ALERT/RDY 引脚置位（从高到低） ADC 是差分输入通道。
   * @param channel  MCU的模拟通道
   * @return Voltage 
   */
  int16_t comparatorVoltage(uint8_t channel);

  /**
   * @fn setLowThreshold
   * @brief 设置阈值
   * @param threshold   低阈值
   */
  void setLowThreshold(int16_t threshold);

  /**
   * @fn getLowThreshold
   * @brief 获取低阈值
   * @return  低阈值
   */
  int16_t   getLowThreshold();

  /**
   * @fn setHighThreshold
   * @brief 设置高阈值
   * @param threshold   高阈值
   */
  void setHighThreshold(int16_t threshold);
  
  /**
   * @fn getHighThreshold
   * @brief 获取高阈值
   * @return  高阈值
   */
  int16_t   getHighThreshold();
```

## 兼容性

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
FireBeetle-ESP32  |      √       |             |            | 
FireBeetle-ESP8266  |      √       |             |            | 
Arduino uno |       √      |             |            | 

## 历史

- 2019/06/19 - 1.0.0 版本

## 创作者

Written by luoyufeng(yufeng.luo@dfrobot.com), 2018. (Welcome to our [website](https://www.dfrobot.com/))



