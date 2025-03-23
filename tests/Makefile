# Compilador Z80
Z80ASM = ../build/src/z80asm

# Diretório onde os arquivos .asm estão localizados
ASM_DIR = ../data/headers

# Lista de arquivos .asm para compilar e verificar
ASM_FILES = pass.asm patch9377.asm bug26772.asm bug47653.asm bug60151.asm bug55596.asm

# Regra padrão: compila e verifica todos os arquivos .asm
all: $(ASM_FILES:.asm=.check)

# Regra para compilar e verificar cada arquivo .asm
%.check: %.asm
	@echo "Compilando e verificando $<..."
	@$(Z80ASM) -I $(ASM_DIR) $< -o $(basename $<).bin 2> $(basename $<).actual-err
	@echo "Verificando $(basename $<).bin..."
	@diff $(basename $<).correct-bin $(basename $<).bin && echo "$(basename $<).bin está correto." || echo "Erro: $(basename $<).bin não corresponde ao esperado."
	@echo "Verificando $(basename $<).actual-err..."
	@diff $(basename $<).correct-err $(basename $<).actual-err && echo "$(basename $<).actual-err está correto." || echo "Erro: $(basename $<).actual-err não corresponde ao esperado."
	@rm -f $(basename $<).bin $(basename $<).actual-err

# Regra para limpar os arquivos gerados
clean:
	@rm -f *.bin *.actual-err

# Regra para exibir ajuda
help:
	@echo "Uso: make [all|clean|help]"
	@echo "  all: Compila e verifica todos os arquivos .asm (padrão)."
	@echo "  clean: Remove todos os arquivos gerados."
	@echo "  help: Exibe esta mensagem de ajuda."

.PHONY: all clean help