// Author: Alexander Thomson (thomson@cs.yale.edu)
//
// The database backend manages all storage and execution of all transaction
// logic for the system.

#ifndef _DB_BACKEND_BACKEND_H_
#define _DB_BACKEND_BACKEND_H_

#include <vector>

#include "../types.h"
#include "../proto/transaction.pb.h"

class Backend {
 public:
  virtual ~Backend() {}
  virtual void Prefetch(vector<Key> keys) = 0;
  virtual void Execute(const TransactionProto& txn) = 0;
};

#endif  // #define _DB_BACKEND_BACKEND_H_

