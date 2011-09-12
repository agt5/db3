// Author: Alexander Thomson (thomson@cs.yale.edu)
//
// The database backend manages all storage and execution of all transaction
// logic for the system.

#ifndef _DB_BACKEND_BACKEND_H_
#define _DB_BACKEND_BACKEND_H_

#include <vector>

#include "../common/types.h"
#include "../proto/txn.pb.h"

using std::vector;

class Backend {
 public:
  Backend() {}
  virtual ~Backend() {}

  // Loads objects specified by 'keys' into memory if they were on disk.
  virtual void Prefetch(const vector<Key>& keys) = 0;

  // Executes 'txn'.
  virtual void Execute(TxnProto* txn) = 0;
};

#endif  // #define _DB_BACKEND_BACKEND_H_

