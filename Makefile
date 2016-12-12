CXX := g++
CXXFLAGS := -std=c++11 -Wall -O3

HEADERS := header
SRCDIR := src
OBJDIR := build
BUILD := tbrg3

CXX_SRCS := $(wildcard $(SRCDIR)/*.cxx)
CXX_OBJS := $(patsubst $(SRCDIR)/%.cxx,$(OBJDIR)/%.cxx.o,$(CXX_SRCS))
OBJECTS := $(CXX_OBJS)

build: $(BUILD)

all: build

$(OBJDIR)/%.cxx.o: $(SRCDIR)/%.cxx
	@mkdir -p $(@D)
	$(CXX) -I $(HEADERS) -c -o $@ $< $(CXXFLAGS)

$(BUILD): $(OBJECTS)
	$(CXX) -I $(HEADERS) -o $@ $^ $(CXXFLAGS) -Os -s -fdata-sections -ffunction-sections -Wl,--gc-sections,--strip-all

.PHONY: clean
.PHONY: clean-all
.PHONY: install
.PHONY: rebuild

rebuild: clean-all all

clean:
	@rm -rf $(OBJDIR)

clean-all: clean
	@rm -f $(BUILD)

install: $(BUILD)
	$@ $^ /usr/local/bin/
