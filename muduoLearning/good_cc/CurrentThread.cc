// need test if it's ok
#include "CurrentThread.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>	// gettid
#include <sys/syscall.h>

pid_t gettid() {
    return static_cast<pid_t>(::syscall(SYS_gettid));
}

namespace CurrentThread {
__thread int t_cachedTid = 0;
__thread char t_tidString[32];
__thread int t_tidStringLength = 6;
__thread const char* t_threadName = "default";
}

void CurrentThread::cacheTid() {
  if (t_cachedTid == 0) {
    t_cachedTid = gettid();
    t_tidStringLength =
        snprintf(t_tidString, sizeof t_tidString, "%5d ", t_cachedTid);
  }
}
