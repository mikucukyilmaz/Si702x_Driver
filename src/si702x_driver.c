#include "si702x_Driver.h"

si702x_dev_t si702x_dev;

__WEAK void si702x_read(uint16_t addr, uint8_t addr_len, uint8_t *data, uint8_t len)
{
  HAL_I2C_Mem_Read(si702x_dev.handle, SI702x_I2C_ADDR, addr, addr_len, data, len, 1000);
}  

__WEAK void si702x_write(uint16_t addr, uint8_t addr_len, uint8_t *data, uint8_t len)
{
  HAL_I2C_Mem_Write(si702x_dev.handle, SI702x_I2C_ADDR, addr, addr_len, data, len, 1000);
} 

// Device Config Registers
int si702x_init(void *handle)
{
  if( handle != NULL )
  {  
    si702x_dev.handle = handle;
    return 0;
  }
  return -1;
}

void si702x_reset(void)
{
  uint8_t data = SI702x_RESET;
  si702x_read(SI702x_RESET, 1, &data, 1); 
  si702x_debug("Si702x-Reset\n");
}

bool si702x_get_vdd_stat(void)
{  
  si702x_user_reg1_t tmp;
  si702x_read(SI702x_READ_USER_REG1, 1, &tmp.user_reg1 , 1); 
  si702x_debug("Si702x-VDD:%s\n", (tmp.bits.vdd_stat ? "Low" : "OK"));  
  return tmp.bits.vdd_stat;  
}

uint8_t si702x_get_resolution(void)
{
  si702x_user_reg1_t tmp;
  uint8_t ret = 0;
  si702x_read(SI702x_READ_USER_REG1, 1, &tmp.user_reg1 , 1); 
  ret = ((tmp.bits.resolution1 << 1) | tmp.bits.resolution0);
  si702x_debug("Si702x-Resolution:0x%02X\n", ret );  
  return ret;
}

void si702x_set_resolution(si702x_resolution_t val)
{
  si702x_user_reg1_t tmp;
  si702x_read(SI702x_READ_USER_REG1, 1, &tmp.user_reg1 , 1);
  tmp.bits.resolution0 = (val & 0x01);
  tmp.bits.resolution1 = (val & 0x02) >> 1 ;
  si702x_write(SI702x_WRITE_USER_REG1, 1, &tmp.user_reg1 , 1);
}

bool si702x_get_heater_stat(void)
{
  si702x_user_reg1_t tmp;
  si702x_read(SI702x_READ_USER_REG1, 1, &tmp.user_reg1 , 1); 
  si702x_debug("Si702x-Heater:%s\n", (tmp.bits.heater_en ? "On" : "Off"));  
  return tmp.bits.heater_en;   
}

void si702x_enable_heater(bool val)
{
  si702x_user_reg1_t tmp;
  si702x_read(SI702x_READ_USER_REG1, 1, &tmp.user_reg1 , 1);
  tmp.bits.heater_en = val;
  si702x_write(SI702x_WRITE_USER_REG1, 1, &tmp.user_reg1 , 1);
}

/*
  Current Level Table
  0x00 = 3mA
  0x01 = 9mA
  0x02 = 15mA
  0x03 = 21mA
  0x04 = 27mA
  0x05 = 33mA
  0x06 = 39mA
  0x07 = 45mA
  0x08 = 51mA
  0x09 = 57mA
  0x0A = 63mA
  0x0B = 70mA
  0x0C = 76mA
  0x0D = 82mA
  0x0E = 88mA
  0x0F = 94mA
*/
uint8_t si702x_get_heater_level(void)
{
  si702x_heater_ctrl_t tmp;
  si702x_read(SI702x_READ_HEATER_CTRL, 1, &tmp.header_ctrl, 1);  
  si702x_debug("Si702x-HeaterLevel:%dmA\n", tmp.bits.current*6+3);
  return tmp.bits.current;
}

void si702x_set_heater_level(uint8_t val)
{
  si702x_heater_ctrl_t tmp;
  si702x_read(SI702x_READ_HEATER_CTRL, 1, &tmp.header_ctrl, 1);  
  tmp.bits.current = (val & 0x0F);
  si702x_write(SI702x_WRITE_HEATER_CTRL, 1, &tmp.header_ctrl , 1);
}

/*
0x00 or 0xFF engineering samples
0x0D=13=Si7013
0x14=20=Si7020
0x15=21=Si7021
*/
void si702x_get_id(void)
{
  si702x_id_t tmp;
  si702x_read(SI702x_READ_ELECTRONIC_ID1, 2, tmp.sn.sna, 4);  
  si702x_read(SI702x_READ_ELECTRONIC_ID2, 2, tmp.sn.snb, 4);  
  si702x_debug("Si702x-ID:%02X%02X%02X%02X%02X%02X%02X%02X\n",tmp.sn.sna[0], tmp.sn.sna[1], tmp.sn.sna[2], tmp.sn.sna[3],
                                                              tmp.sn.snb[0], tmp.sn.snb[1], tmp.sn.snb[2], tmp.sn.snb[3]);
  si702x_debug("Si702x-Dev:0x%02X\n",tmp.sn.snb[0]);
}

uint8_t si702x_get_fw_rev(void)
{
  uint8_t tmp;
  si702x_read(SI702x_READ_FIRM_REV, 2, &tmp, 1);
  si702x_debug("Si702x-FwRev:0x%02X\n",tmp);
  return tmp;
}
  
float si702x_get_rh_hold_master(void)
{
  uint8_t rh_tmp[2];
  si702x_read(SI702x_MEAS_RH_HOLD_MASTER, 1, rh_tmp, 2);  
  si702x_debug("Si702x-RH:%.4f\n", si702x_calculate_rh((rh_tmp[0] << 8) |  rh_tmp[1]));
  return si702x_calculate_rh((rh_tmp[0] << 8) |  rh_tmp[1]); 
}

float si702x_get_temp_prev_meas(void)
{ 
  uint8_t temp_tmp[2];
  si702x_read(SI702x_READ_TEMP_FROM_PREV_RH, 1, temp_tmp, 2); 
  si702x_debug("Si702x-TEMP:%.4f\n", si702x_calculate_temp((temp_tmp[0] << 8) |  temp_tmp[1]));  
  return si702x_calculate_temp((temp_tmp[0] << 8) |  temp_tmp[1]);
}
  
static float si702x_calculate_rh(uint16_t rh_code)
{
  float tmp = (float)(( SI702x_RH_MULT * rh_code) / SI702x_RH_TEMP_DIV) - SI702x_RH_OFFSET; 
  
  if( tmp < 0 )
    return 0;
  else if( tmp > 100)
    return 100;
  
  return tmp;
}

static float si702x_calculate_temp(uint16_t temp_code)
{
  return (float)(( SI702x_TEMP_MULT * temp_code) / SI702x_RH_TEMP_DIV) - SI702x_TEMP_OFFSET;
}
