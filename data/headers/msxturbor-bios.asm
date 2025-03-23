; msxturbor-bios.asm - BIOS calls for the MSX computer
; Copyright 2005  Bas Wijnen <wijnen@debian.org>
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

	include 'msx2+-bios.asm'
CHGCPU:	equ 0x0180
GETCPU:	equ 0x0183
PCMPLY:	equ 0x0186
PCMREC:	equ 0x0189
