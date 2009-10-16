CC=g++
LD=g++
CFLAGS=-ggdb -Wall -O3 -std=gnu++0x
LDFLAGS=-ggdb -Wall -lGL$(/usr/local/sdl-1.3/bin/sdl-config --cflags --libs) -lncurses -std=gnu++0x
TARGET=e3rt

#OBJS=main.o ShaderHandle.o vec3f.o tri.o ObjLoader.o Timer.o utils.o Obj.o vec2f.o tinyxml.o tinyxmlerror.o tinyxmlparser.o
OBJS=main.o ShaderHandle.o vec3f.o tri.o ObjLoader.o Timer.o Obj.o vec2f.o tinyxml.o tinyxmlerror.o tinyxmlparser.o Camera.o

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(LD) $(LDFLAGS) -Wall $(OBJS) $(LIBS) -o $(TARGET) $(shell /usr/local/sdl-1.3/bin/sdl-config --cflags --libs)

.cpp.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TARGET)

Node.o:	Node.cpp Node.h
ShaderHandle.o: ShaderHandle.cpp ShaderHandle.h
Timer.o: Timer.cpp Timer.h
vec2f.o: vec2f.cpp vec2f.h
vec3f.o: vec3f.cpp vec3f.h
main.o: main.cpp main.h
tri.o: tri.cpp tri.h
ObjLoader.o: ObjLoader.cpp ObjLoader.h
utils.o: utils.cpp utils.h
Obj.o: Obj.cpp Obj.h
Camera.o: Camera.h Camera.cpp
tinyxml.o: tinyxml.h tinyxml.cpp
tinyxmlerror.o: tinyxml.h tinyxmlerror.cpp
tinyxmlparser.o: tinyxml.h tinyxmlparser.cpp
