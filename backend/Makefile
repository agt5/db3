PROG=simple_backend_test

CXXFLAGS=-g -O2 -Wno-deprecated -Wall
LDFLAGS=

SRCS=simple_backend_test.cc ../proto/txn.pb.cc
OBJS=$(SRCS:.cc=.o)

all: $(PROG)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(PROG): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(PROG) $(OBJS) -lpthread -lprotobuf

clean:
	rm -f $(PROG) $(OBJS)

test: $(PROG)
	./simple_backend_test
