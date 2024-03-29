// Author: Shu-chun Weng (scweng@cs.yale.edu)
//
// Library for handling messaging between system nodes. Each node generally owns
// a Connection object as well as a Configuration object.

#ifndef _DB_COMMON_CONNECTION_H_
#define _DB_COMMON_CONNECTION_H_

#include <stdint.h>
#include <unistd.h>
#include <sys/select.h>
#include <google/protobuf/message.h>

#include <map>
#include <queue>
#include <set>
#include "../common/configuration.h"

using std::map;
using std::pair;
using std::queue;
using std::set;

using google::protobuf::Message;

class GenericTxn;
class Message;

// Proposed interface (alex, 9/11/11)
class Connection {
  explicit Connection(const Configuration& config);
  void Send(int node_id, Component component, const Message& message);
  Message* GetMessage();
  Message* GetNewTxn();
}

// Previous interface:
class Connection {
 public:
  ssize_t Send(int node_id, const void* buf, size_t count) const;

  ssize_t SendDB(int replica, int partition, const void* buf, size_t count);
  ssize_t SendDBMsg(const Message& message);

  ssize_t SendPreprocessor(int replica, int partition, const void* buf,
               size_t count);
  ssize_t SendMediator(int partition, const void* buf, size_t count);

  void FillIncomingTxns(CircularBuffer<GenericTxn>* txns,
                        int64_t wait_msec = 0LL,
                        CircularBuffer<int>* origin = 0);
  void FillIncomingMessages(CircularBuffer<Message>* msgs);
  
  static Connection* GetInstance(const Configuration& config);

 private:
  explicit Connection(const Configuration& config);
  Connection(const Connection&);
  Connection& operator=(const Connection&);

  void InitializeDB(const DBNode* node);
  void InitializePreprocessor(const PreprocessorNode* node);
  void InitializeMediator(const MediatorNode* node);

  void TryReconnect();
  void BuildFDSets();
  void AcceptingConnection(int server_sock);
  void AddConnection(const Node* node, int fd);

  // process pending outgoing connections
  int ConnectionEstablished(fd_set* fds);
  void Disconnected(int node_id);

  inline ssize_t SendReplicasAndPartitions(
      const map<int, map<int, int> >& fd_map,
      int replica, int partition,
      const void* buf, size_t count);

  int ReadTxn(int fd, GenericTxn* txn);
  int ReadMsg(int fd, Message* msg);

  const Configuration& _config;

  // Type: nodeID -> fd
  map<int, int> _fds;

  // Connect to port_for_new_txns for preprocessors and mediators,
  // to port_for_txn_msgs for dbs. Type: partition -> (replica -> fd)
  map<int, map<int, int> > _db_fds;

  // Type: partition -> (replica -> fd)
  map<int, map<int, int> > _preproc_fds;

  // Type: partition -> fd
  map<int, int> _mediator_fds;

  // Mediator nodes: clients
  set<int> _client_fds;

  // Type: fd -> nodeID
  map<int, int> _in_progress_fds;
  // Type: nodeID -> fd
  map<int, int> _in_progress_nodes;

  int _server_sock_txns;
  int _server_sock_msgs; // only used on DB nodes

  NodeType myNodeType;

  bool _fd_set_valid;
  int _txns_fd_max;
  int _msgs_fd_max; // only used on DB and mediator nodes
  int _in_progress_fd_max;
  fd_set _txns_fd_set;
  fd_set _msgs_fd_set; // only used on DB and mediator nodes
  fd_set _in_progress_fd_set;

  int64_t* _read_buf;
  int _read_buf_size;

#ifndef UNORDERED_RECEIVE
  map<int, queue<CircularBuffer<GenericTxn>*> > _txn_bufs;
#endif

  static map<const Configuration*, Connection*> _instances;
};

#endif // _DB_COMMON_CONNECTION_H_
