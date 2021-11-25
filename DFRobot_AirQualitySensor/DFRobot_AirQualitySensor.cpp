
/*!
 * @file DFRobot_AirQualitySensor.cpp
 * @brief 该传感器可以获取空气中相关颗粒物的浓度
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      PengKaixing(kaixing.peng@dfrobot.com)
 * @version  V1.0
 * @date  2020-11-23
 * @url https://github.com/dfrobot/DFRobot_AirQualitySensor
 */
#include "DFRobot_AirQualitySensor.h"

DFRobot_AirQualitySensor::DFRobot_AirQualitySensor(TwoWire *pWire, uint8_t addr)
{
  _pWire = pWire;
  this->_I2C_addr = addr;
}

bool DFRobot_AirQualitySensor::begin(void)
{
  _pWire->begin();
  _pWire->beginTransmission(_I2C_addr);
  if (_pWire->endTransmission() == 0)
    return true;
  else
    return false;
}

uint16_t DFRobot_AirQualitySensor::gainParticleConcentration_ugm3(uint8_t type)
{
  uint8_t buf[2];
  readReg(type, buf, 2);
  uint16_t concentration = ((uint16_t)buf[0] << 8) + (uint16_t)buf[1];
  return concentration;
}

uint16_t DFRobot_AirQualitySensor::gainParticleNum_Every0_1L(uint8_t type)
{
  uint8_t buf[2];
  readReg(type, buf, 2);
  uint16_t particlenum = ((uint16_t)buf[0] << 8) + (uint16_t)buf[1];
  return particlenum;
}

uint8_t DFRobot_AirQualitySensor::gainVersion(void)
{
  uint8_t version = 0 ;
  readReg(PARTICLENUM_GAIN_VERSION, &version, 1);
  return version;
}

void DFRobot_AirQualitySensor::setLowpower(void)
{
  uint8_t mode = 1;
  writeReg(0x01, &mode, 1);
}

void DFRobot_AirQualitySensor::awake(void)
{
  uint8_t mode = 2;
  writeReg(0x01, &mode, 1);
}

void DFRobot_AirQualitySensor::writeReg(uint8_t Reg, void *pData, uint8_t len)
{
  uint8_t *Data = (uint8_t *)pData;
  _pWire->beginTransmission(this->_I2C_addr);
  _pWire->write(Reg);
  for (uint8_t i = 0; i < len; i++)
  {
    _pWire->write(Data[i]);
  }
  _pWire->endTransmission();
}

int16_t DFRobot_AirQualitySensor::readReg(uint8_t Reg, uint8_t *Data, uint8_t len)
{
  int i = 0;
  _pWire->beginTransmission(this->_I2C_addr);
  _pWire->write(Reg);
  if (_pWire->endTransmission() != 0)
  {
    return -1;
  }
  _pWire->requestFrom((uint8_t)this->_I2C_addr, (uint8_t)len);
  while (_pWire->available())
  {
    Data[i++] = _pWire->read();
  }
  return len;
}
