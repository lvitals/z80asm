;;; These bugs are still not fixed:
bug47653:
	dec (ix)		; shoud assemble to dd 35 00 as dec (ix+0)

bug31030:	
	nop cp (ix) ; similar problem, should not segfault and assemble to cp (ix+0) with a warning - disabled for now since it produces garbage
