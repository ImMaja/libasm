; ft_read
; ssize_t read(int fd, void *buf, size_t count);

global ft_read
extern __errno_location

section .text

ft_read:
	mov rax, 0		; Set read syscall in rax						; rax = SYS_read
	syscall			; Call read syscall								; rax = syscall(SYS_read, fd, buf, count)

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
