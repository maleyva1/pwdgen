cmake_minimum_required(VERSION 3.8)

project(PasswordGenerator
        VERSION 1.0
        LANGUAGES C
)

add_executable(pwdgen)

set(GNULIB "../gnulib/lib")

target_sources(pwdgen PRIVATE
        "src/main.c"
        "src/pw.c"
#        "${GNULIB}/argp-ba.c"
#        "${GNULIB}/argp-eexst.c"
#        "${GNULIB}/argp-fmtstream.c"
#        "${GNULIB}/argp-fmtstream.h"
#        "${GNULIB}/argp-fs-xinl.c"
#        "${GNULIB}/argp-help.c"
#        "${GNULIB}/argp-namefrob.h"
#        "${GNULIB}/argp-parse.c"
#        "${GNULIB}/argp-pin.c"
#        "${GNULIB}/argp-pv.c"
#        "${GNULIB}/argp-pvh.c"
#        "${GNULIB}/argp-version-etc.c"
#        "${GNULIB}/argp-version-etc.h"
#        "${GNULIB}/argp-xinl.c"
)

target_include_directories(pwdgen BEFORE PRIVATE 
        "inc"
        "${GNULIB}"
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