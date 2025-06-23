section .text
global _main
_main:
    push rbp
    mov rbp, rsp
    ; ERROR: Unknown variable def
    ; CallExprAST codegen not implemented
    mov rax, 2
    push rax
    ; ERROR: Unknown variable y
    push rax
    ; ERROR: Unknown variable x
    pop rcx
    add rax, rcx
    pop rcx
    cqo
    idiv rcx
    ; CallExprAST codegen not implemented
    mov rax, 60
    xor rdi, rdi
    syscall
