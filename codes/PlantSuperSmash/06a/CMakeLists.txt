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
list ( APPEND PRJ_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/nullet )
list ( APPEND PRJ_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/scene )
list ( APPEND PRJ_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/player )


if ( MSVC )
    set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME} )
endif()

list ( APPEND PRJ_COMPILE_FEATURES cxx_std_23 )

set ( playerDir "player" )
set ( player_header_files
    ${playerDir}/Player.h 
    ${playerDir}/PlayerID.h 
    ${playerDir}/PeashooterPlayer.h 
	${playerDir}/SunflowerPlayer.h 
)

set ( player_cpp_files
	${playerDir}/Player.cpp
	${playerDir}/PlayerID.cpp
	${playerDir}/PeashooterPlayer.cpp
	${playerDir}/SunflowerPlayer.cpp
)


set ( player_files
    ${player_header_files}
	${player_cpp_files}
)

set ( bulletDir "bullet" )
set ( bullet_header_files
    ${bulletDir}/Bullet.h 
    ${bulletDir}/PeaBullet.h 
    ${bulletDir}/SunBullet.h
	${bulletDir}/SunBulletEx.h
)
set ( bullet_cpp_files
	${bulletDir}/Bullet.cpp
	${bulletDir}/PeaBullet.cpp
	${bulletDir}/SunBullet.cpp	
	${bulletDir}/SunBulletEx.cpp	
)

set ( bullet_files
    ${bullet_header_files}
	${bullet_cpp_files}
)

set ( sceneDir "scene" )
set ( scene_header_files
    ${sceneDir}/Scene.h 
    ${sceneDir}/GameScene.h 
    ${sceneDir}/MenuScene.h 
    ${sceneDir}/SceneManager.h 
    ${sceneDir}/SelectorScene.h 
)

set ( scene_cpp_files
	${sceneDir}/Scene.cpp
	${sceneDir}/GameScene.cpp
	${sceneDir}/MenuScene.cpp	
	${sceneDir}/SceneManager.cpp
	${sceneDir}/SelectorScene.cpp		
)

set ( scene_files
    ${scene_header_files}
	${scene_cpp_files}
)

source_group ( "${bulletDir}/headers" FILES ${bullet_header_files} )
source_group ( "${bulletDir}/src" FILES ${bullet_cpp_files} )

source_group ( "${playerDir}/headers" FILES ${player_header_files} )
source_group ( "${playerDir}/src" FILES ${player_cpp_files} )

source_group ( "${sceneDir}/headers" FILES ${scene_header_files} )
source_group ( "${sceneDir}/src" FILES ${scene_cpp_files} )

add_executable( ${PROJECT_NAME} )

target_sources( ${PROJECT_NAME}
    PRIVATE
        main.cpp
		Animation.h Animation.cpp
		Atlas.h Atlas.cpp
		Camera.h Camera.cpp
		Platform.h Platform.cpp
		Timer.h Timer.cpp
		util.h util.cpp
		Vector2.h Vector2.cpp
		${bullet_files}
		${player_files}
		${scene_files}
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
