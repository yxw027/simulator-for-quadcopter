#ifndef _FIFO_H
#define _FIFO_H

#include <stdbool.h>

struct fifo {
	unsigned char *buf;
	int size;
	int start;
	int end;
};

int fifo_init(struct fifo *fifo, unsigned char *buf, int len);

bool is_fifo_empty(struct fifo *fifo);

bool is_fifo_full(struct fifo *fifo);

int fifo_available_space(struct fifo *fifo);

int fifo_available_data(struct fifo *fifo);
    
int fifo_write(struct fifo* fifo, unsigned char *buffer, int len);

int fifo_read(struct fifo* fifo, unsigned char *buffer, unsigned int len);

#endif /* _FIFO_H */
