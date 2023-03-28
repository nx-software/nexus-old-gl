OBJS	= src/graphics/glad/src/glad.o exampleGame/main.o libglfw3.a
SOURCE	= src/graphics/glad/src/glad.c exampleGame/main.cpp
HEADER	= src/graphics/gameObjects/gameObject.h src/graphics/shaders/shader.h src/engine.h src/graphics/graphics.h src/graphics/textures/stb_image.h src/graphics/textures/texture.h src/physics/*.h
#collider.h
#src/physics/collide_check.h 
OUT	= nexus
LFLAGS	 = -lglfw -lGL -lm -lX11 -lpthread -ldl
CFLAGS   = -fpermissive
CC = g++
all: nexus

nexus: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

%.o: %.cpp $(HEADER)
	$(CC) $(CFLAGS) -c -o $@ $< $(LFLAGS)
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c -o $@ $< $(LFLAGS)

clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)
