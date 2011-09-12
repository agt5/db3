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

// Note: each node has one sequencer, one scheduler, and one backend; these are
// not separate nodes.
enum Component { SEQUENCER, SCHEDULER, BACKEND, };

struct Node {
  // Globally unique node identifier.
  int node_id;
  int replica_id;
  int partition_id;

  // Hostname/IP address of this node's machine.
  string host;

  // Ports for individual components within this node.
  int sequencer_port;
  int scheduler_new_txn_port;
  int scheduler_message_port;
  int backend_port;

  // Total number of cores available for use by this node.
  // Note: Is this needed?
  int cores;
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
