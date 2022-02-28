%include "io.mac"
section .data
    key_len dd 0
    plaintext_len dd 0

section .text
    global vigenere
    extern printf

vigenere:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha

    mov     edx, [ebp + 8]      ; ciphertext
    mov     esi, [ebp + 12]     ; plaintext
    mov     ecx, [ebp + 16]     ; plaintext_len
    mov     edi, [ebp + 20]     ; key
    mov     ebx, [ebp + 24]     ; key_len
    ;; DO NOT MODIFY

    ;; TODO: Implement the Vigenere ciphe
    sub esp,8
    mov [esp],ebx ;key_len
    mov [esp + 4],ecx ;plain_len
copy_key_to_cipher:
	xor eax,eax
	mov al,byte [edi + ebx - 1]
	mov byte[edx + ebx - 1],al
	dec ebx
	jnz copy_key_to_cipher

    xor ecx,ecx ; j
    xor ebx,ebx
    mov ebx,[esp] ; i
    cmp [esp + 4],esp
    jg repeat_key
    jmp before_cipher

;check for non-alphabetical characters to copy on the extended key,
;if not found repeat key char
;builds new key in edx
repeat_key:
    xor eax,eax
    mov al,byte [esi + ebx]
    cmp al,'a';check if char is part of the alphabet
    jge second_condition
else_1:
    cmp al,'A'
    jge second_condition_2
else_2:
    mov [edx + ebx],al ;copy non-alphabetic chars
    cmp ecx,[esp] ;check if counter of key exceds key length
    je ecx_reset
    inc ebx
    cmp ebx,[esp + 4]
    jle repeat_key
    jmp before_cipher
second_condition:
    cmp al,'z'
    jle repeat
    jmp else_2
second_condition_2:
    cmp al,'Z'
    jle repeat
    jmp else_2
repeat:
    mov al,byte [edi + ecx] ;key[j]
    mov [edx + ebx],al ; cipher[i] = key[j]
    inc ecx ; i < text_len
    cmp ecx,[esp]
    je ecx_reset
    inc ebx
    cmp ebx,[esp + 4]
    jle repeat_key
    jmp before_cipher
ecx_reset:
    xor ecx,ecx
    inc ebx
    cmp ebx,[esp + 4]
    jle repeat_key
    jmp before_cipher

;edx cipher
;esi plaintext
;edi key

before_cipher:
    xor ecx,ecx 
    mov ecx,[esp + 4]
    add esp,8
 
cipher:
    xor ebx,ebx
    xor eax,eax
    mov bl,byte [edx + ecx - 1]
    sub bl,'A' ; calculate key just like at caesar and repeat task 2
	mov al,byte [esi + ecx - 1]
    cmp al,'a'
    jge second_condition_a
else_a_1:
    cmp al,'A'
    jge second_condition_a_2
else_a_2:
    mov [edx + ecx -1],al
    dec ecx
    jnz cipher
    jmp end
second_condition_a:
    cmp al,'z'
    jle lower
    jmp else_a_1
second_condition_a_2:
    cmp al,'Z' ;text[i] <= 'Z'
    jle capital
    jmp else_a_2
lower:
    sub eax,'a'
    add eax,ebx
    mov bl,26
    div bl
    mov bl,ah
    add ebx,'a'
    mov [edx + ecx - 1],bl
    dec ecx
    jnz cipher
    jmp end
capital:
    sub eax,'A'
    add eax,ebx
    mov bl,26
    div bl
    mov bl,ah
    add ebx,'A'
    mov [edx + ecx - 1],bl
    dec ecx
    jnz cipher
    jmp end
    ;; DO NOT MODIFY
end:
    popa
    leave
    ret
    ;; DO NOT MODIFY