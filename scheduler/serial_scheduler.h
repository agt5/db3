// Author: Alexander Thomson (thomson@cs.yale.edu)
//
// SerialScheduler is a trivial scheduler that executes transactions serially
// as they come in, without locking.

#ifndef _DB_SCHEDULER_SCHEDULER_H_
#define _DB_SCHEDULER_SCHEDULER_H_

#include "scheduler.h"

class SerialScheduler : public Scheduler {
 public:
  explicit SerialScheduler(Configuration* conf);
  virtual ~SerialScheduler();
  virtual void Run();
};

/////////////////   Implementation details follow   /////////////////

SerialScheduler::SerialScheduler(Configuration* conf)
  : configuration_(conf), connection_(new Connection(configuration_)),
    backend_(new SimpleBackend()) {
}

SerialScheduler::~SerialScheduler() {
  delete configuration_;
  delete connection_;
  delete backend_;
}

void SerialScheduler::Run() {
  TxnProto* txn;
  while (true) {
    if ((txn = connection_->GetNewTxn()) != NULL)
      backend_->Execute(txn);
  }
}

#endif  // #define _DB_SCHEDULER_SCHEDULER_H_

