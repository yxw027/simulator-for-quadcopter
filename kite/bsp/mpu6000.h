#ifndef MPU6000_H
#define MPU6000_H

#include <stdbool.h>

#include <freeRTOS.h>
#include <queue.h>

#include <stm32f10x.h>

/* MPU-6000 register map */
#define XG_OFFS_TC      0x00
#define YG_OFFS_TC      0x01
#define ZG_OFFS_TC      0x02
#define X_FINE_GAIN     0x03
#define Y_FINE_GAIN     0x04
#define Z_FINE_GAIN     0x05
#define XA_OFFS_H       0x06
#define XA_OFFS_L       0x07
#define YA_OFFS_H       0x08
#define YA_OFFS_L       0x09
#define ZA_OFFS_H       0x0A
#define ZA_OFFS_L       0x0B
#define PRODUCT_ID      0x0C
#define SELF_TEST_X     0x0D
#define SELF_TEST_Y     0x0E
#define SELF_TEST_Z     0x0F
#define SELF_TEST_A     0x10
#define XG_OFFS_USRH    0x13
#define XG_OFFS_USRL    0x14
#define YG_OFFS_USRH    0x15
#define YG_OFFS_USRL    0x16
#define ZG_OFFS_USRH    0x17
#define ZG_OFFS_USRL    0x18
#define SMPLRT_DIV      0x19
#define CONFIG          0x1A
#define GYRO_CONFIG     0x1B
#define ACCEL_CONFIG    0x1C
#define MOT_THR         0x1F
#define FIFO_EN         0x23
#define INT_PIN_CFG     0x37
#define INT_ENABLE      0x38
#define INT_STATUS      0x3A
#define ACCEL_XOUT_H    0x3B
#define ACCEL_XOUT_L    0x3C
#define ACCEL_YOUT_H    0x3D
#define ACCEL_YOUT_L    0x3E
#define ACCEL_ZOUT_H    0x3F
#define ACCEL_ZOUT_L    0x40
#define TEMP_OUT_H      0x41
#define TEMP_OUT_L      0x42
#define GYRO_XOUT_H     0x43
#define GYRO_XOUT_L     0x44
#define GYRO_YOUT_H     0x45
#define GYRO_YOUT_L     0x46
#define GYRO_ZOUT_H     0x47
#define GYRO_ZOUT_L     0x48
#define USER_CTRL       0x6A
#define PWR_MGMT_1      0x6B
#define PWR_MGMT_2      0x6C
#define BANK_SEL        0x6D
#define MEM_START_ADDR  0x6E
#define MEM_R_W         0x6F
#define DMP_CFG_1       0x70
#define DMP_CFG_2       0x71
#define FIFO_COUNT_H    0x72
#define FIFO_COUNT_L    0x73
#define FIFO_R_W        0x74
#define WHO_AM_I        0x75

#define SPI_WRITE       (0x7F << 0)
#define SPI_READ        (0x1 << 7)

#define MPU6000_Enable()   GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define MPU6000_Disable()  GPIO_SetBits(GPIOA, GPIO_Pin_4)

int mpu6000_init(void);
uint8_t mpu6000_read_byte(uint8_t reg);
void mpu6000_write_byte(uint8_t reg, uint8_t data);
bool mpu6000_irq_handler(void);
xQueueHandle xGetDataReadyQueue(void);
void EXTI3_Config(void);

#endif
