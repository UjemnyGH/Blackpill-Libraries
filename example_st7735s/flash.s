/*@-----CPU-INFO-----*/
.cpu cortex-m4
.thumb
/*@-----CPU-INFO-----*/

.thumb_func
.global _start
_start:
    stacktop: .word 0x20001000
    .word reset

.thumb_func
reset:
    bl stmMain
    b defHandler

.thumb_func
defHandler: b .

.end
