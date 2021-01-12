cmake_minimum_required(VERSION 3.0)
project(Gamma C)
include(CTest)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif ()

# We want to see the compilation progress messages.
set_property(GLOBAL PROPERTY RULE_MESSAGES ON)

# We want make messages
set(CMAKE_VERBOSE_MAKEFILE ON)

# Common options for all projects
set(CMAKE_C_FLAGS "-std=c11 -Wall -Wextra")
# Default options for Release and Debug are good
# If needed set them below
# set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
# set(CMAKE_C_FLAGS_DEBUG "-g")

include_directories(src)

# Wskazujemy pliki źródłowe.
set(SOURCE_FILES
        src/gamma.c
        src/gamma.h
        src/moves.c
        src/moves.h
        src/memory.c
        src/memory.h
        src/print.c
        src/print.h
        src/board.c
        src/board.h
        src/queue.c
        src/queue.h
        src/types.c
        src/types.h
        src/interactive.c
        src/interactive.h
        src/batch.h
        src/batch.c
        )

add_executable(gamma_test ${SOURCE_FILES} src/gamma_test.c)
add_executable(gamma_test_full ${SOURCE_FILES} src/gamma_test_full.c)
add_executable(gamma ${SOURCE_FILES} src/gamma_main.c)

# Dodajemy obsługę Doxygena: sprawdzamy, czy jest zainstalowany i jeśli tak to:
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # Wskazujemy lokalizacją pliku konfiguracyjnego i podajemy jego docelową lokalizację w folderze, gdzie następuje kompilacja.
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    # Dodajemy cel doc: użycie make doc spowoduje wywołanie doxygena z odpowiednim plikiem konfiguracyjnym w folderze kompilacji.
    # Na wyjście zostanie wypisany odpowiedni komentarz.
    add_custom_target(doc
            ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            )
endif (DOXYGEN_FOUND)
