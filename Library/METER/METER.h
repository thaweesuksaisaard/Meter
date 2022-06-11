#ifndef METER_H
#define METER_H
#include <MODBUS.h>
class METER{
  public:
    void init(int8_t slave, Stream &serial);
    bool readParameter1Phase(String &voltage, String &current, String &power);
    bool readEnergy1Phase(String &energy);
  private:
    bool _return;
    uint8_t _buffers[100];
    uint32_t _value;
    uint8_t _slave;
    Stream* _serial;
    float _result; 
};
#endif
