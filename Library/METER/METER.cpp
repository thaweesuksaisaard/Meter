#include "METER.H"

MODBUS modbus;

void METER::init(int8_t slave, Stream &serial)
{
  _serial = &serial;
  _slave = slave;
  modbus.init(_slave, *_serial);
}

bool METER::readParameter1Phase(String &voltage, String &current, String &power)
{
  _return = false;
  memset(_buffers, 0, sizeof(_buffers));
  if(modbus.readMultipleParameter(0x0000, 14, _buffers))
  {
    _value = _buffers[3]<<24 | _buffers[4]<<16 | _buffers[5]<<8 | _buffers[7];
    _result = (*(float*)&_value);
    voltage = String(_result);
    //voltage = String(_buffers[3],HEX);
    
    _value = _buffers[15]<<24 | _buffers[16]<<16 | _buffers[17]<<8 | _buffers[18];
    _result = (*(float*)&_value);
    current = String(_result);

    _value = _buffers[27]<<24 | _buffers[28]<<16 | _buffers[29]<<8 | _buffers[30];
    _result = (*(float*)&_value);
    power = String(_result);
    _return = true;
  }

  return _return;
}

bool METER::readEnergy1Phase(String &energy)
{
  _return = false;
  memset(_buffers, 0, sizeof(_buffers));
  if(modbus.readMultipleParameter(0x0156, 2, _buffers))
  {
    _value = _buffers[3]<<24 | _buffers[4]<<16 | _buffers[5]<<8 | _buffers[6];
    _result = (*(float*)&_value);
    energy = String(_result);
    _return = true;
  } 
  return _return;
}
