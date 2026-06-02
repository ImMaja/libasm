; ft_strcmp
; int ft_strcmp(const char *s1, const char *s2);

global ft_strcmp

section .text

ft_strcmp:
.loop:
	movzx eax, byte [rdi]		; Move s1 char into 32 bits ret register	; eax = *s1
	movzx edx, byte [rsi]		; Move s2 char into 32 bits register		; edx = *s2

	cmp eax, edx				; Compare both chars						; eax == edx
	jne .ne						; If not equals, jump to ne					; goto .ne

	cmp eax, 0					; Compare s1 char to '\0'					; eax == 0
	je .end						; If equals, jump to end					; goto .end

	inc rdi						; Increment rdi pointer by 1				; rdi++
	inc rsi						; Increment rsi pointer by 1				; rsi++

	jmp .loop					; Loop back									; goto .loop

.ne:
	sub eax, edx				; Substract edx from eax					; eax = eax - edx
	ret							; Return									; return (eax)

.end:
	ret