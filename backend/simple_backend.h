// Author: Alexander Thomson (thomson@cs.yale.edu)
//
// Simple backend implementation in which storage is simply an in-memory
// key-value map.

#ifndef _DB_BACKEND_SIMPLE_BACKEND_H_
#define _DB_BACKEND_SIMPLE_BACKEND_H_

#include "backend.h"

#include <map>
using std::map;

class SimpleBackend : public Backend {
 public:
  SimpleBackend() {}
  virtual ~SimpleBackend() {}
  virtual void Prefetch(const vector<Key>& keys) {}  // No prefetching.
  virtual void Execute(TxnProto* txn);

  // Returns object identified by 'key' (for testing purposes).
  Value Lookup(Key key);

 private:
  // Key-value map of objects (where objects are uint64s).
  map<Key, Value> objects_;
};

/////////////////   Implementation details follow   /////////////////

void SimpleBackend::Execute(TxnProto* txn) {
  for (int64 i = 0; i < txn->write_set_size(); i++) {
    if (objects_.count(txn->write_set(i))) {
      int64 prev = UnpackInt64(objects_[txn->write_set(i)]);
      objects_[txn->write_set(i)] = PackInt64(prev + 1);
    } else {
      objects_[txn->write_set(i)] = PackInt64(1);
    }
  }
}

Value SimpleBackend::Lookup(Key key) {
  if (objects_.count(key) > 0) {
    return objects_[key];
  } else {
    return PackInt64(0);
  }
}

#endif  // #define _DB_BACKEND_BACKEND_H_

