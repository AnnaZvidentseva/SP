.386
.model flat, stdcall
option casemap :none

include includes/windows.inc
include includes/user32.inc
include includes/kernel32.inc
includelib includes/user32.lib
includelib includes/kernel32.lib
 
include includes/msvcrt.inc        
includelib includes/msvcrt.lib         

.data
msg				db 		0dh, 0ah, 'Good Bye!', 0dh, 0ah
msgArray1		db 		'This array: ', 0
msgArray2		db 		0dh, 0ah, 'New  array: ', 0
format	 		db 		"%d ", 0
array			dw 		6345, 567, 1435, 7453, 567, 65, 745, 1123, 1598, 5
count 			db		1

.code
MyProcess proc
	LOCAL 	hStdout :DWORD	
	invoke 	GetStdHandle, STD_OUTPUT_HANDLE
	mov 	hStdout, eax
	invoke 	WriteConsole, hStdout, offset msgArray1, sizeof msgArray1, NULL, NULL
	
	xor ebx, ebx

_thisArray:
	cmp ebx, sizeof array
	je _integer0
	movzx edx, [array+ebx]
	invoke crt_printf, addr format, [array+ebx]
	add ebx, 2d
	jmp _thisArray
	
_integer0:
	xor ebx, ebx
	invoke 	WriteConsole, hStdout, offset msgArray2, sizeof msgArray2, NULL, NULL
	
	jmp _integer

_integer:
	cmp ebx, sizeof array
	je _end
	movzx edx, [array+ebx]	
	test count, 1
	jz _invert
	invoke crt_printf, addr format, [array+ebx]
	inc count
	add ebx, 2d
	jmp _integer

_invert:
	xor edx, 11111111b
	invoke crt_printf, addr format, edx
	inc count
	add ebx, 2d
	jmp _integer
;	invoke WriteConsole, hStdout, offset msg, sizeof msg, NULL, NULL
	
_end: 
	invoke WriteConsole, hStdout, offset msg, sizeof msg, NULL, NULL
		
MyProcess endp

end MyProcess