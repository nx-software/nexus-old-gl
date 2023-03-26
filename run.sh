rm nexus
g++ graphics/glad/src/glad.c graphics/gameObjects/gameObject.h graphics/shaders/shader.h exampleGame/main.cpp engine.h graphics/graphics.h graphics/textures/stb_image.h graphics/textures/texture.h graphics/gui/imgui.h libglfw3.a -fpermissive -lglfw -lGL -lGLU -lm -lX11 -lpthread -lXi -lXrandr -ldl -o nexus
./nexus
