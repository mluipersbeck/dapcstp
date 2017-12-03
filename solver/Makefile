
EXEC      = dapcstp
CXX       = g++
INCLUDES  = -Iinclude
LIBS      = -lboost_timer -lboost_system -lboost_chrono -lboost_program_options -lboost_filesystem
CXXFLAGS  = -std=c++11 -MMD ${INCLUDES}

SRCS      = $(wildcard */*.cpp)
OBJS      = $(SRCS:.cpp=.o)
DEPS      = $(SRCS:.cpp=.d)

.PHONY: all debug clean

all: CXXFLAGS += -O3 -DNDEBUG
#just link boost static
all: LIBS := -Wl,-Bstatic $(LIBS) -Wl,-Bdynamic
all: $(EXEC)

debug: CXXFLAGS += -O0 -g3
debug: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) -o $@ $^ $(LIBS)
clean:
	rm -f $(OBJS) $(DEPS) $(TARGETS) $(EXEC)

-include $(SRCS:%.cpp=%.d)
