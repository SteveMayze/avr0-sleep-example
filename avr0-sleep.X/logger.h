/* 
 * File:   logger.h
 * Author: Steven
 *
 * Created on 25 October 2023, 10:04
 */

#ifndef LOGGER_H
#define	LOGGER_H

#ifdef	__cplusplus
extern "C" {
#endif

   
#define LOGGER_LEVEL_OFF 0
#define LOGGER_LEVEL_ERROR 1
#define LOGGER_LEVEL_INFO 2
#define LOGGER_LEVEL_DEBUG 4
#define LOGGER_LEVEL_ALL 7
    
    
#if defined(LOGGER_LEVEL) && LOGGER_LEVEL > LOGGER_LEVEL_OFF
    #define LOG_ERROR(args...) {printf("ERROR: "); printf(args); }
#else
    #define LOG_ERROR(args...)
#endif

#if defined(LOGGER_LEVEL) && LOGGER_LEVEL > LOGGER_LEVEL_ERROR
    #define LOG_INFO(args...) {printf("INFO: "); printf(args); }
#else
    #define LOG_INFO(args...) 
#endif


#if defined(LOGGER_LEVEL) && LOGGER_LEVEL > LOGGER_LEVEL_INFO 
    #define LOG_DEBUG(args...) {printf("DEBUG: "); printf(args); }
#else
    #define LOG_DEBUG(args...) 
#endif

    
#if defined(LOGGER_LEVEL) && LOGGER_LEVEL > LOGGER_LEVEL_ERROR
    #define LOG_BYTE_STREAM(prefix, byte_stream, stream_size) { \
        LOG_INFO(prefix);                                      \
        for(int idx = 0; idx<stream_size; idx++) {              \
            printf("%02X ", byte_stream[idx]);               \
        }                                                       \
        printf("\n");                                        \
    } 
    #else
        #define LOG_BYTE_STREAM(prefix, byte_stream, stream_size)
    #endif
    

#ifdef	__cplusplus
}
#endif

#endif	/* LOGGER_H */

