

add_executable(
    ${PROJ_NAME}
    main.cc
    task.cc
    reactor.cc
)

set(CMAKE_BUILD_TYPE Debug)

set_property(
    TARGET 
        ${PROJ_NAME}
    PROPERTY 
        CXX_STANDARD 23
)

