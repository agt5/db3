// Author: Alexander Thomson (thomson@cs.yale.edu)
//
// This system supports deterministic and nondeterministic lock managers, whose
// common interface is here defined. Lock managers are owned and accessed by
// database nodes' Schedulers.

#ifndef _DB_SCHEDULER_LOCK_MANAGER_H_
#define _DB_SCHEDULER_LOCK_MANAGER_H_

#include <vector>
#include <queue>

#include "../types.h"

class LockManager {
 public:
  virtual ~LockManager() {}
  // Attempts to assign the lock for each key in keys to the specified
  // transaction. Returns the number of requested locks NOT assigned to the
  // transaction (therefore Lock() returns 0 if the transaction successfully
  // acquires all locks).
  //
  // Requires: 'keys' contains no duplicate keys.
  // Requires: Lock has not previously been called with this transaction_id
  //           and a set of keys that shares common elements with 'keys'.
  virtual int Lock(vector<Key> keys, int transaction_id) = 0;

  // For each key in keys:
  //   - If the specified transaction owns the lock on the item, the lock is
  //     released.
  //   - If the transaction is in the queue to acquire a lock on the item, the
  //     request is cancelled and the transaction is removed from the item's
  //     queue.
  virtual void Release(vector<Key> keys, int transaction_id) = 0;

  // If the object specified by 'key' is locked, Locked sets '*owner' to the
  // transaction ID of the owner and returns true, otherwise returns false.
  virtual bool Locked(Key key, int* owner) = 0;

 private:
  // Queue of transaction ids of transactions that have acquired all locks that
  // they have requested. Not owned by the LockManager.
  queue<int>* ready_txns_;
};

#endif  // #define _DB_SCHEDULER_LOCK_MANAGER_H_

