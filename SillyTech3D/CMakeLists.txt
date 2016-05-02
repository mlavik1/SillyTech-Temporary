cmake_minimum_required(VERSION 3.3)
project(SillyTech3D)

# Gather c++ files
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Set include
include_directories(src)
#include_directories(src/ui)

# External
include_directories ("Include")
include_directories ("Include/assimp")
include_directories ("Include/openal")
include_directories ("Include/glm")
include_directories ("Include/physx")
include_directories ("Include/SDL2")
include_directories ("Include/glew")
include_directories ("Include/boost")
include_directories ("Include/lua")
include_directories ("Include/luabind")

message("${LIB_DIR}}")
# Make executable
add_executable(SillyTech3D ${SRC_FILES} ${RESOURCE_ADDED})
target_link_libraries(SillyTech3D ${OPENGL_LINK})
TARGET_LINK_LIBRARIES(SillyTech3D glu32.lib)


LINK_DIRECTORIES(SillyTech3D ../Libraries/Windows/x86)
TARGET_LINK_LIBRARIES(SillyTech3D ${LIB_DIR}/AntTweakBar.lib)
TARGET_LINK_LIBRARIES(SillyTech3D ${LIB_DIR}/alut.lib)
TARGET_LINK_LIBRARIES(SillyTech3D ${LIB_DIR}/assimp.lib)
TARGET_LINK_LIBRARIES(SillyTech3D ${LIB_DIR}/glew32.lib)
TARGET_LINK_LIBRARIES(SillyTech3D ${LIB_DIR}/SDL2_mixer.lib)
TARGET_LINK_LIBRARIES(SillyTech3D ${LIB_DIR}/SDL2_image.lib)
TARGET_LINK_LIBRARIES(SillyTech3D ${LIB_DIR}/SDL2main.lib)
TARGET_LINK_LIBRARIES(SillyTech3D ${LIB_DIR}/SDL2.lib)
TARGET_LINK_LIBRARIES(SillyTech3D ${LIB_DIR}/glew32.lib)
TARGET_LINK_LIBRARIES(SillyTech3D ${LIB_DIR}/lua.debug.lib)
TARGET_LINK_LIBRARIES(SillyTech3D ${LIB_DIR}/luabind.debug.lib)
TARGET_LINK_LIBRARIES(SillyTech3D ${LIB_DIR}/OpenAL32.lib)
TARGET_LINK_LIBRARIES(SillyTech3D ${LIB_DIR}/PhysX3DEBUG_x86.lib)
TARGET_LINK_LIBRARIES(SillyTech3D ${LIB_DIR}/PhysX3CommonDEBUG_x86.lib)
TARGET_LINK_LIBRARIES(SillyTech3D ${LIB_DIR}/PhysX3ExtensionsDEBUG.lib)


# Gather all other important files to be copied over to the output folder
file(GLOB_RECURSE AddonFiles *.png *.mtl *.obj *.bin *.dat *.jpg *.tfps *.ini)
foreach(AddonFile ${AddonFiles})
	get_filename_component(OUT_DIR ${AddonFile} DIRECTORY)
	string(REGEX REPLACE "${CMAKE_CURRENT_LIST_DIR}"
			"" OUT_DIR ${OUT_DIR})

	file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}${OUT_DIR})
	add_custom_command(TARGET GET SillyTech3D PRE_BUILD
			COMMAND ${CMAKE_COMMAND} -E
			copy ${AddonFile} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}${OUT_DIR}/)
endforeach(AddonFile)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	file(GLOB_RECURSE nativeLibs ../Libraries/Windows/x86/*.dll)
	foreach(AddonFile ${nativeLibs})
		get_filename_component(OUT_DIR ${AddonFile} DIRECTORY)
		string(REGEX REPLACE "${CMAKE_CURRENT_LIST_DIR}/../Libraries/Windows/x86"
				"" OUT_DIR ${OUT_DIR})
	
		file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}${OUT_DIR})
		add_custom_command(TARGET GET SillyTech3D PRE_BUILD
				COMMAND ${CMAKE_COMMAND} -E
				copy ${AddonFile} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}${OUT_DIR}/)
	endforeach(AddonFile)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

