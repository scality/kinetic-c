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

#ifndef _KINETIC_ADMIN_CLIENT_H
#define _KINETIC_ADMIN_CLIENT_H

#include "kinetic_types.h"
#include "kinetic_client.h"

/**
 * Initializes the Kinetic Admin API and configures logging.
 *
 * @param log_file (path to log file, 'stdout' to log to STDOUT, NULL to disable logging)
 * @param log_level Logging level (-1:none, 0:error, 1:info, 2:verbose, 3:full)
 *
 * @return          Returns a pointer to a `KineticClient`. You need to pass 
 *                  this pointer to KineticClient_CreateSession() to create 
 *                  new connections. 
 *                  Once you are finished will the `KineticClient`, and there
 *                  are no active connections. The pointer should be release
 *                  with KineticClient_Shutdown()
 */
KineticClient * KineticAdminClient_Init(const char* log_file, int log_level);

/**
 * @brief Performs shutdown/cleanup of the kinetic-c client library
 */
void KineticAdminClient_Shutdown(KineticClient * const client);

/**
 * @brief Creates a session with the Kinetic Device per specified configuration.
 *
 * @param config   `KineticSessionConfig` structure which must be configured
 *                 by the client prior to creating the device connection.
 *   .host             Host name or IP address to connect to
 *   .port             Port to establish socket connection on
 *   .clusterVersion   Cluster version to use for the session
 *   .identity         Identity to use for the session
 *   .hmacKey          Key to use for HMAC calculations (NULL-terminated string)
 *   .pin              PIN to use for PIN-based operations
 * @param client    The `KineticClient` pointer returned from KineticClient_Init()
 * @param session   Pointer to a KineticSession pointer that will be populated
 *                  with the allocated/created session upon success.
 *
 * @return          Returns the resulting `KineticStatus`, and `session`
 *                  will be populated with a pointer to the session instance
 *                  upon success. The client should call
 *                  KineticClient_DestroySession() in order to shutdown a
 *                  connection and cleanup resources when done using a
 *                  `KineticSession`.
 */
KineticStatus KineticAdminClient_CreateSession(KineticSessionConfig * const config,
    KineticClient * const client, KineticSession** session);

/**
 * @brief Closes the connection to a host.
 *
 * @param session   The connected `KineticSession` to close. The session
 *                  instance will be freed by this call after closing the
 *                  connection, so the pointer should not longer be used.
 *
 * @return          Returns the resulting KineticStatus.
 */
KineticStatus KineticAdminClient_DestroySession(KineticSession * const session);

/**
 * @brief Sets the erase PIN of the Kinetic Device.
 *
 * @param session   The connected `KineticSession` to close. The session
 *                  instance will be freed by this call after closing the
 *                  connection, so the pointer should not longer be used.
 * @param old_pin   Old erase PIN to change.
 * @param new_pin   New erase PIN to change to.
 *
 * @return          Returns the resulting KineticStatus.
 */
KineticStatus KineticAdminClient_SetErasePin(KineticSession const * const session,
    ByteArray old_pin, ByteArray new_pin);

/**
 * @brief Executes a SecureErase command to erase all data from the Kinetic device.
 *
 * @param session   The connected KineticSession to use for the operation.
 * @param pin       PIN to send with operation, which must match the configured erase PIN.
 *
 * @return          Returns the resulting KineticStatus.
 */
KineticStatus KineticAdminClient_SecureErase(KineticSession const * const session,
    ByteArray pin);

/**
 * @brief Executes an InstantErase command to erase all data from the Kinetic device.
 *
 * @param session   The connected KineticSession to use for the operation.
 * @param pin       PIN to send with operation, which must match the configured erase PIN.
 *
 * @return          Returns the resulting KineticStatus.
 */
KineticStatus KineticAdminClient_InstantErase(KineticSession const * const session,
    ByteArray pin);

/**
 * @brief Sets the lock PIN of the Kinetic Device.
 *
 * @param session   The connected `KineticSession` to close. The session
 *                  instance will be freed by this call after closing the
 *                  connection, so the pointer should not longer be used.
 * @param old_pin   Old erase PIN to change.
 * @param new_pin   New erase PIN to change to.
 *
 * @return          Returns the resulting KineticStatus.
 */
KineticStatus KineticAdminClient_SetLockPin(KineticSession const * const session,
    ByteArray old_pin, ByteArray new_pin);

/**
 * @brief Executes a LOCK command to lock the Kinetic device.
 *
 * @param session   The connected KineticSession to use for the operation.
 * @param pin       PIN to send with operation, which must match the configured lock PIN.
 *
 * @return          Returns the resulting KineticStatus.
 */
KineticStatus KineticAdminClient_LockDevice(KineticSession const * const session,
    ByteArray pin);

/**
 * @brief Executes an UNLOCK command to unlock the Kinetic device.
 *
 * @param session   The connected KineticSession to use for the operation.
 * @param pin       PIN to send with operation, which must match the configured lock PIN.
 *
 * @return          Returns the resulting KineticStatus.
 */
KineticStatus KineticAdminClient_UnlockDevice(KineticSession const * const session,
    ByteArray pin);

/**
 * @brief Executes a GETLOG command to retrieve specific configuration and/or
 * operational data from the Kinetic Device.
 *
 * @param session   The connected KineticSession to use for the operation
 * @param type      KineticLogDataType specifying data type to retrieve.
 * @param info      KineticDeviceInfo pointer, which will be assigned to
 *                  a dynamically allocated structure populated with
 *                  the requested data, if successful. The client should
 *                  call free() on this pointer in order to free the root
 *                  and any nested structures.
 * @param closure   Optional closure. If specified, operation will be
 *                  executed in asynchronous mode, and closure callback
 *                  will be called upon completion in another thread.
 *
 * @return          Returns 0 upon success, -1 or the Kinetic status code
 *                  upon failure
 */
KineticStatus KineticAdminClient_GetLog(KineticSession const * const session,
                                   KineticDeviceInfo_Type type,
                                   KineticDeviceInfo** info,
                                   KineticCompletionClosure* closure);

/**
 * @brief Executes a SECURITY command to define/set the access control list
 * (ACL) for the Kinetic device.
 *
 * @param session   The connected KineticSession to use for the operation.
 * @param acl_path  Path to ACL definitions per identity in JSON format.
 *
 * @return          Returns the resulting KineticStatus.
 */
KineticStatus KineticAdminClient_SetAcl(KineticSession const * const session,
    char const * const acl_path);

/**
 * @brief Updates the cluster version of the Kinetic Device.
 *
 * @param version   New cluster version.
 *
 * @return          Returns the resulting KineticStatus.
 */
KineticStatus KineticAdminClient_SetClusterVersion(KineticSession const * const session,
    int64_t version);

/**
 * @brief Executes a Firmware Download command to update the firmware on the Kinetic device.
 *
 * @param session       The connected KineticSession to use for the operation.
 * @param fw_path       Path to firmware update image file.
 *
 * @return              Returns the resulting KineticStatus.
 */
KineticStatus KineticAdminClient_UpdateFirmware(KineticSession const * const session,
    char const * const fw_path);

#endif // _KINETIC_ADMIN_CLIENT_H