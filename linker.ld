MEMORY
{
  0x00000000 : ORIGIN = 0x00000000, LENGTH = 16M
}

SECTIONS
{
  .text : {
    *(.text)
  }
  .data : {
    *(.data)
  }
  .bss : {
    *(.bss)
  }
}
