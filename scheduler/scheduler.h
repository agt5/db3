// Author: Alexander Thomson (thomson@cs.yale.edu)
//
// A database node's Scheduler determines what transactions should be run when
// at that node. It owns the node's lock manager and is responsible for
// communicating with other nodes when necessary to determine whether a
// transaction can be scheduled.

#ifndef _DB_SCHEDULER_SCHEDULER_H_
#define _DB_SCHEDULER_SCHEDULER_H_

#include <vector>

#include "../types.h"
#include "../configuration.h"
#include "../connection.h"

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
};

class Scheduler {
 public:
  // Given a Configuration (of which the Scheduler takes ownership), a
  // LockManager of the appropriate type is created and a RemoteConnection is
  // set up accordingly.
  explicit Scheduler(Configuration* conf) : configuration_(conf) {}
  virtual ~Scheduler() = 0;

  // Scheduler::Run() is essentially the database node's main() function. All
  // further input to the Scheduler (e.g. new transaction requests) is sent via
  // protocol messages over the RemoteConnection.
  virtual void Run() = 0;

 protected:
  // This node's Configuration specifies:
  //    - this node's identity
  //    - this node's execution mode (deterministic vs nondeterministic)
  //    - all other active nodes in the system & their addresses
  Configuration* configuration_;

  // Connection for sending and receiving protocol messages.
  Connection* connection_;

  // Database backend responsible for managing storage and executing transaction
  // logic.
  Backend* backend_;
};

#endif  // #define _DB_SCHEDULER_SCHEDULER_H_

