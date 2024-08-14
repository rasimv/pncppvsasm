.code

find_primes	proc
    push rax
    push rbx
    push rcx
    push rdx
    push rdi
    push rsi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    pushfq

;    mov rax, 0ffffffh
;magic:
;    dec rax
;    jnz magic

    mov rdi, rcx
    mov rsi, rdx

    ; RDI: array ptr, RSI: array length
    ; Keep the start of the array in R9 as RDI points to the next insert place
    mov r9, rdi
    ; RCX holds the numbers to produce
    mov rcx, rsi
    ; Test for the empty array to make it a bit more robust
    jrcxz l9;f
    ; The odd number last checked is in R8
    mov r8d, 1
    ; Outer loop: find a new prime
l2:
    ; Next number
    add r8d, 2
    ; Reset to the start of the array
    mov rsi, r9
    ; Inner loop: test division with an existing prime
l3:
    ; More entries to test?
    cmp rsi, rdi
    jae l4;f
    ; Load a prime from the array - this increments RSI
    lodsd ;eax, dword ptr [rsi]
    mov r11d, r8d
    xchg r11, rax
    ; Zero upper 32-bits
    xor edx, edx
    div r11d
    ; Is the remainder zero? Then this is not a prime
    test edx, edx
    je l2;b
    ; It's a prime if the division result is smaller than the number to check
    cmp eax, r11d
    ja l3;b
    ; We found a new prime
l4:
    mov eax, r8d
    ; Store the number and increment RDI
    stos dword ptr [rdi]
    ; Repeat until RCX is zero
    loop l2;b
l9:

    popfq
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rsi
    pop rdi
    pop rdx
    pop rcx
    pop rbx
    pop rax

    ret

find_primes	endp

end
