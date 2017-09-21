.set MAGIC, 0x1badb002
.set FLAGS, 0x00
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
  .long MAGIC
  .long FLAGS
  .long CHECKSUM

.section .text
.extern kernelMain
.global loader

loader:
  mov $kernel_stack, %esp
  push %eax
  push %ebx
  call kernelMain

_stop:
  cli
  hlt
  jmp _stop

.section .bss
.space 2*1024*1024
kernel_stack:
