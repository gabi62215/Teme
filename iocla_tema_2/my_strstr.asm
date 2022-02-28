%include "io.mac"
section .data
	haystack_len dd 0
section .text
    global my_strstr
    extern printf

my_strstr:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha

    mov     edi, [ebp + 8]      ; substr_index
    mov     esi, [ebp + 12]     ; haystack
    mov     ebx, [ebp + 16]     ; needle
    mov     ecx, [ebp + 20]     ; haystack_len
    mov     edx, [ebp + 24]     ; needle_len
    ;; DO NOT MODIFY

    ;; TO DO: Implement my_strstr
    sub esp,12
    mov dword [haystack_len],ecx
    mov [esp],ecx ; haystack_len
    mov [esp + 4],edx ; needle_len

    xor ecx,ecx ; i
   	;use eax for comparison
   	;use edx for x counter
   	;use ecx for i counter
search: ; looks for the first chat of sub_str to be equl to str
	mov al,byte [esi + ecx]
	cmp al,[ebx]
	je save_ecx
check_haystack_len:
	inc ecx
	cmp ecx,[esp]
	jl search
	jmp not_found
save_ecx:
	mov [esp + 8],ecx ; save a copy of i
	xor edx,edx
count_matching_chars: ; count and see if the sub_str is present
	mov al,byte [esi + ecx]
	cmp al,[ebx + edx]
	jne check_needle_len
	inc ecx
	inc edx
	cmp edx,[esp + 4]
	jl count_matching_chars
	mov ecx,[esp + 8] ; get back copy of i
check_needle_len: ; if the count is corect update substr_index and end program
	cmp edx,[esp + 4]
	je found
	jmp check_haystack_len
found:
	mov [edi],ecx
	jmp end
not_found: ; if not found make substr_index haystack_len  + 1
	mov eax,dword [haystack_len]
	mov [edi],eax
	inc dword[edi]
end:
	add esp,12

	
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY
