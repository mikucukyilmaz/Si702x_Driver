#ifndef __Si702x_Driver_H
#define __Si702x_Driver_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

#define SI702x_I2C_ADDR     (0x40 << 1)
#define SI702x_RH_TEMP_DIV  65536.0
#define SI702x_RH_MULT      125.0
#define SI702x_RH_OFFSET    6.0
#define SI702x_TEMP_MULT    175.72
#define SI702x_TEMP_OFFSET  46.85
                                  
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

typedef enum {
  esample1  = 0x00,
  si7013    = 0x00,
  si7020    = 0x00,
  si7021    = 0x00,
  esample2  = 0xFF
} si702x_dev_type_t;

typedef enum {
  firmware1_0  = 0xFF,
  firmware2_0  = 0x20
} si702x_fwrev_t;

typedef struct {
  _Bool             isInit;
  si702x_dev_type_t dev_type;
  si702x_fwrev_t    fw_rev;
} si702x_dev_t;

// User Register 1 - Reset Settings = 0011_1010
typedef union si702x_user_reg1_u {
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
typedef union si702x_heater_ctrl_u {
  uint8_t header_ctrl;
  struct {
    uint8_t resolution0 :4;
    uint8_t             :3;
  } bits;
} si702x_heater_ctrl_t;



// Device Config Registers
int si702x_init(void);
void si702x_reset(void);
void si702x_set_user_reg1(void);
void si702x_get_user_reg1(void);
void si702x_set_heater_ctrl(void);
void si702x_get_heater_ctrl(void);
void si702x_read_id(void);
void si702x_read_fw_rev(void);
  
// Device Data Registers
void si702x_get_rh_no_hold(void);
void si702x_get_rh_hold(void);

void si702x_get_rh_no_hold(void);
void si702x_get_rh_hold(void);

void si702x_get_rh_temp_prev(void);

static void si702x_calculate_rh(uint16_t rh_code);
static void si702x_calculate_temp(uint16_t temp_code);
  
#ifdef __cplusplus
}
#endif

#endif /* __Si702x_Driver_H */
