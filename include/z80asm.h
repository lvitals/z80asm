/* Z80 assembler by shevek

   Copyright (C) 2002-2007 Bas Wijnen <shevek@fmf.nl>
   Copyright (C) 2005 Jan Wilmans <jw@dds.nl>

   This file is part of z80asm.

   Z80asm is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   Z80asm is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef Z80ASM_H
#define Z80ASM_H

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <stdarg.h>
#include <unistd.h>

#include "files.h"
#include "error.h"
#include "label.h"
#include "macro.h"
#include "reference.h"

/* types */
/* mnemonics. THESE MUST BE IN THE SAME ORDER AS const char *mnemonic[]! */
enum mnemonic
{
  CALL, CPDR, CPIR, DJNZ, HALT, INDR, INIR, LDDR, LDIR, OTDR, OTIR, OUTD,
  OUTI, PUSH, RETI, RETN, RLCA, RRCA, DEFB, DEFW, DEFS, DEFM,
  ADC, ADD, AND, BIT, CCF, CPD, CPI, CPL, DAA, DEC, EQU, EXX, INC, IND, INI,
  LDD, LDI, NEG, NOP, OUT, POP, RES, RET, RLA, RLC, RLD, RRA, RRC, RRD, RST,
  SBC, SCF, SET, SLA, SLL, SLI, SRA, SRL, SUB, XOR, ORG,
  CP, DI, EI, EX, IM, IN, JP, JR, LD, OR, RL, RR, DB, DW, DS, DM,
  INCLUDE, INCBIN, IF, ELSE, ENDIF, END, MACRO, ENDM, SEEK
};


/* global variables */
/* mnemonics, used as argument to indx() in assemble */
extern const char *mnemonics[];

/* linked lists */
extern struct reference *firstreference;
extern struct label *firstlabel, *lastlabel;
extern struct name *firstname;
extern struct macro *firstmacro;

/* current line, address and file */
extern int addr, file;
/* current number of characters in list file, for indentation */
extern int listdepth;

/* use readbyte instead of (hl) if writebyte is true */
extern int writebyte;
extern const char *readbyte;
/* variables which are filled by rd_* functions and used later,
 * like readbyte */
extern const char *readword, *indexjmp, *bitsetres;

/* 0, 0xdd or 0xfd depening on which index prefix should be given */
extern int indexed;

/* read commas after indx() if comma > 1. increase for every call */
extern int comma;

/* address at start of line (for references) */
extern int baseaddr;

/* set by readword and readbyte, used for new_reference */
extern char mem_delimiter;

/* line currently being parsed */
extern char *buffer;

/* if a macro is currently being defined */
extern int define_macro;

/* Produce output even with errors.  */
extern int use_force;

/* skip over spaces in string */
const char *delspc (const char *ptr);

int rd_expr (const char **p, char delimiter, int *valid, int level,
	     int print_errors);
int rd_label (const char **p, int *exists, struct label **previous, int level,
	      int print_errors);
int rd_character (const char **p, int *valid, int print_errors);

int compute_ref (struct reference *ref, int allow_invalid);

extern void assemble(void);

#endif
