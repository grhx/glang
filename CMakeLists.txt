cmake_minimum_required(VERSION 3.24)
project(glang C)

# cmake standards
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# platform
if (WIN32)
    set(PLATFORM_WINDOWS true)
else()
    set(PLATFORM_WINDOWS false)
endif()
if (UNIX)
    set(PLATFORM_UNIX true)
else()
    set(PLATFORM_UNIX false)
endif()

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# LLVM

# Base
set(BASE_SRC

    src/base/alloc.c
    src/base/atof.c
    src/base/atoi.c
    src/base/color.c
    src/base/file.c
    src/base/format.c
    src/base/hash_map.c
    src/base/hash_set.c
    src/base/itoa.c
    src/base/optional.c
    src/base/stack.c
    src/base/str.c  
    src/base/string.c
    src/base/test.c
    src/base/vec.c

)

# CLI
set(CLI_SRC

    src/cli/option.c
    src/cli/option/build.c
    src/cli/parse_command.c
    src/cli/parse_config.c

)

# Command
set(COMMAND_SRC

    src/command/run/run.c

)


# Core
set(CORE_SRC

    # GLANG #
    src/core/g/analysis.c
    src/core/g/ast.c 
    src/core/g/checked.c
    src/core/g/error.c
    src/core/g/ir.c 
    src/core/g/package.c
    src/core/g/parser.c
    src/core/g/precompile.c
    src/core/g/preparser.c
    src/core/g/scanner.c
    src/core/g/token.c
    src/core/g/visibility.c
    src/core/g/warning.c
    # /ast
    # /checked
    # /ir
    # /package

    # CC #

    # CPP #

    # SHARED #

)


# glang libs
add_library(g_base STATIC ${BASE_SRC})
target_include_directories(g_base PUBLIC include)

add_library(g_cli STATIC ${CLI_SRC})
target_link_libraries(g_cli g_base)

#add_library(g_command STATIC ${COMMMAND_SRC})
#target_link_libraries(g_command g_base g_cli g_core)

add_library(g_core STATIC ${CORE_SRC})
target_link_libraries(g_core g_base)
target_include_directories(g_core PUBLIC lib/local)

# exec & libs
add_executable(${PROJECT_NAME} src/bin/main.c)
target_link_libraries(${PROJECT_NAME}

    g_base
    g_cli

)