global ft_list_size

; Define offset for next ptr of t_list struct
%define T_LIST_NEXT 8

section .text
; int ft_list_size(t_list *begin_list);
; Arguments:
;	rdi = begin_list
;
; Return:
;	int The size of the linked list
;
; Registers:
;	rdi -> current list node
;	eax -> node counter and returned value
ft_list_size:
	; Initialize eax to 0
	xor eax, eax

; Iterate on linked list
.list_iter_loop:

	; Return when current node is NULL
	test rdi, rdi
	jz .return

	mov rdi, [rdi + T_LIST_NEXT]
	inc eax

	jmp .list_iter_loop

.return:
	ret
