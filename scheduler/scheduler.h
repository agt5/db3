// Author: Alexander Thomson (thomson@cs.yale.edu)
//
// A database node's Scheduler determines what transactions should be run when
// at that node. It owns the node's lock manager and is responsible for
// communicating with other nodes when necessary to determine whether a
// transaction can be scheduled.

#ifndef _DB_SCHEDULER_SCHEDULER_H_
#define _DB_SCHEDULER_SCHEDULER_H_

#include "../configuration.h"
#include "../remote_connection.h"
#include "lock_manager.h"

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

  // The per-node lock manager tracks what transactions have temporary ownership
  // of what database objects, allowing the scheduler to track LOCAL conflicts
  // and enforce equivalence to transaction orders.
  LockManager lock_manager_;

  // Connection for sending and receiving protocol messages.
  RemoteConnection connection_;

  // Queue of transaction ids of transactions that have acquired all locks that
  // they have requested.
  queue<int> ready_txns_;
};

#endif  // #define _DB_SCHEDULER_SCHEDULER_H_

