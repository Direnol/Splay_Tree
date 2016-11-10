set(SOURCE main.c splay.c)
set(HEADERS splay.h func.h)

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS})
