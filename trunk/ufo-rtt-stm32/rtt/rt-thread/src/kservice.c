/*
 * File      : kservice.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-16     Bernard      the first version
 * 2006-05-25     Bernard      rewrite vsprintf
 * 2006-08-10     Bernard      add rt_show_version
 * 2010-03-17     Bernard      remove rt_strlcpy function
 *                             fix gcc compiling issue.
 * 2010-04-15     Bernard      remove weak definition on ICCM16C compiler
 */

#include <rtthread.h>
#include <rthw.h>
#include <stdio.h>

/* use precision */
#define RT_PRINTF_PRECISION

/**
 * @addtogroup KernelService
 */

/*@{*/

/* global errno in RT-Thread */
static volatile int _errno;

#if defined(RT_USING_DEVICE) && defined(RT_USING_CONSOLE)
static rt_device_t _console_device = RT_NULL;
#endif

/*
 * This function will get errno
 *
 * @return errno
 */
rt_err_t rt_get_errno(void)
{
	rt_thread_t tid;

	if (rt_interrupt_get_nest() != 0)
	{
		/* it's in interrupt context */
		return _errno;
	}

	tid = rt_thread_self();
	if (tid == RT_NULL)
		return _errno;

	return tid->error;
}

/*
 * This function will set errno
 *
 * @param error the errno shall be set
 */
void rt_set_errno(rt_err_t error)
{
	rt_thread_t tid;

	if (rt_interrupt_get_nest() != 0)
	{
		/* it's in interrupt context */
		_errno = error;

		return;
	}

	tid = rt_thread_self();
	if (tid == RT_NULL)
	{
		_errno = error;
		
		return;
	}

	tid->error = error;
}

/**
 * This function returns errno.
 *
 * @return the errno in the system
 */
int *_rt_errno(void)
{
	rt_thread_t tid;
	
	if (rt_interrupt_get_nest() != 0)
		return (int *)&_errno;

	tid = rt_thread_self();
	if (tid != RT_NULL)
		return (int *)&(tid->error);

	return (int *)&_errno;
}

/**
 * This function will set the content of memory to specified value
 *
 * @param s the address of source memory
 * @param c the value shall be set in content
 * @param count the copied length
 *
 * @return the address of source memory
 */
void *rt_memset(void *s, int c, rt_ubase_t count)
{
#ifdef RT_TINY_SIZE
	char *xs = (char *)s;

	while (count--)
		*xs++ = c;

	return s;
#else
#define LBLOCKSIZE      (sizeof(rt_int32_t))
#define UNALIGNED(X)    ((rt_int32_t)X & (LBLOCKSIZE - 1))
#define TOO_SMALL(LEN)  ((LEN) < LBLOCKSIZE)

	int i;
	char *m = (char *)s;
	rt_uint32_t buffer;
	rt_uint32_t *aligned_addr;
	rt_uint32_t d = c & 0xff;

	if (!TOO_SMALL(count) && !UNALIGNED(s))
	{
		/* If we get this far, we know that n is large and m is word-aligned. */
		aligned_addr = (rt_uint32_t *)s;

		/* Store D into each char sized location in BUFFER so that
		 * we can set large blocks quickly.
		 */
		if (LBLOCKSIZE == 4)
		{
			buffer = (d << 8) | d;
			buffer |= (buffer << 16);
		}
		else
		{
			buffer = 0;
			for (i = 0; i < LBLOCKSIZE; i++)
				buffer = (buffer << 8) | d;
		}

		while (count >= LBLOCKSIZE*4)
		{
			*aligned_addr++ = buffer;
			*aligned_addr++ = buffer;
			*aligned_addr++ = buffer;
			*aligned_addr++ = buffer;
			count -= 4 * LBLOCKSIZE;
		}

		while (count >= LBLOCKSIZE)
		{
			*aligned_addr++ = buffer;
			count -= LBLOCKSIZE;
		}

		/* Pick up the remainder with a bytewise loop. */
		m = (char *)aligned_addr;
	}

	while (count--)
	{
		*m++ = (char)d;
	}

	return s;

#undef LBLOCKSIZE
#undef UNALIGNED
#undef TOO_SMALL
#endif
}

/**
 * This function will copy memory content from source address to destination
 * address.
 *
 * @param dst the address of destination memory
 * @param src  the address of source memory
 * @param count the copied length
 *
 * @return the address of destination memory
 */
void *rt_memcpy(void *dst, const void *src, rt_ubase_t count)
{
#ifdef RT_TINY_SIZE
	char *tmp = (char *)dst, *s = (char *)src;

	while (count--)
		*tmp++ = *s++;

	return dst;
#else

#define UNALIGNED(X, Y) \
	(((rt_int32_t)X & (sizeof(rt_int32_t) - 1)) | ((rt_int32_t)Y & (sizeof(rt_int32_t) - 1)))
#define BIGBLOCKSIZE    (sizeof(rt_int32_t) << 2)
#define LITTLEBLOCKSIZE (sizeof(rt_int32_t))
#define TOO_SMALL(LEN)  ((LEN) < BIGBLOCKSIZE)

	char *dst_ptr = (char *)dst;
	char *src_ptr = (char *)src;
	rt_int32_t *aligned_dst;
	rt_int32_t *aligned_src;
	int len = count;

	/* If the size is small, or either SRC or DST is unaligned,
	then punt into the byte copy loop.  This should be rare. */
	if (!TOO_SMALL(len) && !UNALIGNED(src_ptr, dst_ptr))
	{
		aligned_dst = (rt_int32_t *)dst_ptr;
		aligned_src = (rt_int32_t *)src_ptr;

		/* Copy 4X long words at a time if possible. */
		while (len >= BIGBLOCKSIZE)
		{
			*aligned_dst++ = *aligned_src++;
			*aligned_dst++ = *aligned_src++;
			*aligned_dst++ = *aligned_src++;
			*aligned_dst++ = *aligned_src++;
			len -= BIGBLOCKSIZE;
		}

		/* Copy one long word at a time if possible. */
		while (len >= LITTLEBLOCKSIZE)
		{
			*aligned_dst++ = *aligned_src++;
			len -= LITTLEBLOCKSIZE;
		}

		/* Pick up any residual with a byte copier. */
		dst_ptr = (char *)aligned_dst;
		src_ptr = (char *)aligned_src;
	}

	while (len--)
		*dst_ptr++ = *src_ptr++;

	return dst;
#undef UNALIGNED
#undef BIGBLOCKSIZE
#undef LITTLEBLOCKSIZE
#undef TOO_SMALL
#endif
}

/**
 * This function will move memory content from source address to destination
 * address.
 *
 * @param dest the address of destination memory
 * @param src  the address of source memory
 * @param n the copied length
 *
 * @return the address of destination memory
 */
void *rt_memmove(void *dest, const void *src, rt_ubase_t n)
{
	char *tmp = (char *)dest, *s = (char *)src;

	if (s < tmp && tmp < s + n)
	{
		tmp += n;
		s += n;

		while (n--)
			*(--tmp) = *(--s);
	}
	else
	{
		while (n--)
			*tmp++ = *s++;
	}

	return dest;
}

/**
 * This function will compare two areas of memory
 *
 * @param cs one area of memory
 * @param ct znother area of memory
 * @param count the size of the area
 *
 * @return the result
 */
rt_int32_t rt_memcmp(const void *cs, const void *ct, rt_ubase_t count)
{
	const unsigned char *su1, *su2;
	int res = 0;

	for (su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--)
		if ((res = *su1 - *su2) != 0)
			break;

	return res;
}

/**
 * This function will return the first occurrence of a string.
 *
 * @param s1 the source string
 * @param s2 the find string
 *
 * @return the first occurrence of a s2 in s1, or RT_NULL if no found.
 */
char *rt_strstr(const char *s1, const char *s2)
{
	int l1, l2;

	l2 = rt_strlen(s2);
	if (!l2)
		return (char *)s1;
	l1 = rt_strlen(s1);
	while (l1 >= l2)
	{
		l1 --;
		if (!rt_memcmp(s1, s2, l2))
			return (char *)s1;
		s1 ++;
	}

	return RT_NULL;
}

/**
 * This function will compare two strings while ignoring differences in case
 *
 * @param a the string to be compared
 * @param b the string to be compared
 *
 * @return the result
 */
rt_uint32_t rt_strcasecmp(const char *a, const char *b)
{
	int ca, cb;

	do
	{
		ca = *a++ & 0xff;
		cb = *b++ & 0xff;
		if (ca >= 'A' && ca <= 'Z')
			ca += 'a' - 'A';
		if (cb >= 'A' && cb <= 'Z')
			cb += 'a' - 'A';
	}
	while (ca == cb && ca != '\0');

	return ca - cb;
}

/**
 * This function will copy string no more than n bytes.
 *
 * @param dst the string to copy
 * @param src the string to be copied
 * @param n the maximum copied length
 *
 * @return the result
 */
char *rt_strncpy(char *dst, const char *src, rt_ubase_t n)
{
	if (n != 0)
	{
		char *d = dst;
		const char *s = src;

		do
		{
			if ((*d++ = *s++) == 0)
			{
				/* NUL pad the remaining n-1 bytes */
				while (--n != 0)
					*d++ = 0;
				break;
			}
		} while (--n != 0);
	}

	return (dst);
}

/**
 * This function will compare two strings with specified maximum length
 *
 * @param cs the string to be compared
 * @param ct the string to be compared
 * @param count the maximum compare length
 *
 * @return the result
 */
rt_ubase_t rt_strncmp(const char *cs, const char *ct, rt_ubase_t count)
{
	register signed char __res = 0;

	while (count)
	{
		if ((__res = *cs - *ct++) != 0 || !*cs++)
			break;
		count --;
	}

	return __res;
}

/**
 * This function will compare two strings without specified length
 *
 * @param cs the string to be compared
 * @param ct the string to be compared
 *
 * @return the result
 */
rt_ubase_t rt_strcmp(const char *cs, const char *ct)
{
	while (*cs && *cs == *ct)
		cs++, ct++;

	return (*cs - *ct);
}

/**
 * This function will return the length of a string, which terminate will
 * null character.
 *
 * @param s the string
 *
 * @return the length of string
 */
rt_ubase_t rt_strlen(const char *s)
{
	const char *sc;

	for (sc = s; *sc != '\0'; ++sc) /* nothing */
		;

	return sc - s;
}

#ifdef RT_USING_HEAP
/**
 * This function will duplicate a string.
 *
 * @param s the string to be duplicated
 *
 * @return the duplicated string pointer
 */
char *rt_strdup(const char *s)
{
	rt_size_t len = rt_strlen(s) + 1;
	char *tmp = (char *)rt_malloc(len);

	if (!tmp)
		return RT_NULL;

	rt_memcpy(tmp, s, len);

	return tmp;
}
#endif

/**
 * This function will show the version of rt-thread rtos
 */
void rt_show_version(void)
{
	rt_kprintf("\n \\ | /\n");
	rt_kprintf("- RT -     Thread Operating System\n");
	rt_kprintf(" / | \\     %d.%d.%d build %s\n", RT_VERSION, RT_SUBVERSION, RT_REVISION, __DATE__);
	rt_kprintf(" 2006 - 2012 Copyright by rt-thread team\n");
}

/* private function */
#define isdigit(c)  ((unsigned)((c) - '0') < 10)


#define ZEROPAD     (1 << 0)	/* pad with zero */
#define SIGN        (1 << 1)	/* unsigned/signed long */
#define PLUS        (1 << 2)	/* show plus */
#define SPACE       (1 << 3)	/* space if plus */
#define LEFT        (1 << 4)	/* left justified */
#define SPECIAL     (1 << 5)	/* 0x */
#define LARGE       (1 << 6)	/* use 'ABCDEF' instead of 'abcdef' */

/**
 * This function will fill a formatted string to buffer
 *
 * @param buf the buffer to save formatted string
 * @param arg_ptr the arg_ptr
 * @param format the format
 */
rt_int32_t rt_vsprintf(char *buf, const char *format, va_list arg_ptr)
{
	return vsnprintf(buf, (rt_size_t) -1, format, arg_ptr);
}

/**
 * This function will fill a formatted string to buffer
 *
 * @param buf the buffer to save formatted string
 * @param format the format
 */
rt_int32_t rt_sprintf(char *buf, const char *format, ...)
{
	rt_int32_t n;
	va_list arg_ptr;

	va_start(arg_ptr, format);
	n = rt_vsprintf(buf ,format, arg_ptr);
	va_end(arg_ptr);

	return n;
}

#ifdef RT_USING_CONSOLE

#ifdef RT_USING_DEVICE
/**
 * This function returns the device using in console.
 *
 * @return the device using in console or RT_NULL
 */
rt_device_t rt_console_get_device(void)
{
	return _console_device;
}

/**
 * This function will set a device as console device.
 * After set a device to console, all output of rt_kprintf will be
 * redirected to this new device.
 *
 * @param name the name of new console device
 *
 * @return the old console device handler
 */
rt_device_t rt_console_set_device(const char *name)
{
	rt_device_t new, old;

	/* save old device */
	old = _console_device;

	/* find new console device */
	new = rt_device_find(name);
	if (new != RT_NULL)
	{
		if (_console_device != RT_NULL)
		{
			/* close old console device */
			rt_device_close(_console_device);
		}

		/* set new console device */
		_console_device = new;
		rt_device_open(_console_device, RT_DEVICE_OFLAG_RDWR);
	}

	return old;
}
#endif

#if defined(__GNUC__)
void rt_hw_console_output(const char *str) __attribute__((weak));
void rt_hw_console_output(const char *str)
#elif defined(__CC_ARM)
__weak void rt_hw_console_output(const char *str)
#elif defined(__IAR_SYSTEMS_ICC__)
#if __VER__ > 540
__weak
#endif
void rt_hw_console_output(const char *str)
#endif
{
	/* empty console output */
}

/**
 * This function will print a formatted string on system console
 *
 * @param fmt the format
 */
void rt_kprintf(const char *fmt, ...)
{
	va_list args;
	rt_size_t length;
	static char rt_log_buf[RT_CONSOLEBUF_SIZE];

	va_start(args, fmt);
	length = vsnprintf(rt_log_buf, sizeof(rt_log_buf), fmt, args);
#ifdef RT_USING_DEVICE
	if (_console_device == RT_NULL)
	{
		rt_hw_console_output(rt_log_buf);
	}
	else
	{
		rt_device_write(_console_device, 0, rt_log_buf, length);
	}
#else
	rt_hw_console_output(rt_log_buf);
#endif
	va_end(args);
}
#else
void rt_kprintf(const char *fmt, ...)
{
}
#endif

#ifdef RT_USING_HEAP
/**
 * This function allocates a memory block, which address is aligned to the
 * specified alignment size.
 *
 * @param size the allocated memory block size
 * @param align the alignment size
 *
 * @return the allocated memory block on successful, otherwise returns RT_NULL
 */
void* rt_malloc_align(rt_size_t size, rt_size_t align)
{
	void *align_ptr;
	void *ptr;
	rt_size_t align_size;

	/* align the alignment size to 4 byte */
	align = ((align + 0x03) & ~0x03);

	/* get total aligned size */
	align_size = ((size + 0x03) & ~0x03) + align;
	/* allocate memory block from heap */
	ptr = rt_malloc(align_size);
	if (ptr != RT_NULL)
	{
		if (((rt_uint32_t)ptr & (align - 1)) == 0) /* the allocated memory block is aligned */
		{
			align_ptr = (void*) ((rt_uint32_t)ptr + align);
		}
		else
		{
			align_ptr = (void*) (((rt_uint32_t)ptr + (align - 1)) & ~(align - 1));
		}

		/* set the pointer before alignment pointer to the real pointer */
		*((rt_uint32_t*)((rt_uint32_t)align_ptr - sizeof(void*))) = (rt_uint32_t)ptr;

		ptr = align_ptr;
	}

	return ptr;
}

/**
 * This function release the memory block, which is allocated by rt_malloc_align
 * function and address is aligned.
 *
 * @param ptr the memory block pointer
 */
void rt_free_align(void *ptr)
{
	void *real_ptr;

	real_ptr = (void*)*(rt_uint32_t*)((rt_uint32_t)ptr - sizeof(void*));
	rt_free(real_ptr);
}
#endif

#if !defined (RT_USING_NEWLIB) && defined (RT_USING_MINILIBC) && defined (__GNUC__)
#include <sys/types.h>
void *memcpy(void *dest, const void *src, size_t n) __attribute__((weak, alias("rt_memcpy")));
void *memset(void *s, int c, size_t n) __attribute__((weak, alias("rt_memset")));
void *memmove(void *dest, const void *src, size_t n) __attribute__((weak, alias("rt_memmove")));
int   memcmp(const void *s1, const void *s2, size_t n) __attribute__((weak, alias("rt_memcmp")));

size_t strlen(const char *s) __attribute__((weak, alias("rt_strlen")));
char *strstr(const char *s1,const char *s2) __attribute__((weak, alias("rt_strstr")));
int strcasecmp(const char *a, const char *b) __attribute__((weak, alias("rt_strcasecmp")));
char *strncpy(char *dest, const char *src, size_t n) __attribute__((weak, alias("rt_strncpy")));
int strncmp(const char *cs, const char *ct, size_t count) __attribute__((weak, alias("rt_strncmp")));
#ifdef RT_USING_HEAP
char *strdup(const char *s) __attribute__((weak, alias("rt_strdup")));
#endif

int sprintf(char *buf, const char *format, ...) __attribute__((weak, alias("rt_sprintf")));
int snprintf(char *buf, rt_size_t size, const char *fmt, ...) __attribute__((weak, alias("rt_snprintf")));
int vsprintf(char *buf, const char *format, va_list arg_ptr) __attribute__((weak, alias("rt_vsprintf")));

#endif

/*@}*/
