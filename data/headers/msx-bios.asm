; msx-bios.asm - BIOS calls for the MSX computer
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

CHKRAM:	equ 0x0000
SYNCHR:	equ 0x0008
RDSLT:	equ 0x000C
CHRGTR:	equ 0x0010
WRSLT:	equ 0x0014
OUTDO:	equ 0x0018
CALSLT:	equ 0x001C
DCOMPR:	equ 0x0020
ENASLT:	equ 0x0024
GETYPR:	equ 0x0028
CALLF:	equ 0x0030
KEYINT:	equ 0x0038
INITIO:	equ 0x003B
INIFNK:	equ 0x003E
DISSCR:	equ 0x0041
ENASCR:	equ 0x0044
WRTVDP:	equ 0x0047
RDVRM:	equ 0x004A
WRTVRM:	equ 0x004D
SETRD:	equ 0x0050
SETWRT:	equ 0x0053
FILVRM:	equ 0x0056
LDIRMV:	equ 0x0059
LDIRVM:	equ 0x005C
CHGMOD:	equ 0x005F
CHGCLR:	equ 0x0062
NMI:	equ 0x0066
CLRSPR:	equ 0x0069
INITXT:	equ 0x006C
INIT32:	equ 0x006F
INIGRP:	equ 0x0072
INIMLT:	equ 0x0075
SETTXT:	equ 0x0078
SETT32:	equ 0x007B
SETGRP:	equ 0x007E
SETMLT:	equ 0x0081
CALPAT:	equ 0x0084
CALATR:	equ 0x0087
GSPSIZ:	equ 0x008A
GRPPRT:	equ 0x008D
GICINI:	equ 0x0090
WRTPSG:	equ 0x0093
RDPSG:	equ 0x0096
STRTMS:	equ 0x0099
CHSNS:	equ 0x009C
CHGET:	equ 0x009F
CHPUT:	equ 0x00A2
LPTOUT:	equ 0x00A5
LPTSTT:	equ 0x00A8
CNVCHR:	equ 0x00AB
PINLIN:	equ 0x00AE
INLIN:	equ 0x00B1
QINLIN:	equ 0x00B4
BREAKX:	equ 0x00B7
ISCNTC:	equ 0x00BA
CKCNTC:	equ 0x00BD
BEEP:	equ 0x00C0
CLS:	equ 0x00C3
POSIT:	equ 0x00C6
FNKSB:	equ 0x00C9
ERAFNK:	equ 0x00CC
DSPFNK:	equ 0x00CF
TOTEXT:	equ 0x00D2
GTSTCK:	equ 0x00D5
GTTRIG:	equ 0x00D8
GTPAD:	equ 0x00DB
GTPDL:	equ 0x00DE
TAPION:	equ 0x00E1
TAPIN:	equ 0x00E4
TAPIOF:	equ 0x00E7
TAPOON:	equ 0x00EA
TAPOUT:	equ 0x00ED
TAPOOF:	equ 0x00F0
STMOTR:	equ 0x00F3
LFTQ:	equ 0x00F6
PUTQ:	equ 0x00F9
RIGHTC:	equ 0x00FC
LEFTC:	equ 0x00FF
UPC:	equ 0x0102
TUPC:	equ 0x0105
DOWNC:	equ 0x0108
TDOWNC:	equ 0x010B
SCALXY:	equ 0x010E
MAPXY:	equ 0x0111
FETCHC:	equ 0x0114
STOREC:	equ 0x0117
SETATR:	equ 0x011A
READC:	equ 0x011D
SETC:	equ 0x0120
NSETCX:	equ 0x0123
GTASPC:	equ 0x0126
PNTINI:	equ 0x0129
SCANR:	equ 0x012C
SCANL:	equ 0x012F
CHGCAP:	equ 0x0132
CHGSND:	equ 0x0135
RSLREG:	equ 0x0138
WSLREG:	equ 0x013B
RDVDP:	equ 0x013E
SNSMAT:	equ 0x0141
PHYDIO:	equ 0x0144
FORMAT:	equ 0x0147
ISFLIO:	equ 0x014A
OUTDLP:	equ 0x014D
GETVCP:	equ 0x0150
GETVC2:	equ 0x0153
KILBUF:	equ 0x0156
CALBAS:	equ 0x0159
