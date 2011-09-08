PROG=proto_test

CXXFLAGS=-g -O2 -Wno-deprecated -Wall
LDFLAGS=

PROTOS=txn.proto
SRCS=proto_test.cc txn.pb.cc
OBJS=$(SRCS:.cc=.o)

all: proto $(PROG)

proto:
	protoc --proto_path=. --cpp_out=. $(PROTOS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(PROG): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(PROG) $(OBJS) -lpthread

clean:
	rm -f $(PROG) $(OBJS) *.pb.h *.pb.cc *.pb.o

