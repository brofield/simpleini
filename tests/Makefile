CXX?=g++
CXXFLAGS+=-Wall -std=c++14

# Try to find gtest using pkg-config first
GTEST_CFLAGS := $(shell pkg-config --cflags gtest_main 2>/dev/null)
GTEST_LIBS := $(shell pkg-config --libs gtest_main 2>/dev/null)

# If pkg-config fails, try to find gtest via homebrew on MacOS
ifeq ($(GTEST_LIBS),)
    UNAME := $(shell uname -s)
    ifeq ($(UNAME),Darwin)
        # Try formula-specific prefix first (modern Homebrew)
        BREW_GTEST_PREFIX := $(shell brew --prefix googletest 2>/dev/null)
        ifneq ($(BREW_GTEST_PREFIX),)
            GTEST_CFLAGS := -I$(BREW_GTEST_PREFIX)/include
            GTEST_LIBS := -L$(BREW_GTEST_PREFIX)/lib -lgtest_main -lgtest
        else
            # Fall back to general brew prefix
            BREW_PREFIX := $(shell brew --prefix 2>/dev/null)
            ifneq ($(BREW_PREFIX),)
                GTEST_CFLAGS := -I$(BREW_PREFIX)/include
                GTEST_LIBS := -L$(BREW_PREFIX)/lib -lgtest_main -lgtest
            endif
        endif
    endif
endif

# If still not found, try standard system locations
ifeq ($(GTEST_LIBS),)
    GTEST_CFLAGS := -I/usr/local/include
    GTEST_LIBS := -L/usr/local/lib -lgtest_main -lgtest -lpthread
endif

CXXFLAGS+=$(GTEST_CFLAGS)
LDFLAGS+=$(GTEST_LIBS)

OBJS=ts-roundtrip.o ts-snippets.o ts-utf8.o ts-bugfix.o ts-quotes.o ts-noconvert.o

BIN=./tests

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) -o $(BIN) $(OBJS) $(LDFLAGS)

clean:
	rm -f core $(OBJS) $(BIN)

test: $(BIN)
	$(BIN)

$(OBJS): ../SimpleIni.h

