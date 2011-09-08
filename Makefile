CXXFLAGS=-g -O2 -Wall -Wno-deprecated
LDFLAGS=

SRCS=
OBJS=$(SRCS:.cc=.o)

all: $(OBJS)
	$(MAKE) -C scheduler
	$(MAKE) -C backend
	$(MAKE) -C testing

%.o: %.cc
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJS)
	$(MAKE) -C scheduler clean
	$(MAKE) -C backend clean
	$(MAKE) -C testing clean
