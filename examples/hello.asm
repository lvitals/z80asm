; Hello world.  Load as a cartridge in openmsx.  (openmsx hello.rom)
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

	include 'msx-bios.asm'	; symbolic names for bios calls
	; header for a rom
	org 0x4000
	db "AB"
	dw start
text:	db "This is the source which generated this program:\r\n"
	incbin 'hello.asm'
	db 0
start:	ld a, 80
	ld (0xf3ae), a	; width 80
	xor a
	call CHGMOD	; screen 0
	ld hl, text
loop:	ld a, (hl)
	and a		; set the z flag if A is 0
	jr z,stop	; and return in that case
	call CHPUT
	inc hl
	jr loop
stop:	jr stop
	ds 0x8000 - $	; fill up the rest of the page
