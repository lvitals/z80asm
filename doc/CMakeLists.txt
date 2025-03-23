# Adiciona o subdiretório 'man' (se existir)
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/man/CMakeLists.txt)
    add_subdirectory(man)
endif()