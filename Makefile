COMPILER = g++

SOURCE_LIBS = -I/opt/homebrew/Cellar/raylib/4.5.0/include

OSX_OPT = -std=c++11 -L/opt/homebrew/Cellar/raylib/4.5.0/lib/ -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL /opt/homebrew/Cellar/raylib/4.5.0/lib/libraylib.a   

CFILES = src/*.cpp

OSX_OUT = -o "bin/game"

build_osx:
	$(COMPILER) $(CFILES) $(SOURCE_LIBS) $(OSX_OUT) $(OSX_OPT) 