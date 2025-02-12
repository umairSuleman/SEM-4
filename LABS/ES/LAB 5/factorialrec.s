	AREA RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors 
	DCD 0x40001000 ; stack pointer value when stack is empty
	DCD Reset_Handler ; reset vector
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler

	LDR R0,=NUM  ;LOAD NUUM ADDRESS
	LDR R1,=RESULT	;LOAD RESULT ADDRESS
	LDR R2,[R0]	;LOAD NUM VALUE
	
factorial
	CMP R2,#1	;CHECK IF N==1
	BEQ baseCase	;GO TO BC
	
	PUSH{R2,lr}		;PUSH N INTO STACK
	SUB R2,R2,#1	;COMPUTE N-1 FOR FACT
	BL factorial 
	
	POP {R3,lr}
	MUL R2,R2,R3	;ACTS AS N*(N-1)
	STR R2,[R1]		;STORES VALUE IN RESULT EACH TIME
	
	BX LR

baseCase
	MOV R2,#1
	BX LR
	
STOP B STOP

NUM DCD 0x5
	AREA mydata, DATA, READWRITE
RESULT DCD 0
	END