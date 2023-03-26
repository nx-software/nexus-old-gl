#rm nexus
#g++ src/graphics/glad/src/glad.c src/graphics/gameObjects/gameObject.h src/graphics/shaders/shader.h exampleGame/main.cpp engine.h graphics/graphics.h graphics/textures/stb_image.h graphics/textures/texture.h graphics/gui/imgui.h physics/collider.h physics/collide_check.h libglfw3.a -fpermissive -lglfw -lGL -lGLU -lm -lX11 -lpthread -lXi -lXrandr -ldl -o nexus
make
./nexus
