.text
addi x1, x2, 10
add x3, x4, x5

.data
variable1: .word 123
variable2: .byte 'a', 'b', 'c', 'd', 'e'
string2: .asciiz "This is a test"

.text
sub x6, x7, x8
slt x9, x10, x11

.data
array1: .word 10, 20, 30, 40, 50
string1: .asciiz "Hello, World!"
array2: .byte 1, 2, 3, 4, 5

.text
beq x12, x13, label1
bne x14, x15, label2

.data
array3: .half 100, 200, 300, 400, 500
variable3: .word 999
array4: .word 55, 66, 77, 88, 99

.text
jal label3
lw x16, 0(x17)

.data
string3: .asciiz "RISC-V Assembly"
array5: .half 123, 456, 789
variable4: .byte 'x', 'y', 'z'

.text
sw x18, 4(x19)
lb x20, 8(x21)
sb x22, 12(x23)

.data
array6: .word 11, 22, 33, 44, 55
string4: .asciiz "Welcome to RISC-V"

.text
lbu x24, 16(x25)
sbu x26, 20(x27)

.data
array7: .byte 6, 7, 8, 9, 10
variable5: .word 987
array8: .half 333, 444, 555, 666, 777

.text
lui x28, 0x1000
auipc x29, 0x2000

.data
array9: .word 111, 222, 333, 444, 555
string5: .asciiz "Programming is fun!"

.text
jalr x30, x31, 0
jr x0
j label4
