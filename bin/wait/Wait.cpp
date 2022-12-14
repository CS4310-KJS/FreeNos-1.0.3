#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "Wait.h"
#include <ProcessClient.h>


Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Wait");
    parser().registerPositional("PID", "PID is argument");
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{
    int pid = 0;
    int status;
    const ProcessClient process;

    if (((pid = atoi(arguments().get("PID"))) < 0)||(pid > ProcessClient::MaximumProcesses))
    {
        ERROR("PID not found '" << arguments().get("PID") << "'");
        return NotFound;
    }

    waitpid(pid, &status, 0);

    return Success;
}