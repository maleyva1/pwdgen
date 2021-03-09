cmake_minimum_required(VERSION 3.8)

project(PasswordGenerator
        VERSION 1.0
        LANGUAGES C
)

add_executable(pwdgen)

target_sources(pwdgen PRIVATE
        "src/main.c"
        "src/pw.c"
)

target_include_directories(pwdgen BEFORE PRIVATE 
        "inc"
)

set(COMMON_FLAGS 
        -fsanitize=address
        -fsanitize=leak
        -Wall
        -pedantic
)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
        target_compile_options(pwdgen PRIVATE ${COMMON} -g)
else()
        target_compile_options(pwdgen PRIVATE ${COMMON} -O2)
endif()