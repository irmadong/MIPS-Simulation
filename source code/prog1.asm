add	$10, $8, $9
add     $12, $11, $12
sub     $14, $13, $14
sub     $30, $28, $29
addi    $15, $15, 301
slt     $16, $16, $0
slt     $17, $0, $0
lw	$18, -8($19)
lw      $19, 0($19)
sw 	$18, 4($19)
sw      $19, -12($19)
j 0x40003c
add	$3, $4, $8
addi $1, $1, -1
beq $0, $20, 0x40044
sub $20, $0, $0 # $20 gets value 0
j 0x4000044
add $22, $0, $0
