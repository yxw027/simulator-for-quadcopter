/**
 * @file uart.c
 * uart modules implemtation
 */

#include "IUart.h"


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
    buf[index] = packet->checksum;
    
#if UART_DEBUG
    printf("uart: data sent to uart:\n");
    printf("uart: type=%d\n", buf[0]);
    printf("uart: length=%d\n", buf[1]);
    for (i = 0; i < buf[1]; i++) {
        printf("%d ", buf[i + 2]);
        if ((i % 4) == 0)
            puts('\n');
    }
#endif

    /* start to transmit */
    for (i = 0; i < index; i++)
        /* TODO send data via uart */
}

/** @} */

/** @} */