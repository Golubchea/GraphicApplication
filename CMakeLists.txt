project(GraphicApplication)
cmake_minimum_required(VERSION 2.8)

set (${PROJECT_NAME}_VERSION_MAJOR 0)
set (${PROJECT_NAME}_VERSION_MINOR 1)
include(CheckCXXCompilerFlag)
option(SDL_SHARED "help string describing option" OFF)
set( SDL_SHARED OFF CACHE BOOL "Build the shared SDL library" )
set( SDL_STATIC ON CACHE BOOL "Build a static version of the library" )
set( SDL_AUDIO OFF CACHE BOOL "Audio" )
set( VIDEO_OPENGLES OFF CACHE BOOL  "Include OpenGL ES support")
set(SDL_STATIC_PIC  ON CACHE BOOL  "Static version of the library should be built with Position Independent Code")
#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ ")
set( glew-cmake_BUILD_STATIC ON CACHE BOOL "Build the static glew library" )
 
set(BUILD_SHARED_LIBS OFF)

check_cxx_compiler_flag(-std=c++17 HAVE_FLAG_STD_CXX17)
if(HAVE_FLAG_STD_CXX17)
   # set(CMAKE_CXX_STANDARD 17)
    message("Have -std=c++17, use it")
endif()





ADD_SUBDIRECTORY(libs/SDL2)
ADD_SUBDIRECTORY(libs/SDL2_net)
ADD_SUBDIRECTORY(libs/glew)
ADD_SUBDIRECTORY(libs/glm)
 

set(SDL_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/libs/SDL2/include)
set(SDL_NET_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/libs/SDL2_net/include)
set ( GLEW_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/libs/glew/include )
set ( GLM_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/libs/glm)
 


file(GLOB SRC_LIST src/*.cpp src/*.h src/gui/*.c src/gui/*.cpp src/gui/*.h src/System/*.cpp src/System/*.h src/Render/*.cpp src/imgui/*.h src/imgui/*.cpp src/Render/*.h)

include_directories( ${SDL_INCLUDE_DIRS})
include_directories( ${GLM_INCLUDE_DIRS})
include_directories( ${SDL_NET_INCLUDE_DIRS})
include_directories( ${GLEW_INCLUDE_DIRS})
 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_FORCE_INLINES")








if(MINGW)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-std=c++11 -static -Wall  -O3")
#-mwindows



 #freetype

    add_executable(${PROJECT_NAME} ${SRC_LIST} ${PROJECT_SOURCE_DIR}/resources/icon.rc)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} mingw32 SDL2main SDL2-static SDL2_net  libglew_static ${OPENGL_LIBRARY} glm)
endif(MINGW)

if(MSVC)
   # set(EXECUTABLE_OUTPUT_PATH "binMSVS")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -mwindows -O3")

    add_executable(${PROJECT_NAME} ${SRC_LIST} ${PROJECT_SOURCE_DIR}/resources/icon.rc)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} SDL2main SDL2-static SDL2_net libglew_static ${OPENGL_LIBRARY})
endif(MSVC)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O3")

    add_executable(${PROJECT_NAME} ${SRC_LIST} ${PROJECT_SOURCE_DIR}/resources/icon.rc)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} SDL2-static SDL2_net libglew_static ${OPENGL_LIBRARY} )
endif(UNIX)







if (ANDROID)

    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
    set(EXECUTABLE_OUTPUT_PATH "binAndroid")


    include(${PROJECT_SOURCE_DIR}/src/android-project/cmake/android.cmake)
    include(${PROJECT_SOURCE_DIR}/src/android-project/cmake/macros.cmake)
    #add_definitions( -DGLES2=1 )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

    set( SDL_SHARED OFF CACHE BOOL "Build the shared SDL library" )
    set( SDL_SHARED OFF CACHE BOOL "Build the shared SDL library" )
    set( SDL_STATIC ON CACHE BOOL "Build a static version of the library" )
    set( SDL_AUDIO OFF CACHE BOOL "Audio" )
    set( VIDEO_OPENGLES ON CACHE BOOL  "Include OpenGL ES support")
    set(SDL_STATIC_PIC  ON CACHE BOOL  "Static version of the library should be built with Position Independent Code")

    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O3")
    ###############

    set(ANDROID_BIN_ROOT ${PROJECT_SOURCE_DIR}/build/bin-android)
    add_custom_target(android-install ${ANDROID_ANT} ${ANT_INSTALL_TARGET} WORKING_DIRECTORY ${ANDROID_BIN_ROOT})
    add_custom_target(android-backtrace ${ANDROID_ADB} logcat WORKING_DIRECTORY ${ANDROID_BIN_ROOT})
    add_custom_target(android-build ${ANDROID_ANT} ${ANT_FLAGS} ${ANT_TARGET} WORKING_DIRECTORY ${ANDROID_BIN_ROOT})
    add_custom_target(android-start ${ANDROID_ADB} shell am start -n org.libsdl.app/org.libsdl.app.SDLActivity WORKING_DIRECTORY ${ANDROID_BIN_ROOT})


    # add_library (${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/libs/SDL2-2.0.5/src/main/android/SDL_android_main.c ${SRC_LIST})
    #  target_link_libraries (game engine)
    set (${SRC_LIST} ${SRC_LIST} ${PROJECT_SOURCE_DIR}/libs/SDL2/src/main/android/SDL_android_main.c)

    message(STATUS ${SRC_LIST})
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} SDL2-static)

    # add_custom_command(TARGET game POST_BUILD COMMAND ${ANDROID_ANT} ${ANT_FLAGS} ${ANT_TARGET} WORKING_DIRECTORY ${ANDROID_BIN_ROOT})

    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/src/android-project/
        ${ANDROID_BIN_ROOT}/)

    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/src/image/
        ${ANDROID_BIN_ROOT}/image)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/ ${ANDROID_BIN_ROOT}/libs/${ANDROID_NDK_ABI_NAME})

    ##############

endif(ANDROID)




#--------------------------------------------------DOXYGEN-------------------------
#------------------------------------OPTIONS
option(BUILD_DOC "Build documentation" ON)

SET(DOXY_OUTPUT_LANGUAGE "Russian")
SET(DOXY_INPUT ${PROJECT_SOURCE_DIR}/src)
SET(DOXY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/documentation)
SET(DOXY_PROJECT_NAME ${PROJECT_NAME})
#------------OPTIONS-HTML
# Project section
#SET(DOXY_BRIEF_MEMBER_DESC "NO")

# HTML section
#SET(DOXY_HTML_HEADER  ${PROJECT_SOURCE_DIR}/doxygen/header.html)
#SET(DOXY_HTML_FOOTER  ${PROJECT_SOURCE_DIR}/doxygen/footer.html)
#SET(DOXY_HTML_STYLESHEET  ${PROJECT_SOURCE_DIR}/doxygen/qmi.css)


#-----------OPTIONS-HTML
if(BUILD_DOC)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)


        #------------------------------------MACROS----------------------------------------
        MACRO(CONFIGURE_DOXYGEN_FILE DOXYGEN_CONFIG_FILE FILE_NAME_SUFFIX)
        IF(EXISTS ${PROJECT_SOURCE_DIR}/${DOXYGEN_CONFIG_FILE})
        FILE(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/doxy-${FILE_NAME_SUFFIX}.conf)
        FILE(READ ${PROJECT_SOURCE_DIR}/${DOXYGEN_CONFIG_FILE} DOXYFILE_CONTENTS)
        STRING(REGEX REPLACE ";" "\\\\;" DOXYFILE_CONTENTS "${DOXYFILE_CONTENTS}")
        STRING(REGEX REPLACE "\n" ";" DOXYFILE_LINES "${DOXYFILE_CONTENTS}")
        LIST(LENGTH DOXYFILE_LINES ROW)
        MATH(EXPR ROW "${ROW} - 1")
        FOREACH(I RANGE ${ROW})
        LIST(GET DOXYFILE_LINES ${I} LINE)
        IF(LINE STRGREATER "")
        STRING(REGEX MATCH "^[a-zA-Z]([^ ])+" DOXY_PARAM ${LINE})
        IF(DEFINED DOXY_${DOXY_PARAM})
        STRING(REGEX REPLACE "=([^\n])+" "= ${DOXY_${DOXY_PARAM}}" LINE ${LINE})
        ENDIF(DEFINED DOXY_${DOXY_PARAM})
        ENDIF()
        FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/doxy-${FILE_NAME_SUFFIX}.conf "${LINE}\n")
        ENDFOREACH()
        ELSE()
        MESSAGE(SEND_ERROR "Doxygen configuration file '${DOXYGEN_CONFIG_FILE}' not found. Documentation will not be generated")
        ENDIF()
        ENDMACRO(CONFIGURE_DOXYGEN_FILE)

        MACRO(ADD_DOCUMENTATION TARGET DOXYGEN_CONFIG_FILE)
        FIND_PACKAGE(Doxygen)
        IF(DOXYGEN_FOUND)
        CONFIGURE_DOXYGEN_FILE(${DOXYGEN_CONFIG_FILE} ${TARGET})
        ADD_CUSTOM_TARGET(${TARGET} COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxy-${TARGET}.conf)
        ELSE(DOXYGEN_FOUND)
        MESSAGE(STATUS "Doxygen not found. Documentation will not be generated")
        ENDIF(DOXYGEN_FOUND)
        ENDMACRO(ADD_DOCUMENTATION)
        #------------------------------------MACROS----------------------------------------



        message("Doxygen start building docummentation")
        ADD_DOCUMENTATION(doc Doxyfile)

    else (DOXYGEN_FOUND)
        message("Doxygen need to be installed to generate the doxygen documentation")
    endif (DOXYGEN_FOUND)
endif (BUILD_DOC)
execute_process( COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxy-doc.conf)


