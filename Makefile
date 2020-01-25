CXX       = ./toolchains/sx7_toolchain/armv7a/bin/armv7a-cros-linux-gnueabi-clang
CXXFLAGS  = -Wall -march=armv7-a -mcpu=cortex-a9 -marm -mlittle-endian -mfpu=neon -mfloat-abi=hard -stdlib=libc++
CXXFLAGS  += -DPURE_LITTLE_ENDIAN

LDFLAGS   = -L ../sx7_sdk/Install/Core/Lib -ltplfTtsClient \
	    -L ./vs_build/prebuilt/platform -lchromium_platform_1.0 \
	    -L ./vs_build/prebuilt/platform -lfps

INC       = -I ../sx7_sdk/Inc \
	    -I ../sx7_sdk/Application/Inc \
	    -I ../sx7_sdk/Install/Core/Inc/Utility/TridUtil \
	    -I ../sx7_sdk/Application/Inc/Tplfapi \
	    -I ../sx7_sdk/Install/Core/Inc/TAPI 

OBJS   	  = sampletts.o
TARGET    = sampletts 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LIBS) $(LDFLAGS)

sampletts.o: src/sampletts.c
	$(CXX) $(CXXFLAGS) $(INC) -c src/sampletts.c 

clean:
	rm -f $(OBJS) $(TARGET)
