#ifndef _NXS_LOG_H_
#define _NXS_LOG_H_
#include "std.h"

#ifndef _NXS_INIT_LOG_STR_CAP
#define _NXS_INIT_LOG_STR_CAP 10
#endif

/// TODO: for in Display lib: popup callback window(s) for warnings and errors

/** NXS_ErrorCallback
 * function signature for registering an error callback
 */
typedef void (*NXS_ErrorCallback)(void* data);

/** NXS_LogSetErrorCallback
 * is for assigning or changing the assigned error callback
 * the error callback is a function (that should athere to
 * the function signature provided by `NXS_ErrorCallback`)
 * thats called whenever an error message is logged with `NXS_Error`
 * 
 * \param errcb the function to use as callback
 * \param udata a void pointer to pass to the callback when called
 * \note neither `errcb` nor `udata` will not be checked internally
 * at all, so managing it is you responsibility
 */
void NXS_LogSetErrorCallback(NXS_ErrorCallback errcb, void* udata);

/** NXS_LogSetOutFile
 * is for setting the (`FILE*`) filestream
 * to print the log messages to,
 * can be `NULL` to not use
 * 
 * \param file the `FILE*` filestream to use
 * \note `file` will not be checked internally
 * at all, so managing it is you responsibility
 */
void NXS_LogSetOutFile(FILE* file);

/** NXS_Log
 * is for sumbitting a info log message,
 * or checking the last submitted one,
 * for submitting or checking error
 * or warning messages, use `NXS_Error`
 * or `NXS_Warning` respectively
 * 
 * if the context's log file is not `NULL`,
 * the message will also be printed to the provided filestream.
 * 
 * \returns if `msg` is `NULL`, this function will return the last submitted log,
 * otherwise it will submit the message and return `NULL`
 * \param msg the log string to log, or `NULL` to return the last one
 */
const char* NXS_Log(const char* msg);

/** NXS_Warning
 * is for sumbitting a warning message,
 * or checking the last submitted one,
 * for submitting or checking error
 * or info messages, use `NXS_Error`
 * or `NXS_Log` respectively
 * 
 * if the context's log file is not `NULL`,
 * the message will also be printed to the provided filestream.
 * 
 * \returns if `msg` is `NULL`, this function will return the last submitted warning,
 * otherwise it will submit the message and return `NULL`
 * \param msg the warning string to log, or `NULL` to return the last one
 */
const char* NXS_Warning(const char* msg);

/** NXS_Error
 * is for sumbitting a error message,
 * or checking the last submitted one,
 * for submitting or checking warning
 * or info messages, use `NXS_Warning`
 * or `NXS_Log` respectively
 * 
 * if the context's log file is not `NULL`,
 * the message will also be printed to the provided filestream.
 * 
 * if the context's error callback is not `NULL`,
 * the callback will be called and provided
 * the submitted `udata`
 * 
 * \returns if `msg` is `NULL`, this function will return the last submitted error,
 * otherwise it will submit the message and return `NULL`
 * \param msg the error string to log, or `NULL` to return the last one
 */
const char* NXS_Error(const char* msg);

/** NXS_Error
 * is for checking if an error has been submitted
 * 
 * \returns true if the context's error buffer is occupied, false if not
 */
inline bool NXS_HasError();

#endif //_NXS_LOG_H_