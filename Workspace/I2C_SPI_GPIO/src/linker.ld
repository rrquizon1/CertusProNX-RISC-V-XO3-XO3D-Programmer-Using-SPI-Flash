/* Lattice Generated linker script, for normal executables */

ENTRY (_start)

_HEAP_SIZE = DEFINED(_HEAP_SIZE) ? _HEAP_SIZE : 0x0;
_STACK_SIZE = DEFINED(_STACK_SIZE) ? _STACK_SIZE : 0xA00;

MEMORY
{
    sysmem0_inst (rwx) : org = 0x0, len = 0x2a000
}

SECTIONS
{
  /* CODE */
  .text : ALIGN(4)
  {
    _ftext = .;
    PROVIDE (_sprof = .);
    KEEP (*(SORT(.crt*)))
    *(.text .text.* .gnu.linkonce.t.*)
    KEEP (*(.init))
    KEEP (*(.fini))
    . = ALIGN(4);
    _etext = .;
  } >sysmem0_inst

  .gprof : ALIGN(4)
  {
    PROVIDE (_s_part_prof = .);
    KEEP (*(.gprof))
    . = ALIGN(4);
    PROVIDE (_eprof = .);
  } >sysmem0_inst

  .ctors : ALIGN(4)
  {
    _ctors_start = .;
    KEEP (*(.init_array*))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
    . = ALIGN(4);
    _ctors_end = .;
  } >sysmem0_inst

  .dtors : ALIGN(4)
  {
    _dtors_start = .;
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    . = ALIGN(4);
  } >sysmem0_inst

  /* DATA */
  .rodata : ALIGN(4)
  {
    *(.rdata)
    *(.rodata .rodata.*)
    *(.gnu.linkonce.r.*)
    . = ALIGN(4);
  } >sysmem0_inst

  .data : ALIGN(4)
  {
    *(.data .data.*)
    *(.gnu.linkonce.d.*)
    . = ALIGN(4);
    PROVIDE( __global_pointer$ = . + 0x800 );
    *(.sdata .sdata.*)
    *(.gnu.linkonce.s.*)
    *(.srodata.cst16)
    *(.srodata.cst8)
    *(.srodata.cst4)
    *(.srodata.cst2)
    *(.srodata .srodata.*)
    . = ALIGN(4);
  } >sysmem0_inst

  .bss (NOLOAD) : ALIGN(4)
  {
    /* This is used by the startup in order to initialize the .bss secion */
    _bss_start = .;
    *(.sbss*)
    *(.gnu.linkonce.sb.*)
    *(.bss .bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(4);
    _bss_end = .;
  } >sysmem0_inst
  
  .heap (NOLOAD) : ALIGN(8)
  {
    PROVIDE ( _heap_start = .);
    PROVIDE ( __heap_start = .);
    . = . + _HEAP_SIZE;
    . = ALIGN(8);
    PROVIDE ( _heap_end = .);
    PROVIDE ( __heap_end = .);
  } >sysmem0_inst
  
  .stack (NOLOAD) : ALIGN(16)
  {
    PROVIDE (_stack_end = .);
    . = . + _STACK_SIZE;
    . = ALIGN(16);
    PROVIDE (_stack_start = .);
    PROVIDE (_end = .);
    PROVIDE (end = .);
  } >sysmem0_inst
  /* END */
}
