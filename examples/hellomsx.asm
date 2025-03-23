; Hello World para MSX-DOS
; Copyright 2023 Leandro Vital Catarin
;
; Este programa exibe "Hello, World!" no MSX-DOS.
;
; Compilar com z80asm:
; z80asm hellomsx.asm -o hellomsx.com

    org 0x0100      ; MSX-DOS programas começam em 0x0100

    ; Cabeçalho do programa MSX-DOS
    db 0xFE          ; Byte de identificação do MSX-DOS
    dw start         ; Endereço de início do programa
    dw 0             ; Endereço de término do programa (não usado)
    dw 0             ; Endereço de inicialização (não usado)
    dw 0             ; Endereço de término (não usado)

start:
    ; Exibe a mensagem "Hello, World!" na tela
    ld de, message   ; Carrega o endereço da mensagem em DE
    ld c, 9          ; Código da função "Print String" do MSX-DOS
    call 5           ; Chama a função do MSX-DOS

    ; Retorna ao MSX-DOS
    ret

message:
    db "Hello, World!", 0x0D, 0x0A, "$"  ; Mensagem + CR/LF + terminador $
