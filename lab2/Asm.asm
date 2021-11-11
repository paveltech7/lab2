.686
.MODEL FLAT, C
.STACK
.DATA
.CODE
GetMaxNumPos PROC arr:DWORD, len:DWORD
	mov		ecx, len
	mov		esi, arr
	lodsd
	mov		ebx, eax
	mov		edx, ecx
	dec		ecx
@l1:
	lodsd
	cmp		eax, ebx
	jle		@not_max
	;eax > ebx
	mov		ebx, eax
	mov		edx, ecx
@not_max:
	loop @l1

	mov		eax, len
	sub		eax, edx
	ret
GetMaxNumPos ENDP

Increase PROC arr:DWORD, max_pos:DWORD
	mov esi, arr
	mov ebx, [esi];��������� ������� ����� � ���������� �� �������������
	xor ecx,ecx
@max_pos:
	cmp ecx,max_pos
	je @end_inc
	add [esi],ebx
	add esi,4
	inc ecx
	jmp @max_pos
@end_inc:
	ret
Increase ENDP

SortFromMaxToEndUbivanie PROC arr:DWORD, len:DWORD, max_pos:DWORD

	;|				|<---ss
	;|	ebp			|+0<---sp
	;|	eip			|+4
	;|	offset arr	|+8
	;|	length		|+12
	;|	max_pos		|+16
	;|~~~~~~~~~~~~~~|<---����. sp
	;|--------------|

	mov esi,arr ;��������������� �� ������
	mov eax,max_pos
	mov ebx,4
	mul ebx
	add esi,eax;�������� ������� ������� �� ������������ ������� 
	mov edx,len
	sub edx, max_pos
	dec edx ;��������� ������� ��������� �� ����� �������
	cmp edx,0
	jbe exit

a2:    
	mov ecx,edx   
    xor ebx,ebx        ;���� � ����/�� ���� ������������ � �������
a3:    
	mov eax,[esi+ecx*4-4]    ;�������� �������� ���������� ��������    
    cmp [esi+ecx*4],eax    ;���������� �� ��������� ��������� ��������
    jng a4    ;���� ������ ��� ����� - ���� � ���������� ��������
    setna bl    ;���� ������������ - ������� ����
    xchg eax,[esi+ecx*4]    ;������ �������� ��������� �������
    mov [esi+ecx*4-4],eax
a4:    
	loop a3    ;��������� ����� �� ������� �������
    add esi,4    ;�������� ������� ���������������� �������
    dec ebx    ;��������� ���� �� ������������
    jnz exit    ;���� ������������ �� ���� - ����������� ����������
    dec edx        ;��������� ���������� ����������������� ���������
    jnz a2;���� ���� ��� ����������������� �������� - �������� ����� ������
exit:
	ret
		
SortFromMaxToEndUbivanie ENDP

END

