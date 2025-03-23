# Lista de arquivos fonte
set(COMPAT_FILES
    getopt.c
    getopt1.c
    malloc.c
    realloc.c
)

# Adicionar uma biblioteca estática
add_library(compat STATIC ${COMPAT_FILES})

# Incluir diretórios de cabeçalhos
target_include_directories(compat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Adicionar definições de compilação, se necessário
target_compile_definitions(compat PRIVATE HAVE_CONFIG_H)

# Linkar bibliotecas externas, se necessário
# target_link_libraries(compat ${LIBINTL_LIBRARY})