#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "Wait.h"

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Waits for background process to finish and return");
    parser().registerPositional("PID", "Wait for this Process ID");
}
 
Wait::~Wait()
{
}

Wait::Result Wait::exec()
{
    int status;

    pid_t pid = arguments().get("PID");
    if(pid != -1){
        waitpid(pid, &status, 0);
    }
    else{
        ERROR("PID not found, cannot wait");
        return NotFound;
    }
    return Success;
}
