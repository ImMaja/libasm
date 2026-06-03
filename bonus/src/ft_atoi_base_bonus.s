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
; Registers:
;   rdi -> str
;   rsi -> base
;   r8b -> Temp char
;   edx -> base_length
;   ecx -> sign
;   eax -> result
;
; Calls:
;   _check_base
ft_atoi_base:
	; Check if 'str' is not NULL
	cmp rdi, 0
	je .return_error

	; Save callee-saved registers in stack
	push r12
	push r13

	; Save 'str' and 'base' in safe registers
	mov r12, rdi
	mov r13, rsi

	; Move 'base' in first arg register
	mov rdi, rsi

	; Align stack ptr and check 'base' string
	sub rsp, 8
	call _check_base
	add rsp, 8

	; Restore 'str' and 'base'
	mov rdi, r12
	mov rsi, r13

	; Restore callee-saved registers
	pop r13
	pop r12

	; Check if 'base' is valid
	cmp eax, -1
	je .return_error

	; Save 'base' length in edx
	mov edx, eax

; Increment 'str' string ptr to skip whitespaces
.ws_loop:
	mov r8b, byte [rdi]

	; Check for '\0' in 'str'
	cmp r8b, 0
	je .return_error

	; Check for whitespaces in 'str'
	cmp r8b, ' '
	je .char_is_ws
	cmp r8b, 9
	jb .ws_loop_end
	cmp r8b, 13
	jbe .char_is_ws

	jmp .ws_loop_end

; Increment ptr address, get back at the begenning of the loop
.char_is_ws:
	inc rdi
	jmp .ws_loop

.ws_loop_end:

	; Set default value to sign (by default, it's positive)
	mov ecx, 1

; Determine result sign, increment 'str' string ptr to skip signs
; When found a '+', we can just ignore it
.signs_loop:
	mov r8b, byte [rdi]

	; Check for '\0' in 'str'
	cmp r8b, 0
	je .return_error

	; Check for '+' or '-'
	cmp r8b, '-'
	je .invert_sign
	cmp r8b, '+'
	je .continue_signs_loop

	; Not a '\0' nor a sign. At this point 'str' is ready to be converted
	jmp .signs_loop_end

; Invert sign in ecx
; ex: -1 -> 1 and 1 -> -1
.invert_sign:
	neg ecx

; Increment 'str' ptr addr and jump to the begenning of the loop
.continue_signs_loop:
	inc rdi
	jmp .signs_loop

.signs_loop_end:

	; Set 0 in result
	mov eax, 0

; Loop on each remaining char in 'str' and do the conversion
.algo_loop:
	mov r8b, byte [rdi]

	


.algo_loop_end:

	; Signed multiplication result by sign
	imul eax, ecx
	ret

; Return 0
.return_error:
	mov eax, 0
	ret


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
