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

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <ProcessClient.h>
#include "Renice.h"

Renice::Renice(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Change the priority level of a process.");
    parser().registerFlag('n', "change-priority", "Specifies the new priority of the process");
    parser().registerPositional("PRIORITY", "New priority of the process");
    parser().registerPositional("PROCESS-ID", "Process ID of the process to change priority of");
}

Renice::~Renice()
{
}

Renice::Result Renice::exec()
{
    PriorityLevel pl = atoi(arguments().get("PRIORITY"));
    ProcessID process_id = atoi(arguments().get("PROCESS-ID"));
    const ProcessClient p_client;
    if(pl > 5) {
    	ERROR("Invalid Priority Level `" << pl << "'");
    	return InvalidArgument;
    }
    const ProcessClient::Result success = p_client.renicePID(process_id, pl);
    if(success != ProcessClient::Success) {
    	ERROR("Could not set priority `" << pl << "' for PID `" << process_id << "'");
    	return NotFound;
    } 
   
    return Success;
}

