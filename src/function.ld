OUTPUT_FORMAT(binary)

SECTIONS 
{
    . = 0x0000;
    .text : 
    {
        *(.linker)
        *(.text)
        *(.text.*)
    }
    .data : { 
        *(.data); 
        *(.data.*) 
    }
    .bss : {
        *(.bss)
        *(.bss.*)
    }
}