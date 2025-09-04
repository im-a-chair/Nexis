#include "Log.h"
#include "std.h"

///TODO: make threadsafe (e.g. with thread local storage)
struct {
    //bool usefile; //just check if `logfile` is `NULL` or not
    FILE* logfile;
    char* info, warning, error; //stores only the most recent one of each
    NXS_ErrorCallback errcb;
    void* errcb_udata;
} _NXS_LogCTX = {NULL, NULL, NULL, NULL, NULL, NULL};

void NXS_LogSetErrorCallback(NXS_ErrorCallback errcb, void* udata) {
    _NXS_LogCTX.errcb = errcb; //if `NULL`, still fine
    _NXS_LogCTX.errcb_udata = udata;
}
void NXS_LogSetOutFile(FILE* file) {
    _NXS_LogCTX.logfile = file;
}
const char* NXS_Log(const char* msg) {
    if (!msg) {
        return _NXS_LogCTX.info;
    }
    _NXS_LogCTX.info = msg;
    if (_NXS_LogCTX.logfile) {
        fprintf(_NXS_LogCTX.logfile, "%s: INFO: %s\n", __TIME__, msg);
    }
    return NULL;
}
const char* NXS_Warning(const char* msg) {
    if (!msg) {
        return _NXS_LogCTX.warning;
    }
    _NXS_LogCTX.warning = msg;
    if (_NXS_LogCTX.logfile) {
        fprintf(_NXS_LogCTX.logfile, "%s: WARNING: %s\n", __TIME__, msg);
    }
    return NULL;
}
const char* NXS_Error(const char* msg) {
    if (!msg) {
        return _NXS_LogCTX.error;
    }
    _NXS_LogCTX.error = msg;
    if (_NXS_LogCTX.errcb) {
        _NXS_LogCTX.errcb(_NXS_LogCTX.errcb_udata);
    }
    if (_NXS_LogCTX.logfile) {
        fprintf(_NXS_LogCTX.logfile, "%s: ERROR: %s\n", __TIME__, msg);
    }
    return NULL;
}
inline bool NXS_HasError() {
    return (_NXS_LogCTX.error != NULL);
}