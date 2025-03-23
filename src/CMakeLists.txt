# Lista de arquivos fonte
set(SRC_FILES
    main.c
    files.c
    stack.c
    z80asm.c
    expressions.c
    stringstore.c
    error.c
)

# Adicionar o executável
add_executable(z80asm ${SRC_FILES})

# Adicionar definições de compilação
target_compile_definitions(z80asm PRIVATE LOCALEDIR="${LOCALEDIR}")
target_compile_definitions(z80asm PRIVATE PKGDATADIR="${PKGDATADIR}")

# Linkar bibliotecas
target_link_libraries(z80asm ${LIBINTL_LIBRARY})