; macro.asm - usage of macros
; Copyright 2005 Bas Wijnen <wijnen@debian.org>
;
; This file is part of z80asm.
;
; Z80asm is free software; you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation; either version 3 of the License, or
; (at your option) any later version.
;
; Z80asm is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with this program.  If not, see <http://www.gnu.org/licenses/>.

	include "msx-bios.asm"

; Cartridge programs need to start at 0x4000
	org 0x4000

; header to make this a cartridge
	db "AB"
	dw start

; macro definition
print:	macro string
	ld hl, string
; this label (and .finish) must be local to prevent duplicate definitions
; when the macro is used more than once.
.start:	ld a, (hl)
	and a
	jr z, .finish
	call CHPUT
	inc hl
	jr .start
.finish:endm

; Call the macros
start:	print text
	print text2
; Stop doing things
	di
loop:	halt
	jr loop

; The text strings
text:	db "This is some text\r\n", 0
text2:	db "This is some more text\r\n", 0

; Fill up the rest of the page
	ds 0x8000 - $
