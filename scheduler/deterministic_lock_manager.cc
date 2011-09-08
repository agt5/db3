// Author: Alexander Thomson (thomson@cs.yale.edu)

#include "lock_manager.h"

DeterministicLockManager::DeterministicLockManager(queue<int>* ready_txns)
    : ready_txns_(ready_txns) {
}

int DeterministicLockManager::Lock(vector<Key> keys, int transaction_id) {
  int not_acquired = 0;
  for (int i = 0; i < keys.size(); i++) {
    lock_table_[keys[i]].push_back(transaction_id);
    if (lock_table_[keys[i]].front() != transaction_id)
      not_acquired++;
  }
  return not_acquired;
}

int DeterministicLockManager::Unlock(vector<Key> keys, int transaction_id) {
  for (int i = 0; i < keys.size(); i++) {
    if (lock_table_.count(keys[i])) {
      if (lock_table_[keys[i]].front().size() > 0 &&
          lock_table_[keys[i]].front() == transaction_id) {
        // Specified txn holds this lock; release it.
        lock_table_[keys[i]].pop_front();
      } else {
        // Specified txn does not hold this lock; cancel any request for this
        // lock by the txn.
        for (vector<int>::iterator it = lock_table_[keys[i]].begin();
             it != lock_table_[keys[i]].end(); ++it) {
          if (*it == transaction_id) {
            lock_table_[keys[i]].erase(it);
            break;
          }
        }
      }
      // Specified txn should now have released the lock or cancelled its
      // request for the lock.
      DCHECK(!lock_table_[keys[i]].contains(transaction_id));

      // No need to keep the lock queue around if the lock is not held.
      if (lock_table_[keys[i]].empty())
        lock_table_.erase(keys[i]);
    }
  }
}

