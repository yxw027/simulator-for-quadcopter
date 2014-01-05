#include <string.h>

#include "bsp.h"

static xQueueHandle xDataReady;

#define BIT_I2C_MST_VDDIO   (0x80)
#define BIT_FIFO_EN         (0x40)
#define BIT_I2C_IF_DIS		(0x10)
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

#define CLK_SEL_PLL_GX      0x01
#define CLK_SEL_PLL_GY      0x02
#define CLK_SEL_PLL_GZ      0x03

#define BITS_FS_250DPS    	0x00
#define BITS_FS_500DPS      0x08
#define BITS_FS_1000DPS     0x10
#define BITS_FS_2000DPS     0x18

#define BITS_AFS_2G  		0x00
#define BITS_AFS_4G       	0x08
#define BITS_AFS_8G     	0x10
#define BITS_AFS_16G     	0x18

#define BIT_TEMP_FIFO_EN    0x80
#define BIT_XG_FIFO_EN      0x40
#define BIT_YG_FIFO_EN      0x20
#define BIT_ZG_FIFO_EN      0x10
#define BIT_ACCEL_FIFO_EN   0x08

uint8_t mpu6000_read_byte(uint8_t reg)
{
    uint8_t data;

    MPU6000_Enable();
    SPI_WriteByte(SPI_MASTER, SPI_READ | reg);
    data = SPI_ReadByte(SPI_MASTER);
    MPU6000_Disable();

    return data;
}

void mpu6000_write_byte(uint8_t reg, uint8_t data)
{
    MPU6000_Enable();
    SPI_WriteByte(SPI_MASTER, SPI_WRITE & reg);
    SPI_WriteByte(SPI_MASTER, data);
    MPU6000_Disable();
}

static int mpu6000_hw_init(void)
{
    uint8_t val;

    /* Reset device. */
    mpu6000_write_byte(PWR_MGMT_1, BIT_RESET);
    delay_ms(100);

//    mpu6000_write_byte(USER_CTRL, (0x01 << 2) | (0x01 << 1) | (0x01 << 0));
//    while (mpu6000_read_byte(USER_CTRL) & 0x07);
#if 1
    val = mpu6000_read_byte(WHO_AM_I);
    if (val != 0x68)
        return -6; /* No such device or address */
    delay_us(1);
#endif

//    val = mpu6000_read_byte(PRODUCT_ID);

    mpu6000_write_byte(PWR_MGMT_1, 0x01);
    delay_us(1);

    mpu6000_write_byte(SMPLRT_DIV, 0x0F);
    delay_us(1);

    mpu6000_write_byte(CONFIG, 0x00);
    delay_us(1);

    mpu6000_write_byte(GYRO_CONFIG, (1 << 3));
    delay_us(1);

    mpu6000_write_byte(ACCEL_CONFIG, (1 << 3));
    delay_us(1);

    //mpu6000_write_byte(MOT_THR, 0);

    mpu6000_write_byte(FIFO_EN, BIT_TEMP_FIFO_EN | BIT_XG_FIFO_EN | BIT_YG_FIFO_EN | BIT_ZG_FIFO_EN | BIT_ACCEL_FIFO_EN);

    mpu6000_write_byte(FIFO_EN, val);
    delay_us(1);

    mpu6000_write_byte(USER_CTRL, BIT_FIFO_EN | BIT_I2C_IF_DIS);
    delay_us(1);

    mpu6000_write_byte(INT_PIN_CFG, BIT_ANY_RD_CLR);
    delay_us(1);

    val = (1 << 6) | (1 << 4) | (1 << 0);
    mpu6000_write_byte(INT_ENABLE, val);
    delay_ms(100);
    mpu6000_write_byte(INT_ENABLE, val);
    return 0;
}

int mpu6000_init(void)
{
    int retval = 0;

    retval = mpu6000_hw_init();
    if (retval < 0)
        return retval;
    xDataReady = xQueueCreate(10, sizeof(sensor_t));
    if (xDataReady == 0)
        retval = -1;

    return retval;
}

//extern xQueueHandle xGetDataReadyQueue(void);
bool mpu6000_irq_handler(void)
{
    uint8_t int_status;
    uint8_t buf[2];
    uint16_t fifo_count;
    sensor_t sensor_event;
    portBASE_TYPE pxHigherPriorityTaskWoken;
    xQueueHandle xDataReady = xGetDataReadyQueue();
    memset(&sensor_event, 0, sizeof(sensor_t));

    /* get interrupt status */
    int_status = mpu6000_read_byte(INT_STATUS);
    /* data ready interrupt */
    if (int_status & BIT_DATA_RDY_EN) {
        buf[0] = mpu6000_read_byte(FIFO_COUNT_H);
        buf[1] = mpu6000_read_byte(FIFO_COUNT_L);
        fifo_count = (buf[0]<< 8) | buf[1];
        /* get raw data */
        if (fifo_count >= 14) {
            uint8_t send_buf[15] = { /*FIFO_R_W*/ACCEL_XOUT_H | SPI_READ, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            uint8_t recv_buf[15] = { 0 };
            MPU6000_Enable();
            spi_master_xfer(SPI1, &send_buf[0], sizeof(send_buf), &recv_buf[0], sizeof(recv_buf));
            MPU6000_Disable();

            sensor_event.type = SENSOR_TYPE_MPU6000;
            sensor_event.name = "mpu_6000";
            sensor_event.data.value[0] = recv_buf[1];
            sensor_event.data.value[1] = recv_buf[2];
            sensor_event.data.value[2] = recv_buf[3];
            sensor_event.data.value[3] = recv_buf[4];
            sensor_event.data.value[4] = recv_buf[5];
            sensor_event.data.value[5] = recv_buf[6];
            sensor_event.data.value[6] = recv_buf[7];
            sensor_event.data.value[7] = recv_buf[8];
            sensor_event.data.value[8] = recv_buf[9];
            sensor_event.data.value[9] = recv_buf[10];
            sensor_event.data.value[10] = recv_buf[11];
            sensor_event.data.value[11] = recv_buf[12];
            sensor_event.data.value[12] = recv_buf[13];
            sensor_event.data.value[13] = recv_buf[14];

            xQueueSendFromISR(xDataReady, &sensor_event, &pxHigherPriorityTaskWoken);
            return (pdTRUE == pxHigherPriorityTaskWoken);
        }
    }
    /* FIFO buffer overflow interrupt */
    if (int_status & BIT_FIFO_OVERFLOW) {
        /* ignore */
    }
    /* motion detect interrupt */
    if (int_status & BIT_MOT_INT_EN) {
        /* ignore */
    }
    return false;
}

xQueueHandle xGetDataReadyQueue(void)
{
    if (xDataReady)
        return xDataReady;
    else
        return 0;
}
