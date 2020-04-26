cmake_minimum_required(VERSION 3.17)
project(DreamEngine)

set(SRC_FILES 
# Audio
"src/Audio/Music.cpp"
# Components
"src/Components/AnimationComponent.cpp"
"src/Components/Camera.cpp"
"src/Components/DisplayComponent.cpp"
"src/Components/GameComponent.cpp"
"src/Components/ImageComponent.cpp"
"src/Components/PhysicsObject.cpp"
"src/Components/TextComponent.cpp"
"src/Components/UIComponent.cpp"
# GameSystem
"src/GameSystem/FileSystem.cpp"
"src/GameSystem/Game.cpp"
"src/GameSystem/GameEntity.cpp"
"src/GameSystem/Input.cpp"
"src/GameSystem/MathHelper.cpp"
"src/GameSystem/MusicManager.cpp"
"src/GameSystem/Object.cpp"
"src/GameSystem/Physics.cpp"
"src/GameSystem/Position.cpp"
"src/GameSystem/Scene.cpp"
"src/GameSystem/SceneManager.cpp"
"src/GameSystem/Time.cpp"
"src/GameSystem/Transform.cpp"
# Graphics
"src/Graphics/Animation.cpp"
"src/Graphics/DisplayObject.cpp"
"src/Graphics/Image.cpp"
# Misc
"src/Misc/Color.cpp"
"src/Misc/Debug.cpp"
# Main
"src/TourneScript.cpp"
"src/main.cpp"
)

add_executable(DreamEngine ${SRC_FILES})
target_link_libraries(DreamEngine SDL2 SDL2main SDL2_mixer SDL2_ttf SDL2_image physfs)
target_include_directories(DreamEngine PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(DreamEngine)