OBJS	= src/graphics/glad/src/glad.o exampleGame/main.o
SOURCE	= src/graphics/glad/src/glad.c exampleGame/main.cpp
HEADER	= src/graphics/gameObjects/gameObject.h src/graphics/shaders/shader.h src/engine.h src/graphics/graphics.h src/graphics/textures/stb_image.h src/graphics/textures/texture.h src/physics/collider.h src/physics/collide_check.h
OUT	= nexus
LFLAGS	 = 
CFLAGS   = -fpermissive

all: nexus

nexus: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c -o $@ $< $(LFLAGS)

clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)
