; ft_strdup
; char *ft_strdup(const char *s);

global ft_strdup
extern ft_strlen
extern malloc
extern ft_strcpy

section .text
ft_strdup:
	push r12			; Save r12 on stack and align memory		; saved_r12 = r12
	mov r12, rdi		; Set s string on r12 register				; r12 = s

	call ft_strlen		; Retrieve len of s by calling ft_strlen	; rax = ft_strlen(rdi)
	lea rdi, [rax + 1]	; Move `s` length + 1 in rdi				; rdi = rax + 1

	call malloc			; Allocate memory for result				; rax = malloc(rdi)
	cmp rax, 0			; Check if malloc failed					; rax == 0
	je .end				; Jump to .end if rax == 0 and return NULL	; if (rax == 0) goto .end

	mov rdi, rax		; Move newly allocated ptr in rdi			; rdi = rax
	mov rsi, r12		; Move src string from r12 to rsi			; rsi = r12
	call ft_strcpy		; Copy src to dest using ft_strcpy			; rax = ft_strcpy(rdi, rsi)

	jmp .end			; Jump to .end and return newly allocated string	; goto .end

.end:
	pop r12				; Retrieve r12 from stack					; r12 = saved_r12
	ret					; Return rax								; return (rax)
