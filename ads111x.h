

#ifndef ADS111X_H
#define ADS111X_H

#include "i2c2.h"


#define ADS_ADDRESS_GND				(0b1001000 << 1U)
#define ADS_ADDRESS_VDD				(0b1001001 << 1U)
#define ADS_ADDRESS_SDA				(0b1001010 << 1U)
#define ADS_ADDRESS_SCL				(0b1001011 << 1U)

#define ADS_REG_CONVERSION_PTR		0x0U
#define ADS_REG_CONFIG_PTR			0x1U
#define ADS_REG_LO_THRESH_PTR		0x2U
#define ADS_REG_HI_THRESH_PTR		0x3U

#define ADS_CONFIG_OS				(0x1U << 15U)
#define ADS_CONFIG_MUX_Pos			12U
#define ADS_CONFIG_DR_Pos			0U

// Quickstart
#define ADS_CONFIG_UPPER_DEFAULT	0b10000100
#define ADS_CONFIG_LOWER_DEFAULT	0b10000011


void ADS_Init(uint8_t DAddress);
uint16_t ADS_SampleChannel(uint8_t channel);

#endif // ADS111X_H
