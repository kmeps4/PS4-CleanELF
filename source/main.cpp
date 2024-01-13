#include <stdint.h>
#include <stdarg.h>

#include "../include/types.h"
#include "../include/imports.h"
#include "../include/syscall.h"
#include "../include/detour.h"

typedef struct payload_args {
    int (*sceKernelDlsym)(int, const char*, void*);
    int  *rwpipe;
    int  *rwpair;
    long  kpipe_addr;
    long  kdata_base_addr;
    int  *payloadout;
} payload_args_t;

typedef struct notify_request {
    char useless1[45];
    char message[3075];
} notify_request_t;

typedef int dlsym_t(int, const char*, void*);

extern "C" void _main(payload_args_t* args) {
    notify_request_t req;

    int (*sceKernelDlsym)(int, const char*, void*) = (dlsym_t*)args->sceKernelDlsym;
    int (*sceKernelSendNotificationRequest)(int, notify_request_t*, long, int);
    int (*bzero)(void*, unsigned long);
    int (*sprintf)(char *, const char*, ...);
    int (*getpid)(void);

    sceKernelDlsym(0x2, "bzero", &bzero);
    sceKernelDlsym(0x2, "sprintf", &sprintf);
    sceKernelDlsym(0x2001, "getpid", &getpid);
    sceKernelDlsym(0x2001, "sceKernelSendNotificationRequest", &sceKernelSendNotificationRequest);

    initSyscall((uint64_t)getpid);

    bzero(&req, sizeof req);
    sprintf(req.message, "Hello from pid %d", getpid());

    sceKernelSendNotificationRequest(0, &req, sizeof req, 0);
}
