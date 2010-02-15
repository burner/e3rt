CC=g++
LD=g++
#CFLAGS=-Wall -O3 -std=gnu++0x
CFLAGS=-ggdb -Wall -O3 -std=gnu++0x
LDFLAGS=-ggdb -Wall -lGL$(/usr/local/sdl-1.3/bin/sdl-config --cflags --libs) -lncurses -std=gnu++0x -lSDL_image libSOIL.a -lSDL_ttf
TARGET=e3rt

#OBJS=ShaderHandle.o vec3f.o tri.o ObjLoader.o vec2f.o tinyxml.o tinyxmlerror.o tinyxmlparser.o
OBJS=main.o ShaderHandle.o vec3f.o tri.o ObjLoader.o Timer.o Obj.o vec2f.o tinyxml.o tinyxmlerror.o tinyxmlparser.o Camera.o Sphere.o FontWriter.o

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(LD) $(LDFLAGS) -Wall $(OBJS) $(LIBS) -o $(TARGET) $(shell /usr/local/sdl-1.3/bin/sdl-config --cflags --libs)

clean:
	rm -f *.o $(TARGET)

ShaderHandle.o: util/ShaderHandle.cpp util/ShaderHandle.h
	$(CC) $(CFLAGS) -c util/ShaderHandle.cpp

Timer.o: util/Timer.cpp util/Timer.h
	$(CC) $(CFLAGS) -c util/Timer.cpp

vec2f.o: prim/vec2f.cpp prim/vec2f.h
	$(CC) $(CFLAGS) -c prim/vec2f.cpp

vec3f.o: prim/vec3f.cpp prim/vec3f.h
	$(CC) $(CFLAGS) -c prim/vec3f.cpp

main.o: main.cpp main.h
	$(CC) $(CFLAGS) -c main.cpp

tri.o: prim/tri.cpp prim/tri.h
	$(CC) $(CFLAGS) -c prim/tri.cpp

ObjLoader.o: util/ObjLoader.cpp util/ObjLoader.h prim/vec3f.h prim/vec2f.h prim/tri.h
	$(CC) $(CFLAGS) -c util/ObjLoader.cpp

utils.o: utils.cpp utils.h
	$(CC) $(CFLAGS) -c utils.cpp

Obj.o: display/Obj.cpp display/Obj.h
	$(CC) $(CFLAGS) -c display/Obj.cpp

Camera.o: display/Camera.h display/Camera.cpp
	$(CC) $(CFLAGS) -c display/Camera.cpp

tinyxml.o: tinyxml/tinyxml.h tinyxml/tinyxml.cpp
	$(CC) $(CFLAGS) -c tinyxml/tinyxml.cpp

tinyxmlerror.o: tinyxml/tinyxml.h tinyxml/tinyxmlerror.cpp
	$(CC) $(CFLAGS) -c tinyxml/tinyxmlerror.cpp

tinyxmlparser.o: tinyxml/tinyxml.h tinyxml/tinyxmlparser.cpp
	$(CC) $(CFLAGS) -c tinyxml/tinyxmlparser.cpp

Sphere.o: display/Sphere.h display/Sphere.cpp display/Obj.h display/Obj.cpp
	$(CC) $(CFLAGS) -c display/Sphere.cpp

FontWriter.o: display/FontWriter.h display/FontWriter.cpp
	$(CC) $(CFLAGS) -c display/FontWriter.cpp
