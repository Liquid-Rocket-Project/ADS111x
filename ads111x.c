

#include "ads111x.h"

static uint8_t config_default[2] = {
		ADS_CONFIG_UPPER_DEFAULT,
		ADS_CONFIG_LOWER_DEFAULT
};

static uint8_t rxdata[2] = {};

void ADS_Init(uint8_t DAddress) {
	I2C2_Init();
	I2C2_SetDevice(DAddress);

}

uint16_t ADS_SampleChannel(uint8_t channel) {

	I2C2_MemWrite(ADS_REG_CONFIG_PTR, config_default, 2, 1000);

	I2C2_MemRead(ADS_REG_CONVERSION_PTR, rxdata, 2, 1000);

	return (uint16_t) ((rxdata[1] << 8) | rxdata[0]);

}
