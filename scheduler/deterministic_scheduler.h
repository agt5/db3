// Author: Alexander Thomson (thomson@cs.yale.edu)
//
// The deterministic lock manager implements deterministic locking as described
// in 'The Case for Determinism in Database Systems', VLDB 2010. Each
// transaction must request all locks it will ever need before the next
// transaction in the specified order may acquire any locks. Each lock is then
// granted to transactions in the order in which they requested them (i.e. in
// the global transaction order).

#ifndef _DB_SCHEDULER_DETERMINISTIC_SCHEDULER_H_
#define _DB_SCHEDULER_DETERMINISTIC_SCHEDULER_H_

#include "scheduler.h"

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

  // Queue of transaction ids of transactions that have acquired all locks that
  // they have requested. Owned by the DeterministicScheduler.
  queue<int>* ready_txns_;
};

class DeterministicScheduler : public Scheduler {
 public:
  explicit DeterministicScheduler(Configuration* conf);
  virtual ~DeterministicScheduler();
  virtual void Run();

 private:
  // The per-node lock manager tracks what transactions have temporary ownership
  // of what database objects, allowing the scheduler to track LOCAL conflicts
  // and enforce equivalence to transaction orders.
  LockManager lock_manager_;

  // Queue of transaction ids of transactions that have acquired all locks that
  // they have requested.
  queue<int> ready_txns_;
};

#endif  // #define _DB_SCHEDULER_DETERMINISTIC_LOCK_MANAGER_H_

