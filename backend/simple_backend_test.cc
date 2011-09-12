// Author: Alexander Thomson (thomson@cs.yale.edu)

#include "simple_backend.h"

#include <vector>
#include "../common/testing.h"

using namespace std;

TEST(SimpleBackendTest) {
  SimpleBackend backend;

  // Execute a transaction.
  TxnProto t1;
  t1.set_txn_id(1);
  t1.add_write_set(ToKey(10));
  backend.Execute(&t1);
  EXPECT_EQ(PackInt64(1), backend.Lookup(ToKey(10)));

  // Execute another transaction.
  backend.Execute(&t1);
  EXPECT_EQ(PackInt64(2), backend.Lookup(ToKey(10)));

  END;
}

int main(int argc, char** argv) {
  SimpleBackendTest();
}

