#include <FreeNOS/User.h>
#include <ProcessClient.h>
#include "unistd.h"
#include "errno.h"

pid_t setprio(pid_t pid, unsigned int priority, int options)
{
    const ProcessClient process;
    ProcessClient::Info info;
    
    if (process.processInfo(pid, info) != ProcessClient::Success)
    {
        errno = ESRCH;
        return (pid_t) -1;
    }

    info.kernelState.priority = priority;

    const ulong result = (ulong) ProcessCtl(pid, SetPrioPID, (Address) &info.kernelState);

    switch ((const API::Result) (result & 0xffff))
    {
        case API::NotFound:
            errno = ESRCH;
            return (pid_t) -1;

        case API::Success:
            return pid;

        default:
            errno = EIO;
            return (pid_t) -1;
    }
}
