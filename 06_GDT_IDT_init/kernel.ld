ENTRY( entry )

MEMORY
{
    ram : ORIGIN = 0x280000, LENGTH = 0x020000
}


SECTIONS
{
  . = 0x0000;
  .text : 
  {
    *(.text.main);
    *(.text)
  } > ram

  .data :
  {
    *(.data)
  } > ram
}
