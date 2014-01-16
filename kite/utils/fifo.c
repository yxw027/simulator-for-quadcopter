/**
 * @file fifo.c
 * @brief fifo buffer implementation
 */

#include "fifo.h"

#include <string.h>

#ifndef max
  #define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
  #define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

int fifo_init(struct fifo *fifo, uint8_t *buffer, int len)
{
    if (len & (len - 1))
        return -1;

    fifo->xMutex = xSemaphoreCreateMutex();
    if (fifo->xMutex != NULL) {
        fifo->buf = buffer;
        fifo->size = len;
        fifo->start = 0;
        fifo->end = 0;
        return 0;
    }
    return -1;
}

void fifo_destroy(struct fifo *fifo)
{
    if (fifo->xMutex)
        vSemaphoreDelete(fifo->xMutex);
}

bool is_fifo_empty(struct fifo *fifo)
{
    return fifo->start == fifo->end;
}

bool is_fifo_full(struct fifo *fifo)
{
    return fifo->end == (fifo->start ^ fifo->size); /* This inverts the most significant bit of start before comparison */
}

int available_space(struct fifo *fifo)
{
    return fifo->size - fifo->end + fifo->start;
}

int available_data(struct fifo *fifo)
{
    return fifo->end - fifo->start;
}

int fifo_write(struct fifo *fifo, unsigned char *buffer, int len)
{
    unsigned int l;

    if (xSemaphoreTake(fifo->xMutex, (portTickType)10) == pdTRUE) {
        /* available space */
        len = min(len, fifo->size - fifo->end + fifo->start);

        /* first put the data starting form fifo->end to the buffer end */
        l = min(len, fifo->size - (fifo->end & (fifo->size - 1)));
        memcpy(fifo->buf + (fifo->end & (fifo->size - 1)), buffer, l);

        /* then put rest (if any) at the beginning of the buffer */
        memcpy(fifo->buf, buffer + l, len - l);

        fifo->end += len;

        xSemaphoreGive(fifo->xMutex);
        return len;
    }

    return -1;
}

int fifo_read(struct fifo *fifo, unsigned char *buffer, unsigned int len)
{
    unsigned int l;

    if (xSemaphoreTake(fifo->xMutex, (portTickType)10) == pdTRUE) {
        /* available data length */
        len = min(len, fifo->end - fifo->start);

        l = min(len, fifo->size - (fifo->start & (fifo->size - 1)));
        /* first get the data from fifo->start until the end of the buffer */
        memcpy(buffer, fifo->buf + (fifo->start & (fifo->size - 1)), len);
        /* then get the rest (if any) from the beginning of the buffer */
        memcpy(buffer + l, fifo->buf, len - l);

        fifo->start += len;

        return len;
    }

    return -1;
}
 
/**
 * @ }
 */
