/*
* kinetic-c
* Copyright (C) 2014 Seagate Technology.
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*
*/

#include "kinetic_message.h"

void KineticMessage_Init(
    KineticMessage* const message,
    KineticExchange* const exchange)
{
    // Initialize protobuf fields
    KineticProto_init(&message->proto);
    KineticProto_command_init(&message->command);
    KineticProto_header_init(&message->header);
    KineticProto_body_init(&message->body);
    KineticProto_status_init(&message->status);

    // Assemble the message
    message->command.header = &message->header;
    message->command.body = &message->body;
    message->command.status = &message->status;
    message->proto.command = &message->command;

    // Configure/associate the message with the exchange
    KineticExchange_ConfigureHeader(exchange, &message->header);
    message->exchange = exchange;
}

void KineticMessage_BuildNoop(KineticMessage* const message)
{
}