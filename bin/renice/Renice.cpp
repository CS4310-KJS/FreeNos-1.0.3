/*
 * Copyright (C) 2009 Niek Linnenbank
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <FreeNOS/User.h>
#include "Renice.h"

Renice::Renice(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Change the priority level of a process");
    parser().registerFlag('n', "prio", "optional flag for setting priority");
    parser().registerPositional("priority", "new priority level for the process (1-5)");
    parser().registerPositional("process_id", "ID of the process to change priority for");
}

Renice::~Renice() {
}

Renice::Result Renice::exec(){

    unsigned int priority = atoi(arguments().get("priority"));

    if (priority < 1 || priority > 5){
        ERROR("invalid priority level `" << priority << "'");
        return InvalidArgument;
    }

    pid_t pid = atoi(arguments().get("process_id"));

    if (pid < 0){
        ERROR("invalid process id");
        return InvalidArgument;
    }

    if (setprio(pid, priority, 0) != pid)
    {
        ERROR("renice failed: " << strerror(errno));
        return IOError;
    }
}
