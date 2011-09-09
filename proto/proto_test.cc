// Author: Alexander Thomson (thomson@cs.yale.edu)

#include "txn.pb.h"
#include "../testing.h"

#include <sstream>

using namespace std;

TEST(TxnProtoTest) {
  TxnProto t1, t2;

  // Test accessor functions.
  t1.set_txn_id(4);
  t1.set_txn_type(8);
  t1.set_isolation_level(TxnProto::SERIALIZABLE);
  EXPECT_EQ(t1.txn_id(), 4);
  EXPECT_TRUE(t1.has_txn_type());
  EXPECT_TRUE(!t1.has_multipartition());

  // Test encoding.
  string encoded;
  EXPECT_TRUE(t1.SerializeToString(&encoded));
  EXPECT_TRUE(t2.ParseFromString(encoded));
  EXPECT_EQ(t1.DebugString(),t2.DebugString());

  END;
}

int main(int argc, char** argv) {
  TxnProtoTest();
}

