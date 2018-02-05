cmake_minimum_required(VERSION 2.8.12)
set(PROJECT_NAME "Indie Studio")
project(${PROJECT_NAME} CXX C)
exec_program(
        "git"
        ${CMAKE_CURRENT_SOURCE_DIR}
        ARGS "describe" "--tags"
        OUTPUT_VARIABLE VERSION_FULL)
string(REGEX REPLACE "^v([0-9]+)\\..*" "\\1" VERSION_MAJOR "${VERSION_FULL}")
string(REGEX REPLACE "^v[0-9]+\\.([0-9]+).*" "\\1" VERSION_MINOR "${VERSION_FULL}")
string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" VERSION_PATCH "${VERSION_FULL}")
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
set(CMAKE_MODULE_PATH /usr/local/lib/OGRE/cmake)
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not permitted. Make a separate folder for building:\nmkdir build; cd build; cmake ..\nBefore that, remove the files already created:\nrm -rf CMakeCache.txt CMakeFiles")
endif(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)

if(WIN32)
    string(REGEX REPLACE "\\\\" "/" OGRE_HOME "$ENV{OGRE_HOME}")
elseif(UNIX)
    if(EXISTS "/usr/local/lib/OGRE/cmake")

        set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
        set(OGRE_SAMPLES_INCLUDEPATH "/usr/local/share/OGRE/samples/Common/include/") # We could just *assume* that developers uses this basepath : /usr/local

    elseif(EXISTS "/usr/lib/OGRE/cmake")

        set(CMAKE_MODULE_PATH "/usr/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
        set(OGRE_SAMPLES_INCLUDEPATH "/usr/share/OGRE/samples/Common/include/") # Otherwise, this one

    else ()
        message(SEND_ERROR "Failed to find module path.")
    endif(EXISTS "/usr/local/lib/OGRE/cmake")
endif(WIN32)
set(CMAKE_MODULE_PATH "${OGRE_HOME}/CMake/;${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif (CMAKE_BUILD_TYPE STREQUAL "")

set(CMAKE_DEBUG_POSTFIX "_d")

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}")

if (WIN32)
    set(Boost_USE_STATIC_LIBS TRUE)
    set(Boost_USE_MULTITHREADED TRUE)
    set(Boost_USE_STATIC_RUNTIME FALSE)
else ()
    set(Boost_USE_STATIC_LIBS FALSE)
    set(Boost_USE_MULTITHREADED TRUE)
    set(Boost_USE_STATIC_RUNTIME FALSE)
endif (WIN32)
find_package(Boost COMPONENTS system thread filesystem REQUIRED)

find_package(SDL2 REQUIRED)

find_package(OGRE REQUIRED)
if (${OGRE_VERSION} VERSION_LESS "1.9" OR ${OGRE_VERSION} VERSION_GREATER
        "1.9")
    message(FATAL_ERROR "${PROJECT_NAME} requires Ogre 1.9")
endif()
set(OGRE_SDK_BUILD TRUE)
set(OGRE_TEMPLATES_DIR "${OGRE_HOME}/CMake")
include(OgreAddTargets)
include(OgreConfigTargets)

find_package(OIS REQUIRED)
if(NOT OIS_FOUND)
    message(SEND_ERROR "Failed to find OIS.")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/bin")
if (WIN32 OR APPLE)
    if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
        set(CMAKE_INSTALL_PREFIX
                "${CMAKE_BINARY_DIR}/${PROJECT_NAME}" CACHE PATH
                "${PROJECT_NAME} install prefix" FORCE
                )
    endif (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
endif(WIN32 OR APPLE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CMAKE_CXX_STANDARD 14)

include_directories(
        ${OGRE_Overlay_INCLUDE_DIRS}
        ${OIS_INCLUDE_DIRS}
        ${OGRE_INCLUDE_DIRS}
        ${OGRE_SAMPLES_INCLUDEPATH}
        src/includes/
        src/BombManager
        src/includemap/
        src/IaManager
        src/ScoreManager/
        src/PlayerManager/
        src/CollisionManager/
        src/GUIManager/
        src/InputManager/
        src/EntitiesManager/
        src/EntitiesManager/AMovableEntity
        src/EntitiesManager/IMovableEntity
        src/MapManager/
        src/SceneManager/
        src/SoundManager/
        src/InputLinker/
        src/ConfigData/
        src/MenuManager/
        ${SDL2_INCLUDE_DIR}
)

set(SOURCE_FILES ${SOURCE_FILES}
        src/main.cpp)

add_executable(cpp_indie_studio ${SOURCE_FILES} ${HDRS})

target_link_libraries(cpp_indie_studio ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${OGRE_Overlay_LIBRARIES}
        ${OGRE_Terrain_LIBRARIES} ${CMAKE_CURRENT_SOURCE_DIR}/lib/libIrrKlang.so)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/bin)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/media)

# post-build copy for win32
if(WIN32 AND NOT MINGW)
    add_custom_command( TARGET cpp_indie_studio PRE_BUILD
            COMMAND if not exist .\\dist\\bin mkdir .\\dist\\bin )
    add_custom_command( TARGET cpp_indie_studio POST_BUILD
            COMMAND copy \"$(TargetPath)\" .\\dist\\bin )
endif(WIN32 AND NOT MINGW)

if(MINGW OR UNIX)
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/dist/bin)
endif(MINGW OR UNIX)


if(WIN32)

    install(TARGETS cpp_indie_studio
            RUNTIME DESTINATION bin
            CONFIGURATIONS All)

    install(DIRECTORY ${CMAKE_SOURCE_DIR}/dist/Media
            DESTINATION ./
            CONFIGURATIONS Release RelWithDebInfo Debug
            )

    install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins.cfg
            ${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
            DESTINATION bin
            CONFIGURATIONS Release RelWithDebInfo
            )

    install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins_d.cfg
            ${CMAKE_SOURCE_DIR}/dist/bin/resources_d.cfg
            DESTINATION bin
            CONFIGURATIONS Debug
            )

    # NOTE: for the 1.7.1 sdk the OIS dll is called OIS.dll instead of libOIS.dll
    # so you'll have to change that to make it work with 1.7.19
    install(FILES ${OGRE_PLUGIN_DIR_REL}/OgreMain.dll
            ${OGRE_PLUGIN_DIR_REL}/RenderSystem_Direct3D9.dll
            ${OGRE_PLUGIN_DIR_REL}/RenderSystem_GL.dll
            ${OGRE_PLUGIN_DIR_REL}/libOIS.dll
            DESTINATION bin
            CONFIGURATIONS Release RelWithDebInfo
            )

    install(FILES ${OGRE_PLUGIN_DIR_DBG}/OgreMain_d.dll
            ${OGRE_PLUGIN_DIR_DBG}/RenderSystem_Direct3D9_d.dll
            ${OGRE_PLUGIN_DIR_DBG}/RenderSystem_GL_d.dll
            ${OGRE_PLUGIN_DIR_DBG}/libOIS_d.dll
            DESTINATION bin
            CONFIGURATIONS Debug
            )

    # as of sdk 1.7.2 we need to copy the boost dll's as well
    # because they're not linked statically (it worked with 1.7.1 though)
    install(FILES ${Boost_DATE_TIME_LIBRARY_RELEASE}
            ${Boost_THREAD_LIBRARY_RELEASE}
            DESTINATION bin
            CONFIGURATIONS Release RelWithDebInfo
            )

    install(FILES ${Boost_DATE_TIME_LIBRARY_DEBUG}
            ${Boost_THREAD_LIBRARY_DEBUG}
            DESTINATION bin
            CONFIGURATIONS Debug
            )
endif(WIN32)

if(UNIX)

    install(TARGETS cpp_indie_studio
            RUNTIME DESTINATION bin
            CONFIGURATIONS All)

    install(DIRECTORY ${CMAKE_SOURCE_DIR}/dist/media
            DESTINATION .
            CONFIGURATIONS Release RelWithDebInfo Debug
            )

    install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins.cfg
            ${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
            DESTINATION bin
            CONFIGURATIONS Release RelWithDebInfo Debug
            )

        set (CheckFile "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/bin/BomberConfig.txt")
        add_custom_command(TARGET cpp_indie_studio
                POST_BUILD
                COMMAND ${CMAKE_COMMAND}
                -DCheckFile=${CheckFile} -DSRC_DIR=${CMAKE_SOURCE_DIR}
                -DBUILD_DIR=${CMAKE_BINARY_DIR}/${PROJECT_NAME}
                -P ${CMAKE_SOURCE_DIR}/check.cmake
                COMMENT "Checking if BomberConfig is installed.")

endif(UNIX)
