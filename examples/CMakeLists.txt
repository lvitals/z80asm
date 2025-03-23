# Define o caminho para o executável z80asm
set(Z80ASM ${CMAKE_BINARY_DIR}/src/z80asm)

# Define o diretório de inclusão para cabeçalhos
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/data/headers)

# Lista de exemplos a serem compilados
set(EXAMPLES
    hello.asm
    macro.asm
)

# Regra para compilar cada exemplo
foreach(example ${EXAMPLES})
    # Extrai o nome base do arquivo (sem extensão)
    get_filename_component(example_name ${example} NAME_WE)

    # Define o comando para compilar o exemplo
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${example_name}.rom
        COMMAND ${CMAKE_BINARY_DIR}/src/z80asm ${CMAKE_CURRENT_SOURCE_DIR}/${example} -I ${INCLUDE_DIR} -o ${CMAKE_CURRENT_BINARY_DIR}/${example_name}.rom
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${example} z80asm
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Compiling ${example} to ${example_name}.rom"
    )

    # Adiciona um alvo para o exemplo
    add_custom_target(${example_name} ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${example_name}.rom)
endforeach()

# Alvo para limpar os arquivos gerados
add_custom_target(clean_examples
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_CURRENT_BINARY_DIR}/*.rom
    COMMENT "Cleaning up generated .rom files"
)