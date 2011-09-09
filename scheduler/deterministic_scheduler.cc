// Author: Alexander Thomson (thomson@cs.yale.edu)

DeterministicScheduler::DeterministicScheduler(Configuration* conf)
    : configuration_(conf) {
  // Set up connection.
  lock_manager_ = new DeterministicLockManager(&ready_txns_);  
}

DeterministicScheduler::~DeterministicScheduler();

void DeterministicScheduler::Run() {
}
