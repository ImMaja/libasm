; ft_strcpy
; char *ft_strcpy(char *dest, const char *src);

global ft_strcpy

section .text

ft_strcpy:
	mov rax, rdi			; Keep dest addr (rdi) in ret addr (rsi)

.loop:
	mov dl, byte [rsi]		; Move current src char in tmp 8bits register	; dl = *src
	mov byte [rdi], dl		; Move tmp char in dst							; *dest = dl

	cmp dl, 0				; Compare src char to '\0'						; if (dl == '\0')
	je .end					; Jump to .end if src char is '\0'				; goto .end

	inc rdi					; Increment dest register addr by 1				; dest++
	inc rsi					; Increment src register addr by 1				; src++
	jmp .loop				; Get back at the beginning of the loop			; goto .loop

.end:
	ret						; Return dest register addr						; return (rax)
