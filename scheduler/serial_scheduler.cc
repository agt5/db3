// Author: Alexander Thomson (thomson@cs.yale.edu)

#include "serial_scheduler.h"

void SerialScheduler::Run() {
  while (true) {
    ProtocolMessage m;
    if (connection_->GetNewTxn(&m)) {
      // Execute new txn.
      backend_->
    }
}
