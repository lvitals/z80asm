emt: macro trap
rst 30h
defb trap
endm

org 0
emt 1
end