; ft_atoi_base
; int ft_atoi_base(char *str, char *base);

global ft_atoi_base

section .text

ft_atoi_base:
	; not implemented yet

_check_base:
	test rdi, rdi				; Test if 'base' is not NULL				; if (!base)
	jz .invalid_base			; Jump to .invalid_base if NULL				; if (!base) goto .invalid_base

	mov eax, 0					; eax is base length, or -1 if invalid char	; eax = 0

.loop:
	mov dl, byte [rdi]			; Save current char							; dl = *base

	cmp dl, 0					; Compare dl to '\0'						; dl == '\0'
	je .end						; Jump to .end if equals					; if (dl == '\0') goto .end

	cmp dl, 43					; Compare dl to '+'							; dl == '+'
	je .invalid_base			; Jump to .invalid_base if equals			; if (dl == '+') goto .invalid_base

	cmp dl, 45					; Compare dl to '-'							; dl == '-'
	je .invalid_base			; Jump to .invalid_base if equals			; if (dl == '-') goto .invalid_base

	cmp dl, 32					; Compare dl to space						; dl == 32
	je .invalid_base			; Jump to .invalid_base if dl == 32			; if (dl == 32) goto .invalid_base

	cmp dl, 9					; Compare dl to first whitespace			; dl < 9
	jb .not_whitespace			; Jump to .not_whitespace if dl < 9			; if (dl < 9) goto .not_whitespace

	cmp dl, 13					; Compare dl to last whitespace				; dl < 13
	jbe .invalid_base			; Jump to .invalid_base if dl <= 13			; if (dl <= 13) goto .invalid_base

.not_whitespace:
	mov ecx, 1					; Set index for innerloop, start at 1 to ignore curr char	; rcx = 1

.dup_loop:
	cmp byte [rdi + rcx], 0		; Compare innerloop char to '\0'			; rdi[rcx] == '\0'
	je .dup_loop_end			; Jump to .dup_loop_end if equals			; if (rdi[rcx] == '\0') goto .dup_loop_end

	cmp dl, byte [rdi + rcx]	; Compare outerloop char to innerloop char	; dl == rdi[rcx]
	je .invalid_base			; Jump to .invalid_base if equals			; if (dl == rdi[rcx]) goto .invalid_base

	inc rcx						; Increment index by 1						; rcx++
	jmp .dup_loop				; Jump back to the begenning of dup_loop	; goto .dup_loop

.dup_loop_end:
	inc rdi						; Increment base ptr by 1					; base++
	inc eax						; Increment base length count by 1			; eax++
	jmp .loop

.end:
	cmp eax, 2					; Compare base length to 2					; eax < 2
	jl .invalid_base			; Jump to .invalid_base if length < 2		; if (eax < 2) goto .invalid_base

	ret							; Otherwise return successfully				; return (eax)

.invalid_base:
	mov eax, -1					; Set -1 in return value					; eax = -1
	ret							; Return error								; return (-1)
