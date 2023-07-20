/*
 * f74_i2c2.h
 * -- for STM32F75xxx/STM32F74xxx
 * Author: Nick Fan
 * Date: 6/2023
 */


#ifndef I2C2_H
#define I2C2_H

#include "stm32f7xx.h"
#include "stdbool.h"

#define I2C_REQUEST_SIZE  1U
#define F7_MPU_TIMING     0x0010061A
#define F7_ADC_TIMING     0x00301739
#define RESET_REG         0x00

#define I2C_TIMINGR       F7_ADC_TIMING


// Function prototypes

/*
 * @brief Initializes I2C2 peripheral for PF1 and PF0
 */
void I2C2_Init(void);

/*
 * @brief Sets I2C2 Device Address
 * @param DAddress I2C Peripheral Device Address
 */
void I2C2_SetDevice(uint8_t DAddress);

/*
 * @brief Performs a burst memory write in I2C2
 * @param MemAddress register address of peripheral to access
 * @param data pointer(s) to bytes to send
 * @param size the number of bytes to send
 * @param timeout the timeout in milliseconds
*/
void I2C2_MemWrite(uint8_t MemAddress, uint8_t* data, uint8_t size, uint32_t timeout);

/*
 * @brief Performs a burst memory read in I2C2
 * @param MemAddress register address of peripheral to access
 * @param data pointer(s) for storing received data
 * @param size the number of bytes to read
 * @param timeout the timeout in milliseconds
*/
void I2C2_MemRead(uint8_t MemAddress, uint8_t* data, uint8_t size, uint32_t timeout);

#endif // I2C2_H
