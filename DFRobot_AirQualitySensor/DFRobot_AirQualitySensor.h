
/*!
 * @file DFRobot_AirQualitySensor.h
 * @brief 该传感器可以获取空气中相关颗粒物的浓度
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      PengKaixing(kaixing.peng@dfrobot.com)
 * @version  V1.0
 * @date  2020-11-23
 * @url https://github.com/dfrobot/DFRobot_AirQualitySensor
 */

#ifndef __DFR0bot_AIR_H__
#define __DFR0bot_AIR_H__

#include "Arduino.h"
#include <Wire.h>

// Open this macro to see the program running in detail
//#define ENABLE_DBG

#ifdef ENABLE_DBG
#define DBG(...)                     \
    {                                \
        Serial.print("[");           \
        Serial.print(__FUNCTION__);  \
        Serial.print("(): ");        \
        Serial.print(__LINE__);      \
        Serial.print(" ] 0x");         \
        Serial.println(__VA_ARGS__,HEX); \
    }
#else
#define DBG(...)
#endif

#define PARTICLE_PM1_0_STANDARD   0X05
#define PARTICLE_PM2_5_STANDARD   0X07
#define PARTICLE_PM10_STANDARD    0X09
#define PARTICLE_PM1_0_ATMOSPHERE 0X0B
#define PARTICLE_PM2_5_ATMOSPHERE 0X0D
#define PARTICLE_PM10_ATMOSPHERE  0X0F

#define PARTICLENUM_0_3_UM_EVERY0_1L_AIR 0X11
#define PARTICLENUM_0_5_UM_EVERY0_1L_AIR 0X13
#define PARTICLENUM_1_0_UM_EVERY0_1L_AIR 0X15
#define PARTICLENUM_2_5_UM_EVERY0_1L_AIR 0X17
#define PARTICLENUM_5_0_UM_EVERY0_1L_AIR 0X19
#define PARTICLENUM_10_UM_EVERY0_1L_AIR  0X1B

#define PARTICLENUM_GAIN_VERSION 0X1D

class DFRobot_AirQualitySensor
{
  public:
    DFRobot_AirQualitySensor(TwoWire *pWire = &Wire, uint8_t addr = 0x19);
    ~DFRobot_AirQualitySensor(void){};
    /**
     * @fn begin
     * @brief 初始化
     * @return bool类型，表示初始化是否成功
     * @retval True 成功
     * @retval False 失败
     */
    bool begin(void);

    /**
     * @fn gainParticleConcentration_ugm3
     * @brief 获取指定颗粒物类型的浓度
     * @param type:设置需要输出的颗粒物的类型
     * @n          PARTICLE_PM1_0_STANDARD
     * @n          PARTICLE_PM2_5_STANDARD
     * @n          PARTICLE_PM10_STANDARD
     * @n          PARTICLE_PM1_0_ATMOSPHERE
     * @n          PARTICLE_PM2_5_ATMOSPHERE
     * @n          PARTICLE_PM10_ATMOSPHERE
     * @return uint16_t类型，表示返回指定颗粒物类型的浓度
     */
    uint16_t gainParticleConcentration_ugm3(uint8_t type);

    /**
     * @fn gainParticleNum_Every0_1L
     * @brief 获取在0.1升空气中的颗粒物的个数
     * @param type:设置需要输出的颗粒物的类型
     * @n          PARTICLENUM_0_3_UM_EVERY0_1L_AIR
     * @n          PARTICLENUM_0_5_UM_EVERY0_1L_AIR
     * @n          PARTICLENUM_1_0_UM_EVERY0_1L_AIR
     * @n          PARTICLENUM_2_5_UM_EVERY0_1L_AIR
     * @n          PARTICLENUM_5_0_UM_EVERY0_1L_AIR
     * @n          PARTICLENUM_10_UM_EVERY0_1L_AIR
     * @return uint16_t类型，每0.1升气体中的颗粒物的个数
     */
    uint16_t gainParticleNum_Every0_1L(uint8_t type);

    /**
     * @fn gainVersion
     * @brief 获取固件版本
     * @return uint8_t类型，固件版本
     */
    uint8_t gainVersion(void);

    /**
     * @fn setLowpower
     * @brief 控制传感器进入低功耗模式
     */
    void setLowpower(void);

    /**
     * @fn awake
     * @brief 控制传感器唤醒
     */
    void awake(void);

  protected:
    /**
     * @fn writeReg
     * @brief 向传感器的指定寄存器写入数据
     * @param 需要写入的寄存器地址
     * @n     Reg ：寄存器地址
     * @param 等待写入寄存器的数据
     * @n     Data：寄存器的数据指针
     * @param 等待写入的数据的长度
     * @n     len ：数据的长度
     */
    void writeReg(uint8_t Reg, void *Data, uint8_t len);

    /**
     * @fn readReg
     * @brief 从传感器的指定寄存器读取数据
     * @param 需要读取的寄存器地址
     * @n     Reg ：寄存器地址
     * @param 等待读取寄存器的数据
     * @n     Data：寄存器的数据指针
     * @param 等待读取的数据的长度
     * @n     len ：数据的长度
     */
    int16_t readReg(uint8_t Reg, uint8_t *Data, uint8_t len);

  private:
    TwoWire *_pWire;
    uint8_t _I2C_addr;
};
#endif
