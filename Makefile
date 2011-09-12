CXXFLAGS=-g -O2 -Wall -Wno-deprecated
LDFLAGS=

SRCS=
OBJS=$(SRCS:.cc=.o)

all: $(OBJS)
	$(MAKE) -C common
	$(MAKE) -C proto
	$(MAKE) -C client
	$(MAKE) -C sequencer
	$(MAKE) -C scheduler
	$(MAKE) -C backend
	$(MAKE) -C deployment

%.o: %.cc
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJS)
	$(MAKE) -C common clean
	$(MAKE) -C proto clean
	$(MAKE) -C client clean
	$(MAKE) -C sequencer clean
	$(MAKE) -C scheduler clean
	$(MAKE) -C backend clean
	$(MAKE) -C deployment clean

