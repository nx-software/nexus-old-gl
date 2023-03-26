OBJS	= graphics/glad/src/glad.o exampleGame/main.o
SOURCE	= graphics/glad/src/glad.c exampleGame/main.cpp
HEADER	= graphics/gameObjects/gameObject.h graphics/shaders/shader.h engine.h graphics/graphics.h graphics/textures/stb_image.h graphics/textures/texture.h graphics/gui/imgui.h physics/collider.h physics/collide_check.h
OUT	= nexus
LFLAGS	 = 

all: nexus

nexus: $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.c $(HEADER)
	$(CC) -c -o $@ $< $(LFLAGS)

clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)