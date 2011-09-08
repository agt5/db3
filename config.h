// Author: Shu-chun Weng (scweng@cs.yale.edu)
//
// Each node in the system has a Configuration, which stores the identity of
// that node, the system's current execution mode, and the set of all currently
// active nodes in the system.

#ifndef _YALE_SCALE_CONFIG_H_
#define _YALE_SCALE_CONFIG_H_ 1

#include <stdint.h>

#include <map>
#include <string>
#include <vector>

// #define UNORDERED_RECEIVE 1

using std::map;
using std::string;
using std::vector;

enum ExecutionMode{
  MODE_DETERMINISTIC,
  MODE_TRADITIONAL,
};

enum NodeType{
  DB_NODE, PREPROCESSOR_NODE, MEDIATOR_NODE,
};

struct Node {
  int node_id;         // Globally unique node identifier.
  NodeType node_type;  // Type of this node.
  string host;         // Hostname/IP address of this node's machine.
  int cores;           // Total number of cores available for use by the
                       //   database system on this node's machine.
};

struct DBNode : public Node {
  int replica_id;
  int partition_id;
  int port_for_new_txns;
  int port_for_txn_msgs;
};

struct PreprocessorNode : public Node {
  int replica_id;
  int partition_id;
  int port;
};

struct MediatorNode : public Node {
  int partition_id;
  int port;
};

class Configuration {
 public:
  explicit Configuration(int node_id);
  Configuration(int node_id, const string& filename);
  virtual ~Configuration() {}

  int PartitionContainingRecord(Key key) const;

  int64 this_NodeID;

  int64 wait_time;

  map<int, Node*>  all_nodes;
  map<int, MediatorNode*> mediators;
  map<int, vector<DBNode*> > dbreplicas;  // dbreplicas[x] returns a vector of all partitions within replica x
  map<int, vector<DBNode*> > dbpartitions; // dbpartitions[x] returns a vector of nodes that are partition x for some replica
  map<int, vector<PreprocessorNode*> > preprocessorreplicas;
  map<int, vector<PreprocessorNode*> > preprocessorpartitions;

  map<string, string> other_opt;

  ExecutionMode execution_mode;

 private:
  int ReadFromFile(const string& filename);
  virtual void ProcessConfigLine(char key[], char value[]);
};

#endif // !defined(_YALE_SCALE_CONFIG_H_)
