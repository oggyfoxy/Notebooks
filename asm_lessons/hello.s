global _start

section .data
    text db "Hello World!", 10    ; just one newline is enough
    textlen equ $ - text

section .text
_start:
    mov rax, 1          ; sys_write
    mov rdi, 1          ; stdout
    mov rsi, text       ; message
    mov rdx, textlen    ; length
    syscall

    mov rax, 60         ; sys_exit
    mov rdi, 0          ; status 0
    syscall
