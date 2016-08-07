cmake_minimum_required(VERSION 3.3)
project(SillyTech3D)

# Gather c++ files
file(GLOB_RECURSE SRC_FILES 
	src/*.cpp
	src/*.h
)

set(SourceDir ${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE SRC_ACTOR
    "${SourceDir}/Actor/*.cpp"
    "${SourceDir}/Actor/*.h"
)
file(GLOB_RECURSE SRC_COMMON_DEBUGGING
    "${SourceDir}/Common/Debugging/*.cpp"
    "${SourceDir}/Common/Debugging/*.h"
)
file(GLOB_RECURSE SRC_COMMON_INTERFACES
    "${SourceDir}/Common/Interfaces/*.cpp"
    "${SourceDir}/Common/Interfaces/*.h"
)
file(GLOB_RECURSE SRC_COMMON_MACRO
    "${SourceDir}/Common/Macro/*.cpp"
    "${SourceDir}/Common/Macro/*.h"
)
file(GLOB SRC_COMMON
    "${SourceDir}/Common/*.cpp"
    "${SourceDir}/Common/*.h"
)
file(GLOB_RECURSE SRC_COMPONENTS
    "${SourceDir}/Components/*.cpp"
    "${SourceDir}/Components/*.h"
)
file(GLOB_RECURSE SRC_EDITOR
    "${SourceDir}/Editor/*.cpp"
    "${SourceDir}/Editor/*.h"
)
file(GLOB_RECURSE SRC_ENGINE
    "${SourceDir}/Engine/*.cpp"
    "${SourceDir}/Engine/*.h"
)
file(GLOB_RECURSE SRC_FACTORIES
    "${SourceDir}/Factories/*.cpp"
    "${SourceDir}/Factories/*.h"
)
file(GLOB_RECURSE SRC_FEATURES
    "${SourceDir}/Features/*.cpp"
    "${SourceDir}/Features/*.h"
)
file(GLOB_RECURSE SRC_FILEIO
    "${SourceDir}/FileIO/*.cpp"
    "${SourceDir}/FileIO/*.h"
)
file(GLOB_RECURSE SRC_GEOMETRY
    "${SourceDir}/Geometry/*.cpp"
    "${SourceDir}/Geometry/*.h"
)
file(GLOB_RECURSE SRC_GRAPHICS
    "${SourceDir}/Graphics/*.cpp"
    "${SourceDir}/Graphics/*.h"
)
file(GLOB_RECURSE SRC_GUI
    "${SourceDir}/GUI/*.cpp"
    "${SourceDir}/GUI/*.h"
)
file(GLOB_RECURSE SRC_MANAGERS
    "${SourceDir}/Managers/*.cpp"
    "${SourceDir}/Managers/*.h"
)
file(GLOB_RECURSE SRC_MODEL
    "${SourceDir}/Model/*.cpp"
    "${SourceDir}/Model/*.h"
)
file(GLOB_RECURSE SRC_PHYSICS
    "${SourceDir}/Physics/*.cpp"
    "${SourceDir}/Physics/*.h"
)
file(GLOB_RECURSE SRC_RESOURCES
    "${SourceDir}/Resources/*.cpp"
    "${SourceDir}/Resources/*.h"
)
file(GLOB_RECURSE SRC_SCRIPTING
    "${SourceDir}/Scripting/*.cpp"
    "${SourceDir}/Scripting/*.h"
)

file(GLOB_RECURSE SRC_TOOLS
    "${SourceDir}/Tools/*.cpp"
    "${SourceDir}/Tools/*.h"
)
source_group("Actor" FILES ${SRC_ACTOR})
source_group("Common\\Debugging" FILES ${SRC_COMMON_DEBUGGING})
source_group("Common\\Interfaces" FILES ${SRC_COMMON_INTERFACES})
source_group("Common\\Macro" FILES ${SRC_COMMON_MACRO})
source_group("Common" FILES ${SRC_COMMON})
source_group("Components" FILES ${SRC_COMPONENTS})
source_group("Editor" FILES ${SRC_EDITOR})
source_group("Engine" FILES ${SRC_ENGINE})
source_group("Factories" FILES ${SRC_FACTORIES})
source_group("Features" FILES ${SRC_FEATURES})
source_group("FileIO" FILES ${SRC_FILEIO})
source_group("Geometry" FILES ${SRC_GEOMETRY})
source_group("Graphics" FILES ${SRC_GRAPHICS})
source_group("GUI" FILES ${SRC_GUI})
source_group("Managers" FILES ${SRC_MANAGERS})
source_group("Model" FILES ${SRC_MODEL})
source_group("Physics" FILES ${SRC_PHYSICS})
source_group("Resources" FILES ${SRC_RESOURCES})
source_group("Scripting" FILES ${SRC_SCRIPTING})
source_group("Tools" FILES ${SRC_TOOLS})

message(${SourceDir})
FILE(GLOB_RECURSE children2 RELATIVE ${SourceDir} ${SourceDir}/*)
FOREACH(child ${children2})

IF(IS_DIRECTORY ${SourceDir}/${curdir}/${child})
	message( ${curdir}/${child})
	include_directories ( ${curdir}/${child})
ENDIF()
ENDFOREACH()

include_directories(src)
include_directories(src/data)
include_directories(src/resources)
include_directories(src/scene)
include_directories(src/view)
include_directories(src/utils)
include_directories(src/ui)

include_directories("${SourceDir}/Actor")
include_directories("${SourceDir}/Common\\Debugging")
include_directories("${SourceDir}/Common\\Interfaces")
include_directories("${SourceDir}/Common\\Macro")
include_directories("${SourceDir}/Common")
include_directories("${SourceDir}/Components")
include_directories("${SourceDir}/Editor")
include_directories("${SourceDir}/Engine" )
include_directories("${SourceDir}/Factories")
include_directories("${SourceDir}/Features" )
include_directories("${SourceDir}/FileIO" )
include_directories("${SourceDir}/Geometry" )
include_directories("${SourceDir}/Graphics")
include_directories("${SourceDir}/GUI" )
include_directories("${SourceDir}/Managers" )
include_directories("${SourceDir}/Model" )
include_directories("${SourceDir}/Physics" )
include_directories("${SourceDir}/Resources" )
include_directories("${SourceDir}/Scripting" )
include_directories("${SourceDir}/Tools" )



# External
include_directories ("Include")
include_directories ("Include/assimp")
include_directories ("Include/openal")
include_directories ("Include/glm")
include_directories ("Include/physx")
include_directories ("Include/sdl2")
include_directories ("Include/glew")
include_directories ("Include/boost")
include_directories ("Include/lua")
include_directories ("Include/luabind")

message("${LIB_DIR}}")
# Make executable
add_executable(SillyTech3D ${SRC_FILES} ${RESOURCE_ADDED})

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
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
else("")
	TARGET_LINK_LIBRARIES(SillyTech3D GL)
	TARGET_LINK_LIBRARIES(SillyTech3D GLU)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")


# Resources
file(GLOB_RECURSE AddonFiles Resources/*.*)
foreach(AddonFile ${AddonFiles})
	get_filename_component(OUT_DIR ${AddonFile} DIRECTORY)
	#message(${OUT_DIR})
	string(REGEX REPLACE "${CMAKE_CURRENT_LIST_DIR}" "" OUT_DIR ${OUT_DIR})
	
	file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}${OUT_DIR})
	add_custom_command(TARGET GET SillyTech3D PRE_BUILD
			COMMAND ${CMAKE_COMMAND} -E
			copy ${AddonFile} ${CMAKE_CURRENT_BINARY_DIR}${OUT_DIR}/)
			#message(${CMAKE_CURRENT_BINARY_DIR}${OUT_DIR})
endforeach(AddonFile)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

	if (${CMAKE_GENERATOR} MATCHES "Visual Studio 14")
		 set (DLL_TO_DBG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
		 set (DLL_TO_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)
	else()
		 set (DLL_TO_DBG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
		 set (DLL_TO_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	endif()

	file(GLOB_RECURSE nativeLibs ../Libraries/Windows/x86/*.dll)
	foreach(AddonFile ${nativeLibs})
		get_filename_component(OUT_DIR ${AddonFile} DIRECTORY)
		string(REGEX REPLACE "${CMAKE_CURRENT_LIST_DIR}/../Libraries/Windows/x86"
				"" OUT_DIR ${OUT_DIR})
	
		file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}${OUT_DIR})
		add_custom_command(TARGET GET SillyTech3D PRE_BUILD
				COMMAND ${CMAKE_COMMAND} -E
				copy ${AddonFile} ${DLL_TO_DBG}/)
	endforeach(AddonFile)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

