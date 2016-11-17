CXX=clang++

CXXFLAGS=-Wall -g `pkg-config --cflags gtk+-2.0`
LDFLAGS=`pkg-config --libs gtk+-2.0`

DEPS=src/main.o src/model.o src/drawable.o src/generic_block.o

all:	cirgen


cirgen:	$(DEPS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

%.o:	%.c
	$(CXX) -c -o $@ $^ $(CXXFLAGS)
