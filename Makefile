CXX := g++
CXXFLAGS := -Wall -Wextra -std=gnu++14 -MMD -MP -O3

SOURCES = $(wildcard *.cc)
OBJECTS = $(SOURCES:.cc=.o)

.PHONY: clean

planes: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ -c

clean:
	$(RM) *.o planes *.d

-include $(OBJECTS:.o=.d)
