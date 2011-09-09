// Author: Alexander Thomson (thomson@cs.yale.edu)
//
// Simple backend implementation in which storage is simply an in-memory
// key-value map.

#ifndef _DB_BACKEND_SIMPLE_BACKEND_H_
#define _DB_BACKEND_SIMPLE_BACKEND_H_

#include "backend.h"

class SimpleBackend : public Backend {
 public:
  virtual ~SimpleBackend() {}
  virtual void Prefetch(vector<Key> keys) {}  // No prefetching.
  virtual void Execute(const TxnProto& txn);

 private:
  map<Key, Value> objects_;
};

/////////////////   Implementation details follow   /////////////////

void SimpleBackend::Execute(const TransactionProto& txn) {
  // TODO(alex): Implement this.
}

#endif  // #define _DB_BACKEND_BACKEND_H_

