/*
 * ads111x.h
 * author: Nick Fan
 * date: 7/2023
 */

#ifndef ADS111X_H
#define ADS111X_H

#include "i2c2.h"


// ADS I2C Device Address (depending on ADDR Pin)
#define ADS_ADDRESS_GND				(0b1001000 << 1U)
#define ADS_ADDRESS_VDD				(0b1001001 << 1U)
#define ADS_ADDRESS_SDA				(0b1001010 << 1U)
#define ADS_ADDRESS_SCL				(0b1001011 << 1U)

// ADS Data Registers
#define ADS_REG_CONVERSION_PTR		0x0U
#define ADS_REG_CONFIG_PTR			0x1U
#define ADS_REG_LO_THRESH_PTR		0x2U
#define ADS_REG_HI_THRESH_PTR		0x3U

// Config reg bits
#define ADS_CONFIG_OS				(0x1U << 7U)
#define ADS_CONFIG_MODE				(0x1U << 0U)
#define ADS_CONFIG_MODE_CONT		(0x0U << 0U)
#define ADS_CONFIG_MODE_SS			ADS_CONFIG_MODE
#define ADS_CONFIG_MUX_Pos			5U
#define ADS_CONFIG_PGA_Pos			2U
#define ADS_CONFIG_DR_Pos			5U
#define ADS_CONFIG_COMP_MODE		(0x1U << 4U)
#define ADS_CONFIG_COMP_POL			(0x1U << 3U)
#define ADS_CONFIG_COMP_LAT			(0x1U << 2U)
#define ADS_CONFIG_COMP_QUE_Pos		0U

// Channel Mux selection
#define ADS_MUX_DIFF_P0_N1			(0b000U << ADS_CONFIG_MUX_Pos)
#define ADS_MUX_DIFF_P0_N3			(0b001U << ADS_CONFIG_MUX_Pos)
#define ADS_MUX_DIFF_P1_N3			(0b010U << ADS_CONFIG_MUX_Pos)
#define ADS_MUX_DIFF_P2_N3			(0b011U << ADS_CONFIG_MUX_Pos)
#define ADS_MUX_SING_P0				(0b100U << ADS_CONFIG_MUX_Pos)
#define ADS_MUX_SING_P1				(0b101U << ADS_CONFIG_MUX_Pos)
#define ADS_MUX_SING_P2				(0b110U << ADS_CONFIG_MUX_Pos)
#define ADS_MUX_SING_P3				(0b111U << ADS_CONFIG_MUX_Pos)

// Gain amplifier
#define ADS_PGA_6_144V				(0b000U << ADS_CONFIG_PGA_Pos)
#define ADS_PGA_4_096V				(0b001U << ADS_CONFIG_PGA_Pos)
#define ADS_PGA_2_048V				(0b010U << ADS_CONFIG_PGA_Pos)
#define ADS_PGA_1_024V				(0b011U << ADS_CONFIG_PGA_Pos)
#define ADS_PGA_0_512V				(0b100U << ADS_CONFIG_PGA_Pos)
#define ADS_PGA_0_256V_1			(0b101U << ADS_CONFIG_PGA_Pos)
#define ADS_PGA_0_256V_2			(0b110U << ADS_CONFIG_PGA_Pos)
#define ADS_PGA_0_256V_3			(0b111U << ADS_CONFIG_PGA_Pos)

// Datarate
#define ADS_DR_8_SPS				(0b000U << ADS_CONFIG_DR_Pos)
#define ADS_DR_16_SPS				(0b001U << ADS_CONFIG_DR_Pos)
#define ADS_DR_32_SPS				(0b010U << ADS_CONFIG_DR_Pos)
#define ADS_DR_64_SPS				(0b011U << ADS_CONFIG_DR_Pos)
#define ADS_DR_128_SPS				(0b100U << ADS_CONFIG_DR_Pos)
#define ADS_DR_250_SPS				(0b101U << ADS_CONFIG_DR_Pos)
#define ADS_DR_475_SPS				(0b110U << ADS_CONFIG_DR_Pos)
#define ADS_DR_860_SPS				(0b111U << ADS_CONFIG_DR_Pos)

// Quickstart
#define ADS_CONFIG_UPPER_DEFAULT	0b10000100U
#define ADS_CONFIG_LOWER_DEFAULT	0b10000011U

#define ADS_CONFIG_UPPER_BASE		0b10000000U
#define ADS_CONFIG_LOWER_BASE		0b00000011U

#define ADS_CONFIG_BUFFER_SIZE		2U

// Function pointers
typedef void (*I2C_Init) (void);
typedef void (*I2C_SetDevice) (uint8_t DAddress);
typedef void (*I2C_MemWrite) (uint8_t MemAddress, uint8_t* data, uint8_t size, uint32_t timeout);
typedef void (*I2C_MemRead) (uint8_t MemAddress, uint8_t* data, uint8_t size, uint32_t timeout);

// Typedefs
typedef struct {
	// Config parameters
	uint8_t gain;
	uint8_t mode;
	uint8_t datarate;
	uint8_t DAddress;

	// Serial interface
	I2C_Init init;
	I2C_SetDevice selectDevice;
	I2C_MemWrite memWrite;
	I2C_MemRead memRead;

} ADS111x;

// Function prototypes

/*
 * @brief Creates and returns an ADS111x struct with configs setup (no serial)
 * @param DAddress the device address of the ADS
 * @returns the newly created ADS111x struct
 */
inline ADS111x ADS_Default_Struct(uint8_t DAddress);

/*
 * @brief Initializes ADC and I2C
 * @param adc the ADS111x to initialize serial for (serial functions 
 * in ADS struct must be initialized before calling this function)
 */
void ADS_InitSerial(ADS111x *adc);

/*
 * @brief Samples the indicated channel
 * @param adc the ADS111x from which to use configs and I2C
 * @param channel the analog channel number
 * @returns the 16-bit reading from the ADS
 */
uint16_t ADS_SampleChannel(ADS111x *adc, uint8_t channel);

/*
 * @brief Requests the start of a conversion in the indicated channel
 * @param adc the ADS111x from which to use configs and I2C
 * @param channel the analog channel number
 */
void ADS_StartConversion(ADS111x *adc, uint8_t channel);

/*
 * @brief Reads the last conversion
 * @param adc the ADS111x from which to use configs and I2C
 * @returns the 16-bit reading from the ADS
 */
uint16_t ADS_ReadLastConversion(ADS111x *adc);

#endif // ADS111X_H
