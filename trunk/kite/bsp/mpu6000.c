#include "spi.h"
#include "mpu6000.h"

#define SPI_WRITE		(0x7F << 0)
#define SPI_READ        (0x1 << 7)

#define BIT_I2C_MST_VDDIO   (0x80)
#define BIT_FIFO_EN         (0x40)
#define BIT_DMP_EN          (0x80)
#define BIT_FIFO_RST        (0x04)
#define BIT_DMP_RST         (0x08)
#define BIT_FIFO_OVERFLOW   (0x10)
#define BIT_DATA_RDY_EN     (0x01)
#define BIT_DMP_INT_EN      (0x02)
#define BIT_MOT_INT_EN      (0x40)
#define BITS_FSR            (0x18)
#define BITS_LPF            (0x07)
#define BITS_HPF            (0x07)
#define BITS_CLK            (0x07)
#define BIT_FIFO_SIZE_1024  (0x40)
#define BIT_FIFO_SIZE_2048  (0x80)
#define BIT_FIFO_SIZE_4096  (0xC0)
#define BIT_RESET           (0x80)
#define BIT_SLEEP           (0x40)
#define BIT_S0_DELAY_EN     (0x01)
#define BIT_S2_DELAY_EN     (0x04)
#define BITS_SLAVE_LENGTH   (0x0F)
#define BIT_SLAVE_BYTE_SW   (0x40)
#define BIT_SLAVE_GROUP     (0x10)
#define BIT_SLAVE_EN        (0x80)
#define BIT_I2C_READ        (0x80)
#define BITS_I2C_MASTER_DLY (0x1F)
#define BIT_AUX_IF_EN       (0x20)
#define BIT_ACTL            (0x80)
#define BIT_LATCH_EN        (0x20)
#define BIT_ANY_RD_CLR      (0x10)
#define BIT_BYPASS_EN       (0x02)
#define BITS_WOM_EN         (0xC0)
#define BIT_LPA_CYCLE       (0x20)
#define BIT_STBY_XA         (0x20)
#define BIT_STBY_YA         (0x10)
#define BIT_STBY_ZA         (0x08)
#define BIT_STBY_XG         (0x04)
#define BIT_STBY_YG         (0x02)
#define BIT_STBY_ZG         (0x01)
#define BIT_STBY_XYZA       (BIT_STBY_XA | BIT_STBY_YA | BIT_STBY_ZA)
#define BIT_STBY_XYZG       (BIT_STBY_XG | BIT_STBY_YG | BIT_STBY_ZG)

#define MPU6000_Enable()   GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define MPU6000_Disable()  GPIO_SetBits(GPIOA, GPIO_Pin_4)

static uint8_t mpu6000_read_byte(uint8_t reg)
{
    uint8_t data;

    MPU6000_Enable();
    SPI_WriteByte(SPI_MASTER, SPI_READ | reg);
    data = SPI_ReadByte(SPI_MASTER);
    MPU6000_Disable();

    return data;
}

static void mpu6000_write_byte(uint8_t reg, uint8_t data)
{
    MPU6000_Enable();
    SPI_WriteByte(SPI_MASTER, SPI_WRITE & reg);
    SPI_WriteByte(SPI_MASTER, data);
    MPU6000_Disable();	
}

int mpu6000_init()
{
    uint8_t val;

    /* Reset device. */
//    mpu6000_write_byte(PWR_MGMT_1, 0x80);
//    while (mpu6000_read_byte(PWR_MGMT_1) & 0x80);

    mpu6000_write_byte(USER_CTRL, (0x01 << 2) | (0x01 << 1) | (0x01 << 0));
    while (mpu6000_read_byte(USER_CTRL) & 0x07);

    val = mpu6000_read_byte(WHO_AM_I);
    if (val != 0x68)
        return -6; /* No such device or address */

    val = mpu6000_read_byte(PRODUCT_ID);

    mpu6000_write_byte(PWR_MGMT_1, 0x03);

    mpu6000_write_byte(SMPLRT_DIV, 0x07);

    mpu6000_write_byte(CONFIG, 0x00);

    mpu6000_write_byte(GYRO_CONFIG, (1 << 3));

    mpu6000_write_byte(ACCEL_CONFIG, (1 << 3));

//	mpu6000_write_byte(MOT_THR, 0);

    val = ((1 << 7) | (1 << 6) | (1 << 5) | (1 <<4) | (1 << 3));
    mpu6000_write_byte(FIFO_EN, val);

    val = (0 << 7) | (1 << 5) | (1 << 4);
    mpu6000_write_byte(INT_PIN_CFG, val);

    mpu6000_write_byte(INT_ENABLE, (1 << 0));

    return 0;
}
