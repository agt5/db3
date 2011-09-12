// Author: Alexander Thomson (thomson@cs.yale.edu)
//
// Defininitions of some common types and constants used in the system.

#include <stdint.h>
#include <string>

using std::string;

// Abbreviated signed int types.
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

// Abbreviated unsigned int types.
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

// 'bytes' is an arbitrary sequence of bytes, represented as a string.
typedef string bytes;

// Key type for database objects.
// Note: if this changes from bytes, the types need to be updated for the
// following fields in .proto files:
//    proto/txn.proto:
//      TxnProto::'read_set'
//      TxnProto::'write_set'
typedef bytes Key;

// Value type for database objects.
typedef bytes Value;

bytes PackInt8 (int8  unpacked) { return string((const char*)&unpacked, 1); }
bytes PackInt16(int16 unpacked) { return string((const char*)&unpacked, 2); }
bytes PackInt32(int32 unpacked) { return string((const char*)&unpacked, 4); }
bytes PackInt64(int64 unpacked) { return string((const char*)&unpacked, 8); }

int8  UnpackInt8 (bytes packed) { return *((int8 *)(packed.data())); }
int16 UnpackInt16(bytes packed) { return *((int16*)(packed.data())); }
int32 UnpackInt32(bytes packed) { return *((int32*)(packed.data())); }
int64 UnpackInt64(bytes packed) { return *((int64*)(packed.data())); }

bytes PackUInt8 (uint8  unpacked) { return string((const char*)&unpacked, 1); }
bytes PackUInt16(uint16 unpacked) { return string((const char*)&unpacked, 2); }
bytes PackUInt32(uint32 unpacked) { return string((const char*)&unpacked, 4); }
bytes PackUInt64(uint64 unpacked) { return string((const char*)&unpacked, 8); }

uint8  UnpackUInt8 (bytes packed) { return *((uint8 *)(packed.data())); }
uint16 UnpackUInt16(bytes packed) { return *((uint16*)(packed.data())); }
uint32 UnpackUInt32(bytes packed) { return *((uint32*)(packed.data())); }
uint64 UnpackUInt64(bytes packed) { return *((uint64*)(packed.data())); }

bytes ToKey(int8  x) { return PackInt8 (x); }
bytes ToKey(int16 x) { return PackInt16(x); }
bytes ToKey(int32 x) { return PackInt32(x); }
bytes ToKey(int64 x) { return PackInt64(x); }

bytes ToKey(uint8  x) { return PackUInt8 (x); }
bytes ToKey(uint16 x) { return PackUInt16(x); }
bytes ToKey(uint32 x) { return PackUInt32(x); }
bytes ToKey(uint64 x) { return PackUInt64(x); }

