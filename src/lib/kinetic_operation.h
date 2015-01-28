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
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*
*/

#ifndef _KINETIC_OPERATION_H
#define _KINETIC_OPERATION_H

#include "kinetic_types_internal.h"

KineticStatus KineticOperation_SendRequest(KineticOperation* const operation);
KineticStatus KineticOperation_GetStatus(const KineticOperation* const operation);
void KineticOperation_Complete(KineticOperation* operation, KineticStatus status);


/*******************************************************************************
 * Client Operations
*******************************************************************************/

KineticStatus KineticOperation_NoopCallback(KineticOperation* const operation, KineticStatus const status);
void KineticOperation_BuildNoop(KineticOperation* operation);

KineticStatus KineticOperation_PutCallback(KineticOperation* const operation, KineticStatus const status);
void KineticOperation_BuildPut(KineticOperation* const operation,
                               KineticEntry* const entry);

KineticStatus KineticOperation_GetCallback(KineticOperation* const operation, KineticStatus const status);
void KineticOperation_BuildGet(KineticOperation* const operation,
                               KineticEntry* const entry);

void KineticOperation_BuildGetNext(KineticOperation* const operation,
                                   KineticEntry* const entry);
void KineticOperation_BuildGetPrevious(KineticOperation* const operation,
                                       KineticEntry* const entry);

KineticStatus KineticOperation_FlushCallback(KineticOperation* const operation, KineticStatus const status);
void KineticOperation_BuildFlush(KineticOperation* const operation);

KineticStatus KineticOperation_DeleteCallback(KineticOperation* const operation, KineticStatus const status);
void KineticOperation_BuildDelete(KineticOperation* const operation,
                                  KineticEntry* const entry);

KineticStatus KineticOperation_GetKeyRangeCallback(KineticOperation* const operation, KineticStatus const status);
void KineticOperation_BuildGetKeyRange(KineticOperation* const operation,
                               KineticKeyRange* range, ByteBufferArray* buffers);

KineticStatus KineticOperation_P2POperationCallback(KineticOperation* const operation, KineticStatus const status);
KineticStatus KineticOperation_BuildP2POperation(KineticOperation* const operation,
                                                 KineticP2P_Operation* const p2pOp);


/*******************************************************************************
 * Admin Client Operations
*******************************************************************************/

KineticStatus KineticOperation_SetPinCallback(KineticOperation* const operation, KineticStatus const status);
void KineticOperation_BuildSetPin(KineticOperation* const operation, ByteArray old_pin, ByteArray new_pin, bool lock);

KineticStatus KineticOperation_EraseCallback(KineticOperation* const operation, KineticStatus const status);
void KineticOperation_BuildErase(KineticOperation* const operation, bool secure_erase, ByteArray* pin);

KineticStatus KineticOperation_LockUnlockCallback(KineticOperation* const operation, KineticStatus const status);
void KineticOperation_BuildLockUnlock(KineticOperation* const operation, bool lock, ByteArray* pin);

KineticStatus KineticOperation_GetLogCallback(KineticOperation* const operation, KineticStatus const status);
void KineticOperation_BuildGetLog(KineticOperation* const operation,
                               KineticDeviceInfo_Type type,
                               KineticDeviceInfo** info);

KineticStatus KineticOperation_SetAclCallback(KineticOperation* const operation, KineticStatus const status);
void KineticOperation_BuildSetAcl(KineticOperation* const operation,
                               KineticDeviceInfo_Type type,
                               KineticDeviceInfo** info);

KineticStatus KineticOperation_SetClusterVersionCallback(KineticOperation* const operation, KineticStatus const status);
void KineticOperation_BuildSetClusterVersion(KineticOperation* const operation, int64_t newClusterVersion);

#endif // _KINETIC_OPERATION_H
