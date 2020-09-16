lw $8, 0($23) 
addi $2, $0, 1 
addi $3, $0, 25 
loop:beq $2, $3, end	
lw $4, 0($8)   
add $4, $0, $0  
sw $4, 0($8)   
addi $8, $8, 4  
addi $2, $2, 1  
j loop
end: add $24, $0, $0


