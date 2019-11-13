#include <OneWire.h>
OneWire ds(2);    //D4

float get_temp(){
  int HighByte, LowByte, TReading, SignBit, Tc_100;
  byte i, data[12];
  byte addr[8];

  if ( !ds.search(addr))
      return -999;

  if ( OneWire::crc8( addr, 7) != addr[7])
      return -999;

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);
  delay(1000);
  ds.reset();
  ds.select(addr);
  ds.write(0xBE);

  for ( i = 0; i < 9; i++)
    data[i] = ds.read();

  LowByte = data[0];
  HighByte = data[1];
  TReading = (HighByte << 8) + LowByte;
  SignBit = TReading & 0x8000;
  if (SignBit)
    TReading = (TReading ^ 0xffff) + 1;
  Tc_100 = (6 * TReading) + TReading / 4;

  return Tc_100/100.0;
}
