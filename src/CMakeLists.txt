file(
        GLOB_RECURSE
        sources
        ${CMAKE_SOURCE_DIR}/src/*.cpp
)

add_executable(app ${sources})

target_link_libraries (app ${CMAKE_THREAD_LIBS_INIT})

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/app
    DESTINATION bin
    RENAME ${CMAKE_PROJECT_NAME}-app)

