cmake_minimum_required (VERSION 3.8)

project ("D2DSpaceShooter")

set (CMAKE_WIN32_EXECUTABLE "True")
set (CMAKE_CXX_FLAGS 
"/Wall /std:c++20 /DUNICODE /TP /Zc:__cplusplus /EHs")

set (SOURCE_FILES
	src/MainWindow.h src/MainWindow.cpp "src/GraphicsEngine.cpp" "src/GraphicsEngine.h" "src/entities/Entity.cpp" "src/entities/Entity.h" "src/GameEngine.cpp" "src/GameEngine.h" "src/entities/BitmapEntity.cpp" "src/entities/BitmapEntity.h" "src/entities/TextEntity.cpp" "src/entities/TextEntity.h" "src/entities/GradientEntity.cpp" "src/entities/GradientEntity.h")

add_executable (D2DSpaceShooter ${SOURCE_FILES})

# Link Direct2D (d2d1.lib)
find_library(DIRECT2D d2d1)
if (NOT DIRECT2D)
    message(FATAL_ERROR "Could not find Direct2D.")
endif ()

# Link DirectWrite (dwrite.lib)
find_library(DIRECTWRITE dwrite)
if (NOT DIRECTWRITE)
    message(FATAL_ERROR "Could not find DirectWrite.")
endif ()

target_link_libraries(D2DSpaceShooter ${DIRECT2D})
target_link_libraries(D2DSpaceShooter ${DIRECTWRITE})
