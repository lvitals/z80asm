#!/bin/bash
set -x 

# Diretório onde os arquivos .asm estão localizados
ASM_DIR="../data/headers"
Z80ASM="../build/src/z80asm"

# Função para compilar e verificar os arquivos
compile_and_check() {
    local asm_file=$1
    local base_name=$(basename "$asm_file" .asm)

    echo "Compilando $asm_file..."
    $Z80ASM -I "$ASM_DIR" "$asm_file" -o "$base_name.bin" 2> "$base_name.actual-err"

    echo "Verificando $base_name.bin..."
    diff "$base_name.correct-bin" "$base_name.bin"
    if [ $? -eq 0 ]; then
        echo "$base_name.bin está correto."
    else
        echo "Erro: $base_name.bin não corresponde ao esperado."
    fi

    echo "Verificando $base_name.actual-err..."
    diff "$base_name.correct-err" "$base_name.actual-err"
    if [ $? -eq 0 ]; then
        echo "$base_name.actual-err está correto."
    else
        echo "Erro: $base_name.actual-err não corresponde ao esperado."
    fi

    # Limpeza
    rm "$base_name.bin" "$base_name.actual-err"
}

# Lista de arquivos .asm para compilar e verificar
asm_files=(
    "pass.asm"
    "patch9377.asm"
    "bug26772.asm"
    "bug47653.asm"
    "bug60151.asm"
    "bug55596.asm"
)

# Executa a compilação e verificação para cada arquivo
for asm_file in "${asm_files[@]}"; do
    compile_and_check "$asm_file"
done

echo "Todos os testes foram concluídos."