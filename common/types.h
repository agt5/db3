// Author: Alexander Thomson (thomson@cs.yale.edu)
//
// Defininitions of some common types and constants used in the system.

// Borrowing common.h from the protobuf lib to declare types like 'int32',
// 'uint64', 'bytes', etc.
#include <google/protobuf/stubs/common.h>

// Key type for database objects.
// Note: if this changes from uint64, the types need to be updated for the
// following fields in .proto files:
//    proto/txn.proto:
//      TxnProto::'read_set'
//      TxnProto::'write_set'
typedef Key uint64;

