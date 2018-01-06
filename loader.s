# This is the code that first eexecutes when the bootloader calls our kernel
# it sets the magic number which is required by the boot loader
# then it calls the kernel main routine in the CPP domain
.set MAGIC, 0x1badb002
.set FLAGS, (1<<0 | 1<<1 )
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

.section .text
.extern kernelMain
.extern callConstructors
.global loader

loader:
    mov $kernel_stack, %esp
    call callConstructors
    push %eax
    push %ebx
    call kernelMain

_stop:
    cli
    hlt
    jmp _stop



.section .bss
.space 2*1024*1024;   # 2Mb
kernel_stack:
