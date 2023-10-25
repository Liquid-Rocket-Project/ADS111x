/*
 * ads111x.c
 * author: Nick Fan
 * date: 7/2023
 */

#include "ads111x.h"

static uint8_t rxdata[2] = {};

static uint8_t configBuffer[2] = {};



static inline void Get_Configs(ADS111x *adc, uint8_t channel, uint8_t *configsBuff) {
	/* You can edit this function along with the base config
	 * macros to adjust what gets set each time
	 */
	configsBuff[1] = ADS_CONFIG_LOWER_BASE | adc->datarate | adc->interruptEn;
	configsBuff[0] = ADS_CONFIG_UPPER_BASE | ADS_CONFIG_OS | adc->mode
				| adc->gain | channel;
}

ADS111x ADS_Default_Struct(uint8_t DAddress) {
	ADS111x ret = {
		ADS_PGA_4_096V,
		ADS_CONFIG_MODE,
		ADS_DR_128_SPS,
		ADS_COMP_QUE_DISABLE,
		DAddress,
	};
	return ret;

}

void ADS_InitSerial(ADS111x *adc) {
	// Initialize i2c
	adc->init();

}

int16_t ADS_SampleChannel(ADS111x *adc, uint8_t channel) {

	// Store configs in buffer to send
	Get_Configs(adc, channel, configBuffer);

	// Set target adc
	adc->selectDevice(adc->DAddress);

	// Configure and start conversion
	adc->memWrite(ADS_REG_CONFIG_PTR, configBuffer, ADS_REGISTER_SIZE, 1000);

	// Wait for adc to be no longer in conversion
	rxdata[0] = 0;
	while (!(rxdata[0] & ADS_CONFIG_OS)) {
		adc->memRead(ADS_REG_CONFIG_PTR, rxdata, ADS_REGISTER_SIZE, 1000);
	}

	// Read last conversion
	adc->memRead(ADS_REG_CONVERSION_PTR, rxdata, ADS_REGISTER_SIZE, 1000);

	return (int16_t) ((rxdata[0] << 8) | rxdata[1]);

}

void ADS_StartConversion(ADS111x *adc, uint8_t channel) {
	// Store configs in buffer to send
	Get_Configs(adc, channel, configBuffer);

	// Set target adc
	adc->selectDevice(adc->DAddress);

	// Configure and start conversion
	adc->memWrite(ADS_REG_CONFIG_PTR, configBuffer, ADS_REGISTER_SIZE, 1000);
}

int16_t ADS_ReadLastConversion(ADS111x *adc) {
	// Set target adc
	adc->selectDevice(adc->DAddress);

	// Read last conversion
	adc->memRead(ADS_REG_CONVERSION_PTR, rxdata, ADS_REGISTER_SIZE, 1000);

	return (int16_t) ((rxdata[0] << 8) | rxdata[1]);
}

int16_t ADS_ReadRegister(ADS111x *adc, uint8_t regPtr) {
	// Set target adc
	adc->selectDevice(adc->DAddress);

	// Read config register
	adc->memRead(regPtr, rxdata, ADS_REGISTER_SIZE, 1000);

	return (int16_t) ((rxdata[0] << 8) | rxdata[1]);
}

uint16_t ADS_ReadConfigs(ADS111x *adc) {
	// Set target adc
	adc->selectDevice(adc->DAddress);

	// Read config register
	adc->memRead(ADS_REG_CONFIG_PTR, rxdata, ADS_REGISTER_SIZE, 1000);

	return (uint16_t) ((rxdata[0] << 8) | rxdata[1]);
}

void ADS_EnableConversionReady(ADS111x *adc, uint8_t compQue) {
	// Set interrupt set value
	adc->interruptEn = compQue;

	// Set target adc
	adc->selectDevice(adc->DAddress);

	// Reset bit 15 in Lo Thresh register
	adc->memRead(ADS_REG_LO_THRESH_PTR, rxdata, ADS_REGISTER_SIZE, 1000);
	rxdata[0] &= ~ADS_LO_THRESH_ALERT;
	adc->memWrite(ADS_REG_LO_THRESH_PTR, rxdata, ADS_REGISTER_SIZE, 1000);

	// Set bit 15 in Hi Tresh register
	adc->memRead(ADS_REG_HI_THRESH_PTR, rxdata, ADS_REGISTER_SIZE, 1000);
	rxdata[0] |= ADS_HI_THRESH_ALERT;
	adc->memWrite(ADS_REG_LO_THRESH_PTR, rxdata, ADS_REGISTER_SIZE, 1000);

}
