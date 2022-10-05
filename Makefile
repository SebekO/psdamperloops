CXX=/acc/local/Linux/x86_64-linux-gcc/current/gcc/bin/g++

LIBPSDL_VER=1.0.0

CPU?=L867

EDGE_VER=2.1

EDGE_DRIVER_PATH=/acc/local/$(CPU)/drv/edge/$(EDGE_VER)

LIBPSDL_PATH?=/user/sowarzan/libs/rf-ps_damper-lib/build

SRC_PATH=src

INCLUDES= -I$(LIBPSDL_PATH)/include -I$(EDGE_DRIVER_PATH)/include
INCLUDES+= -I$(SRC_PATH)

CXXFLAGS= -std=c++11 -g $(INCLUDES) -D_GLIBCXX_USE_CXX11_ABI=0 --sysroot=/acc/sys/L867 --sysroot=/acc/sys/L867 -m64 -fPIC -Wl,-rpath=/acc/sys/Linux/toolchain_libs:/acc/local/Linux/x86_64-linux-gcc/toolchain_libs:$(EDGE_DRIVER_PATH)/lib

LDFLAGS= -L$(LIBPSDL_PATH)/lib/$(CPU) -lrf-ps_damper-lib -L$(EDGE_DRIVER_PATH)/lib -ledge

TARGET=psdamperloop

BUILD_DIR=build


SOURCES=$(wildcard $(SRC_PATH)/*.cpp)
OBJECTS=$(SOURCES:$(SRC_PATH)/%.cpp=$(BUILD_DIR)/%.o)

all: build_dir $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$@ $^ $(LDFLAGS)

build_dir:
	mkdir -p $(BUILD_DIR)

clean:
	rm -r $(BUILD_DIR)

.PHONY: all
