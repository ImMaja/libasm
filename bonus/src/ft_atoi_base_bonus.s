global ft_atoi_base

section .text

; int ft_atoi_base(char *str, char *base)
;
; Arguments:
;   rdi = str
;   rsi = base
;
; Return:
;   eax = converted value
;   eax = 0 if an argument is invalid
;
; Clobbers:
;   rax, rcx, rdx
;
; Calls:
;   _check_base
ft_atoi_base:
	push rdi			; Save 'str' and align memory
	mov rdi, rsi		; Move 'base' in first arg register

	call _check_base	; Check if 'base' string is valid

	pop rdi				; Retrieve 'str' and align memory

	; Check if 'base' is valid
	cmp eax, -1
	je .invalid_base

	; 

	; Return converted 'str' in 'base'
	mov eax, 0;
	ret

; Return 0 on error
.invalid_base:
	mov eax, 0
	ret

; r12 = str courant
; r13 = base début
; r15d = base_len
; r14d = sign
; r10d = result
; ecx = index temporaire dans base
; al/dl = caractères temporaires


; int _check_base(char *base)
;
; Arguments:
;   rdi = base
;
; Return:
;   eax = base length
;   eax = -1 if base is invalid
;
; Clobbers:
;   rcx, rdx, rdi
_check_base:
	; Check if 'base' is NULL
	test rdi, rdi
	jz .invalid_base

	; Set 'base' length at 0
	mov eax, 0

.loop:
	mov dl, byte [rdi]	; Save current char

	; Check if current char is '\0'
	cmp dl, 0
	je .end

	; Check if current char is '+' or '-'
	cmp dl, '+'
	je .invalid_base
	cmp dl, '-'
	je .invalid_base

	; Check if current char is whitespace
	cmp dl, ' '
	je .invalid_base
	cmp dl, 9
	jb .not_whitespace
	cmp dl, 13
	jbe .invalid_base

.not_whitespace:
	; Innerloop index, start after the
	; current char to avoid matching itself
	mov ecx, 1

.dup_loop:
	; Check if current char is '\0'
	cmp byte [rdi + rcx], 0
	je .dup_loop_end

	; Check if current char is the same as outerloop char
	cmp dl, byte [rdi + rcx]
	je .invalid_base

	; Incr index and jump back at the begenning of .dup_loop
	inc rcx
	jmp .dup_loop

.dup_loop_end:
	; Inct 'base' ptr and 'base' length
	; Jump back at the begenning of .loop
	inc rdi
	inc eax
	jmp .loop

.end:
	; Check is 'base' length is < 2
	cmp eax, 2
	jl .invalid_base
	ret

.invalid_base:
	; Return -1 on invalid 'base'
	mov eax, -1
	ret
