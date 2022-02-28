%include "io.mac"

section .data
    number_4 db 4
    len dd 0
    counter db 1

section .text
    global bin_to_hex
    extern printf

bin_to_hex:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha

    mov     edx, [ebp + 8]      ; hexa_value
    mov     esi, [ebp + 12]     ; bin_sequence
    mov     ecx, [ebp + 16]     ; length
    ;; DO NOT MODIFY
    ;edi
    
    ;; TODO: Implement bin to hex
    ;PRINTF32 `1\n\x0`
    xor ebx,ebx ; counter for edx
    inc ebx
    xor eax,eax
    xor edi,edi
    inc edi
    mov edi,ecx; ; counter for esi
    xor ecx,ecx  ; j counter
    mov dword[len],0
  
check_each_char:
	;PRINTF32 `LEN:%d\n\x0`,[len]
    xor eax,eax
    cmp ecx,eax
    jne second_condition
    jmp check_for_1

second_condition:
    mov al,cl
    mov [counter],ebx
    xor ebx,ebx
    div byte [number_4]
    mov bl,ah
    cmp bl,0
    je restore_ebx_1

    jmp restore_ebx_2

restore_ebx_1:
	mov ebx,[counter]
	jmp write_byte

restore_ebx_2:
	mov ebx,[counter]
	jmp check_for_1

write_byte:
    xor eax,eax
    cmp byte [len],9
    jg greater_than_10
    mov al,'0'
    add al,byte [len]
    mov [edx + ebx - 1],al
back:
    inc ebx
    xor ecx,ecx
    mov [len],ecx

check_for_1:
    xor eax,eax
    mov al,byte [esi + edi - 1]
    cmp al,'1'
    je add_value
looping_conditions:
    inc ecx
    dec edi
    cmp edi,0
    jg check_each_char
    jmp end
add_value:
    xor eax,eax
    inc eax
    ;PRINTF32 `ecx:%d\n\x0`,ecx
    shl eax,cl
    ;PRINTF32 `eax:%d\n\x0`,eax
    add [len],eax
    jmp looping_conditions

greater_than_10:
    cmp byte[len],10
    je hex_10
    cmp byte[len],11
    je hex_11
    cmp byte[len],12
    je hex_12
    cmp byte[len],13
    je hex_13
    cmp byte[len],14
    je hex_14
    cmp byte[len],15
    je hex_15

hex_10:
    mov byte [edx + ebx - 1],byte 'A'
    jmp back
hex_11:
    mov byte [edx + ebx - 1],byte 'B'
    jmp back
hex_12:
    mov byte [edx + ebx - 1],byte 'C'
    jmp back
hex_13:
    mov byte [edx + ebx - 1],byte 'D'
    jmp back
hex_14:
    mov byte [edx + ebx - 1],byte 'E'
    jmp back
hex_15:
    mov byte [edx + ebx - 1],byte 'F'
    jmp back

end:
    xor eax,eax
    cmp byte [len],9
    jg greater_than_10_2
    mov al,'0'
    add al,byte [len]
    mov [edx + ebx - 1],al
    jmp actual_end

greater_than_10_2:
    cmp byte[len],10
    je hex_10_2
    cmp byte[len],11
    je hex_11_2
    cmp byte[len],12
    je hex_12_2
    cmp byte[len],13
    je hex_13_2
    cmp byte[len],14
    je hex_14_2
    cmp byte[len],15
    je hex_15_2

hex_10_2:
    mov byte [edx + ebx - 1],byte 'A'
    jmp actual_end
hex_11_2:
    mov byte [edx + ebx - 1],byte 'B'
    jmp actual_end
hex_12_2:
    mov byte [edx + ebx - 1],byte 'C'
    jmp actual_end
hex_13_2:
    mov byte [edx + ebx - 1],byte 'D'
    jmp actual_end
hex_14_2:
    mov byte [edx + ebx - 1],byte 'E'
    jmp actual_end
hex_15_2:
    mov byte [edx + ebx - 1],byte 'F'
    jmp actual_end

actual_end:
	mov ecx,ebx
push:
    mov al,byte [edx + ecx - 1]
    push eax
    loop push

    mov ecx,ebx
pop:
	pop eax
	mov [edx + ecx - 1],al
	loop pop

	mov eax,[ebp + 16]
	add eax,3
	shr eax,2
	mov byte[edx + eax],0x0a
	PRINTF32 `%s\n\x0`,edx

    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY