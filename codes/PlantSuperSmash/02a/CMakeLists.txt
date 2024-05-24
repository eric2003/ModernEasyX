cmake_minimum_required(VERSION 3.28)

project(testprj)

set ( PRJ_SRC_LIST )
set ( PRJ_LIBRARIES )
set ( PRJ_INCLUDE_DIRS )
set ( PRJ_COMPILE_FEATURES )
set ( PRJ_COMPILE_DEFINITIONS )

set ( EASYX_PATH "c:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/VS/" )
set ( EASYX_INCLUDE_DIRS ${EASYX_PATH}/include )
set ( EASYX_LIBRARY_DIRS ${EASYX_PATH}/lib/x64 )
set ( EASYX_LIBRARIES ${EASYX_LIBRARY_DIRS}/EasyXa.lib )

set ( some_img32_LIB "MSIMG32.LIB")
set ( some_music_LIB "Winmm.lib")

get_directory_property( my_import_targets DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} IMPORTED_TARGETS )
message( STATUS "my_import_targets=${my_import_targets}" )

list ( APPEND PRJ_LIBRARIES ${EASYX_LIBRARIES} )
list ( APPEND PRJ_LIBRARIES ${some_img32_LIB} )
list ( APPEND PRJ_LIBRARIES ${some_music_LIB} )
list ( APPEND PRJ_INCLUDE_DIRS ${EASYX_INCLUDE_DIRS} )
list ( APPEND PRJ_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} )
list ( APPEND PRJ_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/scene )


if ( MSVC )
    set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME} )
endif()

list ( APPEND PRJ_COMPILE_FEATURES cxx_std_23 )

add_executable( ${PROJECT_NAME} )

target_sources( ${PROJECT_NAME}
    PRIVATE
        main.cpp
		Animation.h Animation.cpp
		Atlas.h Atlas.cpp
		util.h util.cpp
		scene/GameScene.h scene/GameScene.cpp
		scene/MenuScene.h scene/MenuScene.cpp
		scene/Scene.h scene/Scene.cpp
		scene/SceneManager.h scene/SceneManager.cpp
		scene/SelectorScene.h scene/SelectorScene.cpp
		
)

target_include_directories ( ${PROJECT_NAME}
	PRIVATE 
        ${PRJ_INCLUDE_DIRS}
)

target_link_libraries ( ${PROJECT_NAME} 
    PRIVATE 
        ${PRJ_LIBRARIES}
)

target_compile_definitions( ${PROJECT_NAME} 
    PRIVATE 
        ${PRJ_COMPILE_DEFINITIONS}
)

target_compile_features ( ${PROJECT_NAME} 
    PRIVATE 
    ${PRJ_COMPILE_FEATURES}
)
