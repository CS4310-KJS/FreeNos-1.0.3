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
    parser().setDescription("Changes a process's priority level");
    parser().registerFlag('n', "priorityn", "priority level flag");
    parser().registerPositional("priority", "set priority level");
    parser().registerPositional("pid", "ID of the process to change priority for");
}

Renice::~Renice() {
}

Renice::Result Renice::exec(){

    PriorityLevel priority = atoi(arguments().get("priority"));
    if (priority < 1 || priority > 5){
        ERROR("Invalid priority level");
        return InvalidArgument;
    }

    pid_t pid = atoi(arguments().get("pid"));
    if (pid < 0){
        ERROR("Invalid process id");
        return InvalidArgument;
    }

    if (changePriority(pid, priority, 0) != pid)
    {
        ERROR("Renice failed");
        return IOError;
    }



}
