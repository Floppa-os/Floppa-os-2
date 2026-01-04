; x86-32, AT&T синтаксис
.section .text

.global context_switch
context_switch:
    ; Сохраняем регистры текущей задачи
    pushl %eax
    pushl %ebx
    pushl %ecx
    pushl %edx
    pushl %esi
    pushl %edi
    pushl %ebp

    ; Запоминаем текущий ESP
    movl %esp, tasks(,%edi,8)  ; tasks[current_task].stack_ptr

    ; Загружаем ESP следующей задачи
    movl tasks+4(,%esi,8), %esp  ; tasks[next_task].stack_ptr

    ; Восстанавливаем регистры
    popl %ebp
    popl %edi
    popl %esi
    popl %edx
    popl %ecx
    popl %ebx
    popl %eax
    ret
