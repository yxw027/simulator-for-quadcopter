#include "initcall.h"

void do_initcalls(void)
{
    initcall_t *call;
#ifdef __CC_ARM
    extern const int initcall$$Base;
    extern const int initcall$$Limit;
    for (call = initcall_begin; call < initcall_end; call++) {
        if (call)
            call();
    }
#elif defined (__ICCARM__)
    __section_begin("initcall")
    __section_end("initcall")
#elif defined (__GNUC__)
	extern const int __initcall_start;
	extern const int __initcall_end;
#endif
}
