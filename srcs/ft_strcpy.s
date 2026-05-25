global ft_strcpy

section .text

ft_strcpy:
	mov rax, rsi			; Keep dest addr (rsi) in ret addr (rsi)

.loop:
	mov [rdi], [rsi]		; Move character at src (rsi) to dest (rdi)

	cmp byte [rsi], 0		; Compare src char to '\0'
	je .end					; Jump to .end if src char is '\0'

	inc rdi					; Increment dest register addr by 1
	inc rsi					; Increment src register addr by 1

.end:
	ret						; Return dest register addr


