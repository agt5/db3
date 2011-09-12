PROG=types_test

CXXFLAGS=-g -O2 -Wno-deprecated -Wall
LDFLAGS=

SRCS=types_test.cc #configuration.cc connection.cc
OBJS=$(SRCS:.cc=.o)

all: $(PROG)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(PROG): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(PROG) $(OBJS)

clean:
	rm -f $(PROG) $(OBJS)

