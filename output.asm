section .text
global _main
_main:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    mov rax, 0
    mov [rbp-20], eax
    mov rax, 0
    mov [rbp-24], eax
    mov rax, 0
    mov [rbp-28], eax
    mov rax, 0
    mov [rbp-32], eax
for_loop_0:
    mov rax, 3
    push rax
    mov eax, [rbp-32]
    movsx rax, eax
    pop rcx
    cmp rax, rcx
    setl al
    movzx rax, al
    test rax, rax
    jz for_end_1
    mov rax, 0
    mov [rbp-36], eax
for_loop_2:
    mov rax, 3
    push rax
    mov eax, [rbp-36]
    movsx rax, eax
    pop rcx
    cmp rax, rcx
    setl al
    movzx rax, al
    test rax, rax
    jz for_end_3
    mov eax, [rbp-36]
    movsx rax, eax
    push rax
    mov eax, [rbp-32]
    movsx rax, eax
    pop rcx
    imul rax, rcx
    mov [rbp-40], eax
    mov eax, [rbp-40]
    movsx rax, eax
    push rax
    mov eax, [rbp-20]
    movsx rax, eax
    pop rcx
    add rax, rcx
    mov [rbp-20], eax
    mov rax, 2
    push rax
    mov eax, [rbp-40]
    movsx rax, eax
    pop rcx
    cmp rax, rcx
    setg al
    movzx rax, al
    test rax, rax
    jz if_false_4
    mov rax, 2
    push rax
    mov eax, [rbp-40]
    movsx rax, eax
    pop rcx
    imul rax, rcx
    mov [rbp-40], eax
if_false_4:
    mov rax, 1
    push rax
    mov eax, [rbp-36]
    movsx rax, eax
    pop rcx
    add rax, rcx
    mov [rbp-36], eax
    jmp for_loop_2
for_end_3:
    mov rax, 1
    push rax
    mov eax, [rbp-32]
    movsx rax, eax
    pop rcx
    add rax, rcx
    mov [rbp-32], eax
    jmp for_loop_0
for_end_1:
    mov rax, 10
    mov [rbp-44], eax
while_loop_6:
    mov rax, 0
    push rax
    mov eax, [rbp-44]
    movsx rax, eax
    pop rcx
    cmp rax, rcx
    setg al
    movzx rax, al
    test rax, rax
    jz while_end_7
    mov rax, 5
    push rax
    mov eax, [rbp-44]
    movsx rax, eax
    pop rcx
    cmp rax, rcx
    setg al
    movzx rax, al
    test rax, rax
    jz if_false_8
    mov rax, 0
    mov [rbp-48], eax
for_loop_10:
    mov rax, 2
    push rax
    mov eax, [rbp-48]
    movsx rax, eax
    pop rcx
    cmp rax, rcx
    setl al
    movzx rax, al
    test rax, rax
    jz for_end_11
    mov rax, 1
    push rax
    mov eax, [rbp-44]
    movsx rax, eax
    pop rcx
    sub rax, rcx
    mov [rbp-44], eax
    mov rax, 1
    push rax
    mov eax, [rbp-48]
    movsx rax, eax
    pop rcx
    add rax, rcx
    mov [rbp-48], eax
    jmp for_loop_10
for_end_11:
    jmp if_end_9
if_false_8:
    mov rax, 1
    push rax
    mov eax, [rbp-44]
    movsx rax, eax
    pop rcx
    sub rax, rcx
    mov [rbp-44], eax
if_end_9:
    jmp while_loop_6
while_end_7:
    add rsp, 16
    mov rax, 60
    xor rdi, rdi
    syscall
