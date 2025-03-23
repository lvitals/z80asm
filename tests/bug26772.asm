;;; These bugs are fixed and should assemble correctly now
bug26772:
x:	macro arg
	db arg
	endm

	org 0x8000
	x 'mld ' 		; macro should handle string arg correctly

