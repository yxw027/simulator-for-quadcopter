#ifndef _INITCALL_H
#define _INITCALL_H

typedef void (*initcall_t)(void);

#ifdef __CC_ARM
  #define __define_initcall(level,fn,id) \
  static initcall_t __initcall_##fn##id SECTION("initcall") = fn
#elif defined (__GNUC__)
  #define __define_initcall(level,fn,id) \
    static initcall_t __initcall_##fn##id __used \
    __attribute__((__section__(".initcall" level ".init"))) = fn
#endif

#define MODULE_INITCALL(fn)     __define_initcall(0,fn,0)
#define THREAD_INITCALL(fn)     __define_initcall(1,fn,1)

#endif /* _INITCALL_H */
