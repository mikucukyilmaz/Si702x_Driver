# Si702x_Driver
Silicon Labs Si7020/21 I2C Relative Humidity and Temperature Sensor Driver.
1. Override the weak read and write functions according to platform.
    *   ```void si702x_read(uint16_t addr, uint8_t addr_len, uint8_t *data, uint8_t len)```
    *   ```void si702x_write(uint16_t addr, uint8_t addr_len, uint8_t *data, uint8_t len)```
1. Init the driver with handler.
    * ```  si702x_init(&hi2c1);```
1. Change the resolution if needed. (Low resolution-> Lower Conversion Time -> Lower Current Consumption.) Default: 12-bit RH , 14-bit temperature
    * ```si702x_set_resolution(RH10_TEMP13);```
1.  Read data with get temperature and humidity methods.Initiating a RH measurement will also automatically initiate a temperature measurement.
    * ```float rh = si702x_get_rh_hold_master();```
    * ```float temp = si702x_get_temp_prev_meas();```
1. Internal heater can be used to test sensor or deal with condensation and high humidity.
    * ```//For example 0x00 = 3mA, 0x08 = 51mA, 0x0F = 94mA (maximum) ```   
    * ```si702x_set_heater_level(0x0F) // HeaterCurrent(mA) = HeaterLevel*3 + 6 ```
    * ```si702x_enable_heater(true); ```
1. Debug messages can be disabled by commenting ```#define SI702x_DEBUG``` line.


