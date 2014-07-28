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

#ifndef _KINETIC_EXCHANGE_H
#define _KINETIC_EXCHANGE_H

#include "kinetic_types.h"
#include "kinetic_proto.h"
#include "kinetic_connection.h"

typedef struct _KineticExchange
{
    // Defaults to false, since clusterVersion is optional
    // Set to true to enable clusterVersion for the exchange
    bool has_clusterVersion;

    // Optional field - default value is 0
    // The version number of this cluster definition. If this is not equal to
    // the value on the device, the request is rejected and will return a
    // `VERSION_FAILURE` `statusCode` in the `Status` message.
    int64_t clusterVersion;

    // Required field
    // The identity associated with this request. See the ACL discussion above.
    // The Kinetic Device will use this identity value to lookup the
    // HMAC key (shared secret) to verify the HMAC.
    int64_t identity;

    // Required field
    // This is the identity's HMAC Key. This is a shared secret between the
    // client and the device, used to sign requests.
    bool has_key;
    size_t keyLength;
    uint8_t key[KINETIC_MAX_KEY_LEN];

    // Required field
    // A unique number for this connection between the source and target.
    // On the first request to the drive, this should be the time of day in
    // seconds since 1970. The drive can change this number and the client must
    // continue to use the new number and the number must remain constant
    // during the session
    int64_t connectionID;

    // Required field
    // A monotonically increasing number for each request in a TCP connection.
    int64_t sequence;

    // Associated Kinetic connection
    KineticConnection* connection;
} KineticExchange;

#define KINETIC_EXCHANGE_INIT(exchg, id, k, klen, con) { \
    memset((exchg), 0, sizeof(KineticExchange)); \
    (exchg)->identity = id; \
    if (k != NULL && klen > 0) \
    { \
        memcpy((exchg)->key, k, klen); \
        (exchg)->keyLength = klen; \
        (exchg)->has_key = true; \
    } \
    (exchg)->connection = con; \
    (exchg)->sequence = -1; \
}

void KineticExchange_Init(
    KineticExchange* const exchange,
    int64_t identity,
    uint8_t* key,
    size_t keyLength,
    KineticConnection* const connection);

void KineticExchange_ConfigureConnectionID(
    KineticExchange* const exchange);

void KineticExchange_SetClusterVersion(
    KineticExchange* const exchange,
    int64_t clusterVersion);

void KineticExchange_IncrementSequence(
    KineticExchange* const exchange);

void KineticExchange_ConfigureHeader(
    const KineticExchange* const exchange,
    KineticProto_Header* const header);

#endif // _KINETIC_EXCHANGE_H
