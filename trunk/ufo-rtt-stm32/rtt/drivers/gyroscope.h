#define L3G4200D    0

#ifndef SENSOR_GYROSCOPE
  #define SENSOR_GYROSCOPE    L3G4200D
#else
  #warning "No gyroscope defined"  
#endif

extern void gyro_init();