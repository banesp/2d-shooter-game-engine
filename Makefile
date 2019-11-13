CXX = g++
CXXFLAGS = -w -std=c++14 -Wfatal-errors
LDFLAGS = -I"./lib/lua" -L"./lib/lua" -llua -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

src = $(wildcard src/*.cpp) \
	$(wildcard src/Engine/*.cpp) \
	$(wildcard src/States/*.cpp) \
	$(wildcard src/Data/*.cpp) \
	$(wildcard src/Components/*.cpp)
obj = $(src:.cpp=.o)

game: $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) build

run:
	./game;
