#ifndef _LOG_H
#define _LOG_H

#ifdef _DEBUG
    #define DEFAULT_LOG_LEVEL
    #define LOG_INFO
    #define LOG_DBG
    #define LOG_WARN
    #define LOG_ERR

    void log_dbg(fmt, ...);
    void log_info(fmt, ...);
    void log_warn(fmt, ...);
    void log_err(fmt, ...);
#endif

#endif
