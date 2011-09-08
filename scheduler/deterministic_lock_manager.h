// Author: Alexander Thomson (thomson@cs.yale.edu)
//
// The deterministic lock manager implements deterministic locking as described
// in 'The Case for Determinism in Database Systems', VLDB 2010. Each
// transaction must request all locks it will ever need before the next
// transaction in the specified order may acquire any locks. Each lock is then
// granted to transactions in the order in which they requested them (i.e. in
// the global transaction order).

#ifndef _DB_SCHEDULER_DETERMINISTIC_LOCK_MANAGER_H_
#define _DB_SCHEDULER_DETERMINISTIC_LOCK_MANAGER_H_

#include "lock_manager.h"

class DeterministicLockManager : public LockManager {
 public:
  explicit DeterministicLockManager(queue<int>* ready_txns);
  virtual ~LockManager() {}
  virtual int Lock(vector<Key> keys, int transaction_id);
  virtual void Release(vector<Key> keys, int transaction_id);
  virtual bool Locked(Key key, int* owner);

 private:
  // The DeterministicLockManager's lock table tracks all lock requests. For a
  // given key, if 'lock_table_' contains a nonempty queue, then the item with
  // that key is locked and the first element in the queue specifies the owner.
  // Subsequent elements in the queue are waiting to acquire the lock.
  map<Key, queue<int> > lock_table_;
};

#endif  // #define _DB_SCHEDULER_DETERMINISTIC_LOCK_MANAGER_H_

