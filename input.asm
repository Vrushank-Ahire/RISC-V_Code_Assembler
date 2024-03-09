.text
and x4, x6, x2

Label1:
and    x3, x6, x0
jal x1, Label2
or    x3, x6, x0
sll    x3, x6, x0
slt    x3, x6, x0
jalr x0, 0(x1)

Label2:
sra    x3, x6, x0

srl    x3, x6, x0

sub    x3, x6, x0


xor    x3, x6, x0

mul    x3, x6, x0

rem    x3, x6, x0

.text

andi x1, x1, 42
addi x1, x1, 42

ori x1, x1, 42


lb x3, 23(x4)
ld x5, 235(x4)
lh x5, 235(x4)

lw x4, 827(x6)

jalr x9, 2(x1)

.text
beq x0, x0, Label1
bne x0, x0, Label1
bge x0, x0, Label1
blt x0, x0, Label1

auipc x4, 432
lui x6, 423
jal x1, Label1
