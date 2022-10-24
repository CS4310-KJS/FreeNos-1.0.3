#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ProcessClient.h>
#include <unistd.h>
#include <Process.h>
#include "renice.h"

int prio;
ProcessID pid;

renice::renice(int argc, char **argv) : POSIXApplication(argc, argv){
    parser().setDescription("Change the priority of a process");
    parser().registerFlag('n', "setPriority", "Changes process priority to new priority");
    parser().registerPositional("PRI", "Priority to change the process to");
    parser().registerPositional("PID", "PID of the process to change");
    prio = atoi(argv[2]);
    pid = atoi(argv[3]);
}

renice::~renice(){

}

renice::Result renice::exec(){
    ProcessClient process;
    if (pid <=  0 || pid >= ProcessClient::MaximumProcesses)
    {
        ERROR("Invalid PID: " << pid);
        return InvalidArgument;
    } else if (prio <= 0 || prio > 5){
        ERROR("Invalid priority: " << prio);
        return InvalidArgument;
    } else {
        process.setPriority(pid, prio);
        //out << "Priority Changed!!!!!!!!!!\r\n";
    }

    return Success;
}
