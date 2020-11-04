#ifndef __Si702x_Driver_H
#define __Si702x_Driver_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

#define SI702x_I2C_ADDR (0x40 << 1)
/*
#define SI702x_MEAS_RH_HOLD_MASTER      0xE5 // Measure Relative Humidity, Hold Master Mode
#define SI702x_MEAS_RH_NO_HOLD_MASTER   0xF5 // Measure Relative Humidity, No Hold Master Mode
#define SI702x_MEAS_TEMP_HOLD_MASTER    0xE3 // Measure Temperature, Hold Master Mode
#define SI702x_MEAS_TEMP_NO_HOLD_MASTER 0xF3 // Measure Temperature, No Hold Master Mode
#define SI702x_READ_TEMP_FROM_PREV_RH   0xE0 // Read Temperature Value from Previous RH Measurement 
#define SI702x_RESET                    0xFE // Reset
#define SI702x_WRITE_USER_REG1          0xE6 // Write RH/T User Register 1
#define SI702x_READ_USER_REG1           0xE7 // Read RH/T User Register 1
#define SI702x_WRITE_HEATER_CTRL        0x51 // Write Heater Control Register
#define SI702x_READ_HEATER_CTRL         0x11 // Read Heater Control Register
#define SI702x_READ_ELECTRONIC_ID1_1    0xFA // Read Electronic ID 1st Byte Part 1
#define SI702x_READ_ELECTRONIC_ID1_2    0xF0 // Read Electronic ID 1st Byte Part 2
#define SI702x_READ_ELECTRONIC_ID2_1    0xFC // Read Electronic ID 2nd Byte Part 1
#define SI702x_READ_ELECTRONIC_ID2_2    0xC9 // Read Electronic ID 2nd Byte Part 2
#define SI702x_READ_FIRM_REV_1          0x84 // Read Firmware Revision Part 1
#define SI702x_READ_FIRM_REV_2          0xB8 // Read Firmware Revision Part 2
*/
typedef struct {
  _Bool isInit;
} si702x_dev_t;

int32_t si702x_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __Si702x_Driver_H */
