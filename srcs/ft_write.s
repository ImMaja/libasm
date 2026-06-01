global ft_write
extern __errno_location

section .text

ft_write:
	mov rax, 1		; Set write syscall in rax						; rax = SYS_write
	syscall			; Call write syscall							; rax = syscall(SYS_write, fd, buffer, count)

	cmp rax, 0		; Compare returned value with 0					; rax < 0
	jl .error		; If returned value < 0, goto .error			; if (rax < 0) goto .error

	ret				; Return successfully							; return (rax)

.error:
	neg rax			; Convert negative error code to errno value	; rax = -rax
	push rax		; Save errno val on stack						; saved_errno = rax

	call __errno_location	; Get errno addr						; rax = __errno_location()

	pop rcx			; Retrieve errno value in rcx					; rcx = saved_errno
	mov [rax], ecx	; Move errno value in errno						; *(int *)rax = ecx
	mov rax, -1		; Set ret val register at -1					; rax = -1
	ret				; Return failure								; return (rax)
