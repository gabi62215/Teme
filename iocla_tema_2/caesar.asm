%include "io.mac"

section .text
    global caesar
    extern printf

caesar:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha

    mov     edx, [ebp + 8]      ; ciphertext
    mov     esi, [ebp + 12]     ; plaintext
    mov     edi, [ebp + 16]     ; key
    mov     ecx, [ebp + 20]     ; length
    ;; DO NOT MODIFY

    ;; TODO: Implement the caesar cipher
chypher:
    xor eax, eax
    mov al,byte [esi + ecx - 1]
    cmp al,'a' ;text[i] >= 'a'
    jge second_condition   
else_1:
    cmp al, 'A' ;text[i] >= 'A'
    jge second_condition_2
else_2: ; non-alphabetical char
    mov [edx + ecx - 1],al ;cipher[i] = text[i]
    loop chypher
    jmp end
second_condition: 
    cmp al,'z' ; text[i] <= 'z'
    jle lower
    jmp else_1
second_condition_2:
    cmp al,'Z' ;text[i] <= 'Z'
    jle capital
    jmp else_2
lower: ; cipher[i] = (text[i] - 'a' + x) % 26 + 'a'
    sub eax, 'a'
    add eax, edi
    mov bl, 26
    div bl
    mov bl, ah
    add ebx, 'a'
    mov [edx + ecx - 1], bl
    loop chypher
    jmp end
capital: ; cipher[i] = (text[i] - 'A' + x) % 26 + 'A'
    sub eax, 'A'
    add eax, edi
    mov bl, 26
    div bl
    mov bl, ah
    add ebx, 'A'
    mov [edx + ecx - 1], bl
    loop chypher
    jmp end
end:
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY