.data
msg:
 .ascii "Hello, World!\n"
 .set len, . - msg
 
.text
.globl main
main:
 mov $4, %eax
 mov $1, %ebx
 mov $msg, %ecx
 mov $len, %edx
 int $0x80
 
 mov $1, %eax
 xor %ebx, %ebx
 int $0x80
