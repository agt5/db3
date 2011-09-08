// Author: Alexander Thomson (thomson@cs.yale.edu)

#include "txn.pb.h"

#include <assert.h>

using namespace std;

int main(int argc, char** argv) {
  TxnProto* t = new TxnProto();
  t->set_txn_id(1);
  assert(t->txn_id() == 1);
  delete t;
}
