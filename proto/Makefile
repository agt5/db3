PROG=proto_test

CXXFLAGS=-g -O2 -Wno-deprecated -Wall
LDFLAGS=

PROTOS=txn.proto
PROTO_HDRS=$(PROTOS:.proto=.pb.h)
SRCS=proto_test.cc txn.pb.cc
OBJS=$(SRCS:.cc=.o)

all: $(PROG)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJS): $(PROTO_HDRS)

%.pb.cc %.pb.h: %.proto
	protoc --proto_path=. --cpp_out=. $<

$(PROG): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(PROG) $(OBJS) -lpthread -lprotobuf

clean:
	rm -f $(PROG) $(OBJS) *.pb.h *.pb.cc *.pb.o

