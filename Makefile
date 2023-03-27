OUTPUT	:= a
SOURCES	:= a.cpp 
LD_FLAGS := -lPocoNet -lPocoFoundation -lPocoUtil -lstdc++
all:
	g++ -o $(OUTPUT) $(SOURCES) $(LD_FLAGS)
