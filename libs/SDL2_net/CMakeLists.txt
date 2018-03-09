project(SDL2_net C)
set(SOURCES SDLnet.c SDLnetselect.c SDLnetTCP.c SDLnetUDP.c)
set(HEADERS SDL_net.h SDLnetsys.h)
set(SDL_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/libs/SDL2/include)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_FORCE_INLINES")
include_directories( ${SDL_INCLUDE_DIRS})
add_library(SDL2_net STATIC ${SOURCES} ${HEADERS} )
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC SDL2-static)

