#ifndef __Si702x_Driver_H
#define __Si702x_Driver_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "stdbool.h"

#define SI702x_DEBUG

#if defined(SI702x_DEBUG)
#define si702x_debug(...) printf(__VA_ARGS__)
#else
#define si702x_debug(...)
#endif

#define SI702x_I2C_ADDR     (0x40 << 1)
#define SI702x_RH_TEMP_DIV  65536.0f
#define SI702x_RH_MULT      125.0f
#define SI702x_RH_OFFSET    6.0f
#define SI702x_TEMP_MULT    175.72f
#define SI702x_TEMP_OFFSET  46.85f
                                  
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
#define SI702x_READ_ELECTRONIC_ID1      0xFA0F // Read Electronic ID 1st Byte Part 1
#define SI702x_READ_ELECTRONIC_ID2      0xFCC9 // Read Electronic ID 2nd Byte Part 1
#define SI702x_READ_FIRM_REV            0x84B8 // Read Firmware Revision Part 1

typedef enum {
  RH12_TEMP14  =  0x00,
  RH08_TEMP12  =  0x01,
  RH10_TEMP13  =  0x02,
  RH11_TEMP11  =  0x03,
} si702x_resolution_t;

typedef struct {
  bool  isInit;
  void  *handle;
} si702x_dev_t;

typedef union {
  uint16_t data16;
  uint8_t data8[2];
} si702x_data_t;

// User Register 1 - Reset Settings = 0011_1010
typedef union {
  uint64_t id;
  struct {
    uint8_t sna[4];
    uint8_t snb[4];
  } sn;
} si702x_id_t;

// User Register 1 - Reset Settings = 0011_1010
typedef union {
  uint8_t user_reg1;
  struct {
    uint8_t resolution0 :1;
    uint8_t             :1;
    uint8_t heater_en   :1;
    uint8_t             :3;
    uint8_t vdd_stat    :1;
    uint8_t resolution1 :1;
  } bits;
} si702x_user_reg1_t;

// Heater Control - Register Reset Settings = 0000_0000
typedef union {
  uint8_t header_ctrl;
  struct {
    uint8_t current :4;
    uint8_t         :3;
  } bits;
} si702x_heater_ctrl_t;

int si702x_init(void *handle);
void si702x_reset(void);
bool si702x_get_vdd_stat(void);  
uint8_t si702x_get_resolution(void);
void si702x_set_resolution(si702x_resolution_t val);
bool si702x_get_heater_stat(void);
void si702x_enable_heater(bool en);
uint8_t si702x_get_heater_level(void);
void si702x_set_heater_level(uint8_t val);
void si702x_get_id(void);
uint8_t si702x_get_fw_rev(void);
float si702x_get_rh_hold_master(void);
float si702x_get_temp_prev_meas(void);

static float si702x_calculate_rh(uint16_t rh_code);
static float si702x_calculate_temp(uint16_t temp_code);
  
#ifdef __cplusplus
}
#endif

#endif /* __Si702x_Driver_H */
