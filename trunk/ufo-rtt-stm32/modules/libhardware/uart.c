/**
 * @file uart.c
 * uart modules implementation
 */

#include "hardware/IUart.h"
#include "hardware/IGyro.h"
#include "math/crc16.h"

#include <stdio.h>

/**
 * @addtogroup ufo
 * @}
 */

/**
 * @addtogroup Hardware Abstract Layer
 * @{
 */

#define MAX_UART_LEN    32

int uart_packet_tx(struct uart_packet_t *packet)
{
    int retval = 0;
    int index = 0;
    uint8_t buf[MAX_UART_LEN];

    if (packet->type >= MAX_PACKET_TYPE)
        return retval;
    if (packet->length <= 0)
        return retval;

    /* copy data from packet */
    buf[0] = packet->type;
    buf[1] = packet->length;
    for (i = 0, index = 2; i < packet->length; i++, index++)
        buf[index] = packet->buf[i];
    buf[index++] = crc16(0, buf, index);
    
#if UART_DEBUG
    printf("uart: data sent to uart:\n");
    printf("uart: type=%d\n", buf[0]);
    printf("uart: length=%d\n", buf[1]);
    for (i = 0; i < buf[1]; i++) {
        printf("%d ", buf[i + 2]);
        if ((i % 4) == 0)
            putchar('\n');
    }
#endif

    /* start to transmit */
    for (i = 0; i < index; i++)
        ;/* TODO send data via uart */
}

int gyro_packet_tx()
{
    struct uart_packet_t packet;
    struct gyro_event_t event;
    int err;
    
    err = gyro_get_value(&event);
    if (err)
        return err;

    packet.type = GET_GYRO_DATA;
    packet.length = 6;
    /* x axis */
    packet.buf[0] = (event.gx >> 8) & 0xFF;
    packet.buf[1] = event.gx & 0xFF;
    /* y axis */
    packet.buf[2] = (event.gy >> 8) & 0xFF;
    packet.buf[3] = event.gy & 0xFF;
    /* z axis */
    packet.buf[4] = (event.gz >> 8) & 0xFF;
    packet.buf[5] = event.gz & 0xFF;

    return uart_packet_tx(&packet);
}

/** @} */

/** @} */