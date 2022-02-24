/*!
 * @file DFRobot_ADS1115.h
 * @brief Provides an Arduino library to read ADS1115 data over I2C. Use this library to read analog voltage values.
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [luoyufeng](yufeng.luo@dfrobot.com)
 * @version  V1.0
 * @date  2019-06-19
 * @url https://github.com/DFRobot/DFRobot_ADS1115
 */
#include "Arduino.h"

#include <Wire.h>
#define ADS1115_IIC_ADDRESS0         (0x48)
#define ADS1115_IIC_ADDRESS1         (0x49)
#define DFROBOT_ADS1115_CONVERSIONDELAY         (100)
#define DFROBOT_ADS1115_POINTER_MASK        (0x03)
#define DFROBOT_ADS1115_POINTER_CONVERT     (0x00)
#define DFROBOT_ADS1115_POINTER_CONFIG      (0x01)
#define DFROBOT_ADS1115_POINTER_LOWTHRESH   (0x02)
#define DFROBOT_ADS1115_POINTER_HITHRESH    (0x03)

#define DFROBOT_ADS1115_OS_MASK      (0x0001)    ///< Operational status/single-shot conversion start
#define DFROBOT_ADS1115_OS_NOEFFECT  (0x0000)    ///< Write: Bit = 0
#define DFROBOT_ADS1115_OS_SINGLE    (0x0001)    ///< Write: Bit = 1
#define DFROBOT_ADS1115_OS_BUSY      (0x0000)    ///< Read: Bit = 0
#define DFROBOT_ADS1115_OS_NOTBUSY   (0x0001)    ///< Read: Bit = 1

#define DFROBOT_ADS1115_MUX_MASK     (0x0007)    ///< Input multiplexer configuration
#define DFROBOT_ADS1115_MUX_1        (0x0000)    ///< P = AIN0, N = AIN1(default)
#define DFROBOT_ADS1115_MUX_2        (0x0001)    ///< P = AIN0, N = AIN3
#define DFROBOT_ADS1115_MUX_3        (0x0002)    ///< P = AIN1, N = AIN3
#define DFROBOT_ADS1115_MUX_4        (0x0003)    ///< P = AIN2, N = AIN3
#define DFROBOT_ADS1115_MUX_5        (0x0004)    ///< P = AIN0, N = GND
#define DFROBOT_ADS1115_MUX_6        (0x0005)    ///< P = AIN1, N = GND
#define DFROBOT_ADS1115_MUX_7        (0x0006)    ///< P = AIN2, N = GND
#define DFROBOT_ADS1115_MUX_8        (0x0007)    ///< P = AIN3, N = GND

#define DFROBOT_ADS1115_PGA_MASK     (0x0008)    ///< Programmable gain amplifier configuration
#define DFROBOT_ADS1115_PGA_0        (0x0000)    ///< 6.144V 
#define DFROBOT_ADS1115_PGA_1        (0x0001)    ///< 4.096V 
#define DFROBOT_ADS1115_PGA_2        (0x0002)    ///< 2.048V (default)
#define DFROBOT_ADS1115_PGA_3        (0x0003)    ///< 1.024V 
#define DFROBOT_ADS1115_PGA_4        (0x0004)    ///< 0.512V 
#define DFROBOT_ADS1115_PGA_5        (0x0005)    ///< 0.256V 

#define DFROBOT_ADS1115_MODE_MASK    (0x0001)    ///< Device operating mode
#define DFROBOT_ADS1115_MODE_CONTIN  (0x0000)    ///< Continuous conversion mode
#define DFROBOT_ADS1115_MODE_SINGLE  (0x0001)    ///< Power-down single-shot mode (default)

#define DFROBOT_ADS1115_DR_MASK      (0x0000)    ///< Data rate(samples per second)
#define DFROBOT_ADS1115_DR_1         (0x0000)    ///< 8 SPS
#define DFROBOT_ADS1115_DR_2         (0x0001)    ///< 16 SPS
#define DFROBOT_ADS1115_DR_3         (0x0002)    ///< 32 SPS
#define DFROBOT_ADS1115_DR_4         (0x0003)    ///< 64 SPS
#define DFROBOT_ADS1115_DR_5         (0x0004)    ///< 128 SPS (default)
#define DFROBOT_ADS1115_DR_6         (0x0005)    ///< 250 SPS
#define DFROBOT_ADS1115_DR_7         (0x0006)    ///< 475 SPS
#define DFROBOT_ADS1115_DR_8         (0x0007)    ///< 860 SPS

#define DFROBOT_ADS1115_COMP_MODE_MASK   (0x0001)    ///< Comparator mode
#define DFROBOT_ADS1115_COMP_MODE_TRAD   (0x0000)    ///< Traditional comparator with hysteresis (default)
#define DFROBOT_ADS1115_COMP_MODE_WINDOW (0x0001)    ///< Window comparator

#define DFROBOT_ADS1115_COMP_POL_MASK    (0x0001)    ///< Comparator polarity
#define DFROBOT_ADS1115_COMP_POL_ACTVLOW (0x0000)    ///< Active low(default)
#define DFROBOT_ADS1115_COMP_POL_ACTVHIGH  (0x0001)  ///< Active high

#define DFROBOT_ADS1115_COMP_LAT_MASK    (0x0001)    ///< Latching comparator
#define DFROBOT_ADS1115_COMP_LAT_NONLAT  (0x0000)    ///< Non-latching comparator (default)
#define DFROBOT_ADS1115_COMP_LAT_LATCH   (0x0001)    ///< Latching comparator

#define DFROBOT_ADS1115_COMP_QUE_MASK    (0x0003)    ///< Comparator queue and disable
#define DFROBOT_ADS1115_COMP_QUE_1CONV   (0x0000)    ///< After one conversions
#define DFROBOT_ADS1115_COMP_QUE_2CONV   (0x0001)    ///< After two conversions
#define DFROBOT_ADS1115_COMP_QUE_4CONV   (0x0002)    ///< After four conversions
#define DFROBOT_ADS1115_COMP_QUE_NONE    (0x0003)    ///< Disable the comparator(default)

typedef enum {
    eAds219_ok,
    eAds219_InitError,
    eAds219_WriteRegError,
    eAds219_ReadRegError,
}eAds219_Status;

typedef enum
{
    eOSMODE_SINGLE       = DFROBOT_ADS1115_OS_SINGLE,
    eOSMODE_BUSY         = DFROBOT_ADS1115_OS_BUSY,
    eOSMODE_NOTBUSY      = DFROBOT_ADS1115_OS_NOTBUSY
    
} eADSOSMode_t;

typedef enum
{
    eGAIN_TWOTHIRDS      = DFROBOT_ADS1115_PGA_0, /**< ADC Range: 0~6.144V (1 bit = 0.1875mV)*/
    eGAIN_ONE            = DFROBOT_ADS1115_PGA_1, /**< ADC Range: 0~4.096V (1 bit = 0.125mV)*/
    eGAIN_TWO            = DFROBOT_ADS1115_PGA_2, /**< ADC Range: 0~2.048V (1 bit = 0.0625mV)*/
    eGAIN_FOUR           = DFROBOT_ADS1115_PGA_3, /**< ADC Range: 0~1.024V (1 bit = 0.03125mV)*/
    eGAIN_EIGHT          = DFROBOT_ADS1115_PGA_4, /**< ADC Range: 0~0.512V (1 bit = 0.015625mV)*/
    eGAIN_SIXTEEN        = DFROBOT_ADS1115_PGA_5  /**< ADC Range: 0~0.256V (1 bit = 0.0078125mV)*/
} eADSGain_t;

typedef enum
{
    eMODE_CONTIN          = DFROBOT_ADS1115_MODE_CONTIN,
    eMODE_SINGLE          = DFROBOT_ADS1115_MODE_SINGLE
} eADSMode_t;

typedef enum
{
    eRATE_8              = DFROBOT_ADS1115_DR_1, /**< 8 SPS */
    eRATE_16             = DFROBOT_ADS1115_DR_2, /**< 16 SPS */
    eRATE_32             = DFROBOT_ADS1115_DR_3, /**< 32 SPS */
    eRATE_64             = DFROBOT_ADS1115_DR_4, /**< 64 SPS */
    eRATE_128            = DFROBOT_ADS1115_DR_5, /**< 128 SPS (default) */
    eRATE_250            = DFROBOT_ADS1115_DR_6, /**< 250 SPS */
    eRATE_475            = DFROBOT_ADS1115_DR_7, /**< 475 SPS */
    eRATE_860            = DFROBOT_ADS1115_DR_8  /**< 860 SPS */
} eADSRate_t;

typedef enum
{
    eCOMPMODE_TRAD       = DFROBOT_ADS1115_COMP_MODE_TRAD,
    eCOMPMODE_WINDOW     = DFROBOT_ADS1115_COMP_MODE_WINDOW
} eADSCompMode_t;

typedef enum
{
    eCOMPPOL_LOW         = DFROBOT_ADS1115_COMP_POL_ACTVLOW,
    eCOMPPOL_HIGH        = DFROBOT_ADS1115_COMP_POL_ACTVHIGH
} eADSCompPol_t;

typedef enum
{
    eCOMPLAT_NONLAT      = DFROBOT_ADS1115_COMP_LAT_NONLAT,
    eCOMPLAT_LATCH       = DFROBOT_ADS1115_COMP_LAT_LATCH
} eADSCompLat_t;

typedef enum
{
    eCOMPQUE_ONE         = DFROBOT_ADS1115_COMP_QUE_1CONV,
    eCOMPQUE_TWO         = DFROBOT_ADS1115_COMP_QUE_2CONV,
    eCOMPQUE_FOUR        = DFROBOT_ADS1115_COMP_QUE_4CONV,
    eCOMPQUE_NONE        = DFROBOT_ADS1115_COMP_QUE_NONE
} eADSCompQue_t;

typedef enum
{
    eADSMUX_1             = DFROBOT_ADS1115_MUX_1,
    eADSMUX_2             = DFROBOT_ADS1115_MUX_2,
    eADSMUX_3             = DFROBOT_ADS1115_MUX_3,
    eADSMUX_4             = DFROBOT_ADS1115_MUX_4,
    eADSMUX_5             = DFROBOT_ADS1115_MUX_5,
    eADSMUX_6             = DFROBOT_ADS1115_MUX_6,
    eADSMUX_7             = DFROBOT_ADS1115_MUX_7,
    eADSMUX_8             = DFROBOT_ADS1115_MUX_8
} eADSMux_t;

typedef enum
{
    eADSOS_NOEFFECT       = DFROBOT_ADS1115_OS_NOEFFECT,
    eADSOS_SINGLE         = DFROBOT_ADS1115_OS_SINGLE,
    eADSOS_BUSY           = DFROBOT_ADS1115_OS_BUSY,
    eADSOS_NOTBUSY        = DFROBOT_ADS1115_OS_NOTBUSY
} eADSOs_t;

class DFRobot_ADS1115
{
protected:
  uint8_t ads_conversionDelay;
  int16_t ads_lowthreshold;
  int16_t ads_highthreshold;
  eADSOSMode_t ads_osmode;
  eADSGain_t ads_gain;
  eADSMode_t ads_mode;
  eADSRate_t ads_rate;
  eADSCompMode_t ads_compmode;
  eADSCompPol_t ads_comppol;
  eADSCompLat_t ads_complat;
  eADSCompQue_t ads_compque;
  void writeReg(uint8_t i2cAddress, uint8_t reg, uint8_t *pBuf, uint16_t len);
  void readReg(uint8_t i2cAddress, uint8_t reg, uint8_t *pBuf, uint16_t len);
  int16_t readAdsReg(uint8_t i2cAddress, uint8_t reg);
  void writeAdsReg(uint8_t i2cAddress, uint8_t reg, uint16_t value);
  TwoWire   *_pWire;

public:
 /**
  * @fn DFRobot_ADS1115
  * @brief Sets the IIC address
  * @param pWire The pointer of TwoWire class object.
  */
  DFRobot_ADS1115(TwoWire *pWire){_pWire = pWire;};
  uint8_t ads_i2cAddress;
  /**
   * @fn setAddr_ADS1115
   * @brief Sets the IIC address
   * @param i2cAddress: 7 bits I2C address, the range is 1~127.
   */
  void setAddr_ADS1115(uint8_t i2cAddress);
  /**
   * @fn init
   * @brief init ADS1115 device
   */
  void init(void);
  /**
   * @fn checkADS1115
   * @brief Checks the connection status of ads1115
   * @return result:
   * @retval true or false
   */
  bool checkADS1115();
  /**
   * @fn setCompQue
   * @brief  Sets the Comparator queue and disable .
   * @n This perform two functions. 
   * @n It can disable the comparator function and put the ALERT/RDY pin into a high state. 
   * @n It also can control the number of successive conversions exceeding the upper
   * @n or lower thresholds required before asserting the ALERT/RDY pin.
   * @param value  The enum variable struct of  eADSCompLat_t
   * @n eCOMPQUE_ONE
   * @n eCOMPQUE_TWO
   * @n eCOMPQUE_FOUR
   * @n eCOMPQUE_NONE
   */
  void setCompQue(eADSCompQue_t value);
  /**
   * @fn setCompLat
   * @brief  Sets the Latching comparator .
   * @n This controls whether the ALERT/RDY pin latches once asserted 
   * @n or clears when conversions are within the margin of the upper 
   * @n and lower threshold values.
   * @param value  The enum variable struct of  eADSCompLat_t
   * @n eCOMPLAT_NONLAT
   * @n eCOMPLAT_LATCH  
   */
  void setCompLat(eADSCompLat_t value);
  /**
   * @fn setCompMode
   * @brief  Sets the Comparator polarity. This controls the polarity of the ALERT/RDY pin
   * @param value  The enum variable struct of  eADSCompPol_t
   * @n eCOMPPOL_LOW
   * @n eCOMPPOL_HIGH  
   */
  void setCompPol(eADSCompPol_t value);
  /**
   * @fn setCompMode
   * @brief Sets the Comparator mode.This controls the comparator mode of operation.
   * @param value  The enum variable struct of  eADSCompMode_t
   * @n eCOMPMODE_TRAD
   * @n eCOMPMODE_WINDOW  
   */
  void setCompMode(eADSCompMode_t value);
  /**
   * @fn setRate
   * @brief Sets the Date Rate. This controls the data rate setting.
   * @param value The enum variable struct of  eADSRate_t
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
   * @brief Sets the Device operating mode. This controls the current operational mode of the ADS1115
   * @param value  The enum variable struct of  eADSMode_t 
   * @n eMODE_CONTIN
   * @n eMODE_SINGLE  
   */
  void setMode(eADSMode_t value);
  /**
   * @fn setGain
   * @brief Sets the gain and input voltage range.This configures the programmable gain amplifier
   * @param value  The enum variable struct of  eADSGain_t
   * @n eGAIN_TWOTHIRDS      ADC Range: 0~6.144V (1 bit = 0.1875mV)
   * @n eGAIN_ONE            ADC Range: 0~4.096V (1 bit = 0.125mV)
   * @n eGAIN_TWO            ADC Range: 0~2.048V (1 bit = 0.0625mV)
   * @n eGAIN_FOUR           ADC Range: 0~1.024V (1 bit = 0.03125mV)
   * @n eGAIN_EIGHT          ADC Range: 0~0.512V (1 bit = 0.015625mV)
   * @n eGAIN_SIXTEEN        ADC Range: 0~0.256V (1 bit = 0.0078125mV)
   */
  void setGain(eADSGain_t value);
  /**
   * @fn setMux
   * @brief Sets multiplexer
   * @param value  The enum variable struct of  eADSMux_t
   * @n eADSMUX_1      multiplexer 1
   * @n eADSMUX_2      multiplexer 2
   * @n eADSMUX_3      multiplexer 3
   * @n eADSMUX_4      multiplexer 4
   * @n eADSMUX_5      multiplexer 5
   * @n eADSMUX_6      multiplexer 6
   * @n eADSMUX_7      multiplexer 7
   * @n eADSMUX_8      multiplexer 8
   */
  void setMux(eADSMux_t value);
  /**
   * @fn setOSMode
   * @brief Sets the Operational status/single-shot conversion to start.
   * @n This determines the operational status of the device.
   * @param value  The enum variable struct of  eADSOSMode_t   
   * @n eOSMODE_SINGLE
   * @n eOSMODE_BUSY
   * @n eOSMODE_NOTBUSY
   */
  void setOSMode(eADSOSMode_t value);
  /**
   * @fn readVoltage
   * @brief Reads the voltage of the specified channel
   * @param  channel   The analog channnel of MCU
   * @return Voltage
   */
  uint16_t readVoltage(uint8_t channel);
  /**
   * @fn comparatorVoltage
   * @brief Sets up the comparator causing the ALERT/RDY pin to assert 
   * @n   (go from high to low) when the ADC value exceeds the specified upper or lower threshold
   * @n   ADC is Differential input channel
   * @param channel  The analog channnel of MCU
   * @return Voltage 
   */
  int16_t comparatorVoltage(uint8_t channel);
  /**
   * @fn setLowThreshold
   * @brief Sets the low threshold value
   * @param threshold   The low threshold value
   */
  void setLowThreshold(int16_t threshold);
  /**
   * @fn getLowThreshold
   * @brief Get the low threshold value
   * @return  The low threshold value
   */
  int16_t   getLowThreshold();
  /**
   * @fn setHighThreshold
   * @brief Sets the high threshold value
   * @param threshold   The high threshold value
   */
  void setHighThreshold(int16_t threshold);
  /**
   * @fn getHighThreshold
   * @brief Get the high threshold value
   * @return  The high threshold value
   */
  int16_t   getHighThreshold();
};

