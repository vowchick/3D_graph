#include "thread_info.h"
void *
pthread_func (void *arg)
{
    thread_info *info = static_cast<thread_info *> (arg);
    FIX_UNUSED (info);

    return 0;
}
