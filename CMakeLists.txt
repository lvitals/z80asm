# Minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(z80asm VERSION 1.9 LANGUAGES C)

# Global configurations
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O2")

# Common include directories
include_directories(include)

# Detect operating system and configure specific paths
if(APPLE)
    # Automatically find the gettext include directory
    find_path(GETTEXT_INCLUDE_DIR 
        NAMES libintl.h
        HINTS /opt/homebrew/opt/gettext/include /usr/local/include /usr/include
    )
    
    if(GETTEXT_INCLUDE_DIR)
        include_directories(${GETTEXT_INCLUDE_DIR})
    else()
        message(FATAL_ERROR "libintl.h not found! Please install gettext.")
    endif()
    
    # Automatically find the intl library
    find_library(LIBINTL_LIBRARY 
        NAMES intl
        HINTS /opt/homebrew/opt/gettext/lib /usr/local/lib /usr/lib
    )
    
elseif(UNIX)
    find_package(Intl REQUIRED) # Try to find libintl automatically on Linux
    if(Intl_FOUND)
        message(STATUS "Found libintl: ${Intl_LIBRARIES}")
        set(LIBINTL_LIBRARY ${Intl_LIBRARIES})
    else()
        find_library(LIBINTL_LIBRARY 
            NAMES intl
            HINTS /usr/lib /usr/local/lib /usr/lib/x86_64-linux-gnu
        )
    endif()
endif()

# Check if the library was found
if(NOT LIBINTL_LIBRARY)
    message(FATAL_ERROR "The libintl library was not found!")
else()
    message(STATUS "Using libintl at: ${LIBINTL_LIBRARY}")
endif()

# Define localization and data directories
set(LOCALEDIR "/usr/local/share/locale")
set(PKGDATADIR "/usr/local/share/z80asm")

# Add subdirectories
add_subdirectory(src)  # The z80asm target is created here
add_subdirectory(compat)
add_subdirectory(doc)
add_subdirectory(data)
add_subdirectory(examples)

# Apply compile definitions to the z80asm target
# Now that the z80asm target exists, we can use target_compile_definitions
target_compile_definitions(z80asm PRIVATE -DLOCALEDIR="${LOCALEDIR}")
target_compile_definitions(z80asm PRIVATE -DPKGDATADIR="${PKGDATADIR}")

# Configurations for gettext
find_program(GETTEXT_XGETTEXT_EXECUTABLE xgettext)
find_program(GETTEXT_MSGFMT_EXECUTABLE msgfmt)

if(GETTEXT_XGETTEXT_EXECUTABLE AND GETTEXT_MSGFMT_EXECUTABLE)
    # Generate .pot file
    file(GLOB_RECURSE SRC_FILES src/*.c)
    add_custom_command(
        OUTPUT ${CMAKE_SOURCE_DIR}/po/z80asm.pot
        COMMAND ${GETTEXT_XGETTEXT_EXECUTABLE} --from-code=UTF-8 -k_ -o ${CMAKE_SOURCE_DIR}/po/z80asm.pot ${SRC_FILES}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating .pot file"
    )

    # Read languages from the LINGUAS file
    file(STRINGS ${CMAKE_SOURCE_DIR}/po/LINGUAS LANGUAGES)
    list(FILTER LANGUAGES EXCLUDE REGEX "^#.*$")  # Ignore comment lines
    list(FILTER LANGUAGES EXCLUDE REGEX "^$")     # Ignore empty lines

    # Compile .po files into .mo files
    foreach(LANG ${LANGUAGES})
        set(PO_FILE ${CMAKE_SOURCE_DIR}/po/${LANG}.po)
        set(MO_FILE ${CMAKE_SOURCE_DIR}/po/${LANG}.mo)
        add_custom_command(
            OUTPUT ${MO_FILE}
            COMMAND ${GETTEXT_MSGFMT_EXECUTABLE} -o ${MO_FILE} ${PO_FILE}
            DEPENDS ${PO_FILE}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Compiling translation for ${LANG}"
        )
        list(APPEND MO_FILES ${MO_FILE})
    endforeach()

    # Add target to generate .pot and .mo files
    add_custom_target(translations ALL DEPENDS ${CMAKE_SOURCE_DIR}/po/z80asm.pot ${MO_FILES})
else()
    message(WARNING "gettext tools (xgettext and msgfmt) not found. Translations will not be generated.")
endif()

# Installation of the z80asm executable
install(TARGETS z80asm
    RUNTIME DESTINATION bin
)

# Installation of translations (.mo files)
foreach(LANG ${LANGUAGES})
    install(FILES ${CMAKE_SOURCE_DIR}/po/${LANG}.mo
        DESTINATION ${LOCALEDIR}/${LANG}/LC_MESSAGES
        RENAME z80asm.mo
    )
endforeach()

# Installation of data files
install(DIRECTORY ${CMAKE_SOURCE_DIR}/data/
    DESTINATION ${PKGDATADIR}
    FILES_MATCHING PATTERN "*.asm"
)

# Installation of documentation
install(FILES ${CMAKE_SOURCE_DIR}/doc/man/z80asm.1
    DESTINATION share/man/man1
)

# Enable testing
enable_testing()

# Z80 assembler executable
set(Z80ASM "${CMAKE_BINARY_DIR}/src/z80asm")

# Directory where .asm files are located
set(ASM_DIR "${CMAKE_SOURCE_DIR}/data/headers")

# List of .asm files to compile and verify
set(ASM_FILES
    pass.asm
    patch9377.asm
    bug26772.asm
    bug47653.asm
    bug60151.asm
    bug55596.asm
)

# Add custom target for each .asm file
foreach(ASM_FILE ${ASM_FILES})
    # Base name without extension
    get_filename_component(BASE_NAME ${ASM_FILE} NAME_WE)

    # Output files
    set(BIN_FILE "${BASE_NAME}.bin")
    set(ACTUAL_ERR_FILE "${BASE_NAME}.actual-err")

    # Custom command to compile and verify
    add_custom_command(
        OUTPUT ${BIN_FILE} ${ACTUAL_ERR_FILE}
        COMMAND ${Z80ASM} -I ${ASM_DIR} ${ASM_FILE} -o ${BIN_FILE} 2> ${ACTUAL_ERR_FILE}
        COMMAND ${CMAKE_COMMAND} -E compare_files ${BASE_NAME}.correct-bin ${BIN_FILE}
        COMMAND ${CMAKE_COMMAND} -E compare_files ${BASE_NAME}.correct-err ${ACTUAL_ERR_FILE}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
        COMMENT "Compiling and verifying ${ASM_FILE}"
    )

    # Add custom target for the test
    add_custom_target(${BASE_NAME}_test ALL DEPENDS ${BIN_FILE} ${ACTUAL_ERR_FILE})

    # Add test to CTest
    add_test(
        NAME ${BASE_NAME}_test
        COMMAND ${CMAKE_COMMAND} -E compare_files ${BASE_NAME}.correct-bin ${BIN_FILE}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
    )
    add_test(
        NAME ${BASE_NAME}_err_test
        COMMAND ${CMAKE_COMMAND} -E compare_files ${BASE_NAME}.correct-err ${ACTUAL_ERR_FILE}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
    )
endforeach()