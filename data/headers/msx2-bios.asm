; msx2-bios.asm - BIOS calls for the MSX computer
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

	include 'msx-bios.asm'
SUBROM:	equ 0x015C
EXTROM:	equ 0x015F
CHKSLZ:	equ 0x0162
CHKNEW:	equ 0x0165
EOL:	equ 0x0168
BIGFIL:	equ 0x016B
NSETRD:	equ 0x016E
NSTWRT:	equ 0x0171
NRDVRM:	equ 0x0174
NWRVRM:	equ 0x0177
