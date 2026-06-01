; ft_strlen
; size_t ft_strlen(const char *s);

global ft_strlen				; Export ft_strlen

section .text					; Code section

ft_strlen:
	mov rax, 0					; Put 0 in rax (return register)

.loop:
	cmp byte [rdi + rax], 0		; Compare current caracter with '\0'
	je .end						; '\0' found

	inc rax						; Increment rax (ret value) by 1
	jmp .loop					; Jump to the beginning of the loop

.end:
	ret							; Return of the ft_strlen function
