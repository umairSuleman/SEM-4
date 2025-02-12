	AREA RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors 
	DCD 0x40001000 ; stack pointer value when stack is empty
	DCD Reset_Handler ; reset vector
	ALIGN
	AREA ascend, code, readonly
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	mov r4, #0          ; Initialize r4 (index register) to 0
	mov r1, #10         ; Set r1 to 10 (number of elements in the list)
	ldr r0, =list       ; Load the address of the input list into r0
	ldr r2, =result     ; Load the address of the result array into r2
up 
	ldr r3, [r0, r4]    ; Load the value at address [r0 + r4] into r3
	str r3, [r2, r4]    ; Store the value in r3 into the result array at [r2 + r4]
	add r4, #4          ; Increment r4 by 4 (move to the next word in the array)
	sub r1, #1          ; Decrement r1 (element counter) by 1
	cmp r1, #0          ; Compare r1 with 0
	bhi up     	; Branch to "up" if r1 > 0 (loop until all elements are copied)
	
	ldr r0, =result     ; Load the address of the result array into r0
	mov r3, #10         ; Set r3 to 10 (number of elements)
	sub r3, r3, #1      ; Decrement r3 by 1 (number of passes = n-1)
	mov r9, r3          ; Store the number of passes in r9
				; outer loop counter
outer_loop
	mov r5, r0          ; Copy the base address of the result array to r5
	mov r4, r3          ; Set r4 to the number of comparisons in the current pass

inner_loop
	ldr r6, [r5], #4    ; Load the value at [r5] into r6 and increment r5 by 4
	ldr r7, [r5]        ; Load the next value into r7
	cmp r7, r6          ; Compare r7 and r6
	strls r6, [r5]      ; If r7 <= r6, store r6 at [r5] (swap)
	strls r7, [r5, #-4] ; If r7 <= r6, store r7 at [r5 - 4] (swap)
	subs r4, r4, #1     ; Decrement the inner loop counter (r4)
	bne inner_loop      ; Branch to inner_loop if r4 != 0
	sub r3, #1          ; Decrement the number of comparisons for the next pass
	subs r9, r9, #1     ; Decrement the outer loop counter (r9)
	bne outer_loop      ; Branch to outer_loop if r9 != 0
	
list DCD 0x10,0x05,0x33,0x24,0x56,0x77,0x21,0x04,0x87,0x01
	AREA data1, data, readwrite
result DCW 0,0,0,0,0,0,0,0,0,0
	end