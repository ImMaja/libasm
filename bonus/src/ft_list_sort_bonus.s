global ft_list_sort

; Define offset for t_list struct
%define T_LIST_DATA 0
%define T_LIST_NEXT 8

section .text

; void ft_list_sort(t_list **begin_list, int (*cmp)());
; Arguments:
;	rdi = begin_list
;	rsi = cmp
;
; Return:
;	void
;
; Registers:
;	r12 = begin_list
;	r13 = cmp
;	r14 = sorted
;	r15 = current
;	rbx = next
;	rbp = pos
ft_list_sort:
	; Check if there is enought nodes to sort the linked-list
	test rdi, rdi
	jz .return
	cmp qword [rdi], 0
	je .return
	mov rax, [rdi]
	cmp qword [rax + T_LIST_NEXT], 0
	je .return

	; Check if cmp function is NULL
	test rsi, rsi
	jz .return

	; Save callee-saved registers
	push r12
	push r13
	push r14
	push r15
	push rbx
	push rbp

	; Stack not align at this point

	; Initialize registers with ptrs
	mov r12, rdi		; begin_list
	mov r13, rsi		; cmp fct ptr
	xor r14, r14		; sorted = NULL
	mov r15, [r12]		; current = *begin_list

	; Align stack memory for cmp call
	sub rsp, 8

; Iterate through the linked-list, node-by-node
.lst_loop:

	; Check if current is NULL
	cmp r15, 0
	jz .end

	; next = current->next
	mov rbx, [r15 + T_LIST_NEXT]

	; if (sorted == NULL)
	test r14, r14
	jz .insert_head

	; Call cmp function with current->data and sorted->data
	mov rdi, [r15 + T_LIST_DATA]
	mov rsi, [r14 + T_LIST_DATA]
	call r13

	; if (eax <= 0)
	cmp eax, 0
	jle .insert_head

; Insertion loop
.insert_loop:

	; ici looper sur la liste triee, call cmp pour determiner ou inserer le noeud

	; current = next
	mov r15, rbx

	; Get back at the beginning of the loop
	jmp .lst_loop


; Insert current node in sorted linked-list
.insert:
	; Set pos->next = current
	mov [rbp + T_LIST_NEXT], r15

	; current->next = NULL
	mov [r15 + T_LIST_NEXT], 0

	; current = next
	mov [r15 + T_LIST_NEXT], rbx

	; Jump back in the main loop
	jmp .lst_loop

; Insert current in first position of the linked_list
.insert_head:
	; current->next = sorted
	mov [r15 + T_LIST_NEXT] = r14

	; sorted = current
	mov r14, r15

	; current = next
	mov r15, rbx

	; Get back at the beginning of the loop
	jmp .lst_loop

; Restore stack memory alignment,
; retrieve callee-saved registers then return
.end:
	add rsp, 8
	pop rbp
	pop rbx
	pop r15
	pop r14
	pop r13
	pop r12
	ret

; Just return
.return:
	ret