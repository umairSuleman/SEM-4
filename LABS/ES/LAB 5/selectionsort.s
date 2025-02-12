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

	; Copy Input List to Result Array
up
	ldr r3, [r0, r4]    ; Load the value at address [r0 + r4] into r3
	str r3, [r2, r4]    ; Store the value in r3 into the result array at [r2 + r4]
	add r4, #4          ; Increment r4 by 4 (move to the next word in the array)
	sub r1, #1          ; Decrement r1 (element counter) by 1
	cmp r1, #0          ; Compare r1 with 0
	bhi up              ; Branch to "up" if r1 > 0 (loop until all elements are copied)

	; Selection Sort Implementation
	ldr r0, =result     ; Load the address of the result array into r0
	mov r9, #0          ; Initialize outer loop counter (r9) to 0

outer_loop
	ldr r6, [r0, r9]    ; Initialize r6 with the value at [r0 + r9] (current ith element)
	mov r10, r9         ; Initialize r10 to r9 (index of the current ith element)
	mov r5, r9          ; Set r5 to the current index (r9)
	add r5, r5, #4      ; Start inner loop from outer_loop_counter + 1 (r5 = r9 + 4)
	mov r7, r5          ; Initialize r7 to r5 (inner loop counter starts from r9 + 1)

inner_loop
	ldr r3, [r0, r7]    ; Load the value at [r0 + r7] into r3
	cmp r3, r6          ; Compare r3 with the current minimum (r6)
	movlt r6, r3        ; If r3 < r6, update r6 to the new minimum
	movlt r10, r7       ; If r3 < r6, update r10 to the index of the new minimum
	add r7, r7, #4      ; Increment r7 by 4 (move to the next element)
	cmp r7, #40         ; Compare r7 with 40 (10 * 4, since there are 10 elements)
	blt inner_loop      ; Branch to inner_loop if r7 < 40

	; Swap the smallest element with the current ith element
	ldr r3, [r0, r9]    ; Load the value at [r0 + r9] into r3 (current ith element)
	ldr r4, [r0, r10]   ; Load the value at [r0 + r10] into r4 (minimum element)
	str r4, [r0, r9]    ; Store r4 at [r0 + r9] (swap minimum element to ith position)
	str r3, [r0, r10]   ; Store r3 at [r0 + r10] (swap ith element to minimum position)

	; Update outer loop counter
	add r9, r9, #4      ; Increment r9 by 4 (move to the next element)
	cmp r9, #36         ; Compare r9 with 36 (9 * 4, since there are 10 elements)
	blt outer_loop      ; Branch to outer_loop if r9 < 36

	; Data Section
list DCD 0x10, 0x05, 0x33, 0x24, 0x56, 0x77, 0x21, 0x04, 0x87, 0x01
	AREA data1, data, readwrite
result DCW 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	END