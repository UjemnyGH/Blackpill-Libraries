
/*@------CPU-INFO------*/
.cpu cortex-m4
.thumb
/*@------CPU-INFO------*/

.thumb_func
.global _start
_start:
    stacktop: .word 0x20001000
    .word reset
/*    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
    .word defaultloop
*/

.thumb_func
reset:
    bl stmMain
    b defaultloop

.thumb_func
defaultloop: b .

.end
