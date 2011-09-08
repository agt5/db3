// Author: Alexander Thomson (thomson@cs.yale.edu)
//
// SerialScheduler is a trivial scheduler that executes transactions serially
// as they come in, without locking.

#ifndef _DB_SCHEDULER_SCHEDULER_H_
#define _DB_SCHEDULER_SCHEDULER_H_

#include "scheduler.h"

class SerialScheduler : public Scheduler {
 public:
  // Given a Configuration (of which the Scheduler takes ownership), a
  // LockManager of the appropriate type is created and a RemoteConnection is
  // set up accordingly.
  explicit SerialScheduler(Configuration* conf) : configuration_(conf) {}
  virtual ~SerialScheduler() {}

  // Scheduler::Run() is essentially the database node's main() function. All
  // further input to the Scheduler (e.g. new transaction requests) is sent via
  // protocol messages over the RemoteConnection.
  virtual void Run();
};

#endif  // #define _DB_SCHEDULER_SCHEDULER_H_

