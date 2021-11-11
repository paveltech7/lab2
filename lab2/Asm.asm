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
	mov ebx, [esi];Получение первого числа и прибавлять до максимального
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
	;|~~~~~~~~~~~~~~|<---стар. sp
	;|--------------|

	mov esi,arr ;позиционируемся на массив
	mov eax,max_pos
	mov ebx,4
	mul ebx
	add esi,eax;сдвигаем границу массива на максимальный элемент 
	mov edx,len
	sub edx, max_pos
	dec edx ;вычисляем сколько элементов до конца массива
	cmp edx,0
	jbe exit

a2:    
	mov ecx,edx   
    xor ebx,ebx        ;флаг – были/не были перестановки в проходе
a3:    
	mov eax,[esi+ecx*4-4]    ;получаем значение очередного элемента    
    cmp [esi+ecx*4],eax    ;сравниваем со значением соседнего элемента
    jng a4    ;если больше или равен - идем к следующему элементу
    setna bl    ;была перестановка - взводим флаг
    xchg eax,[esi+ecx*4]    ;меняем значение элементов местами
    mov [esi+ecx*4-4],eax
a4:    
	loop a3    ;двигаемся вверх до границы массива
    add esi,4    ;сдвигаем границу отсортированного массива
    dec ebx    ;проверяем были ли перестановки
    jnz exit    ;если перестановок не было - заканчиваем сортировку
    dec edx        ;уменьшаем количество неотсортированных элементов
    jnz a2;если есть еще неотсортированные элементы - начинаем новый проход
exit:
	ret
		
SortFromMaxToEndUbivanie ENDP

END

