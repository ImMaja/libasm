global ft_list_push_front

extern malloc

; Define offset for t_list struct
%define T_LIST_DATA 0
%define T_LIST_NEXT 8

; Define total size of the struct
%define T_LIST_SIZE 16

section .text
; void ft_list_push_front(t_list **begin_list, void *data);
; Arguments:
;	rdi = begin_list
;	rsi = data
;
; Return:
;	void
;
; Registers:
;	rdi -> begin_list
;	rsi -> data
;	r12 -> Save begin_list
;	r13 -> Save data
;	rdx -> tmp ptr holder
;	rax -> new struct ptr
;
; Calls:
;	malloc
ft_list_push_front:
	; Return if 'begin_list' is NULL
	test rdi, rdi
	jz .return

	; Save r12 and r13 before use
	push r12
	push r13

	; Save 'begin_list' and 'data' in callee-saved registers
	mov r12, rdi
	mov r13, rsi

	; Set number of bytes to allocate in first param register
	mov rdi, T_LIST_SIZE

	; Align stack memory and call malloc
	sub rsp, 8
	call malloc
	add rsp, 8

	; Retrieve 'begin_list' and 'data'
	mov rdi, r12
	mov rsi, r13

	; Restore callee-saved registers
	pop r13
	pop r12

	; Return if malloc failed
	test rax, rax
	jz .return

	; Set 'data' in newly allocated node
	mov [rax + T_LIST_DATA], rsi

	; Set new_node->next to the current first node
	; new_node->next = *begin_list
	mov rdx, [rdi]
	mov [rax + T_LIST_NEXT], rdx

	; Set new node ptr in *begin_list
	mov [rdi], rax

	ret

.return:
	ret

