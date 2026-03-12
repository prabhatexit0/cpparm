// Hand-written AArch64 memcpy
// void arm_memcpy(void* dst, const void* src, size_t n)
// x0 = dst, x1 = src, x2 = n

.globl _arm_memcpy
.align 4
_arm_memcpy:
    // Handle zero length
    cbz     x2, .Lmemcpy_done

    // Save dst for return (not needed here, but good practice)
    mov     x3, x0

    // If n >= 64, use the NEON (LDP/STP of Q registers) fast path
    cmp     x2, #64
    b.lt    .Lmemcpy_small

.Lmemcpy_64:
    // Copy 64 bytes at a time using NEON registers
    ldp     q0, q1, [x1]
    ldp     q2, q3, [x1, #32]
    stp     q0, q1, [x0]
    stp     q2, q3, [x0, #32]
    add     x0, x0, #64
    add     x1, x1, #64
    sub     x2, x2, #64
    cmp     x2, #64
    b.ge    .Lmemcpy_64

.Lmemcpy_small:
    // If n >= 16, copy 16 bytes at a time
    cmp     x2, #16
    b.lt    .Lmemcpy_tail

.Lmemcpy_16:
    ldr     q0, [x1]
    str     q0, [x0]
    add     x0, x0, #16
    add     x1, x1, #16
    sub     x2, x2, #16
    cmp     x2, #16
    b.ge    .Lmemcpy_16

.Lmemcpy_tail:
    // Copy remaining bytes one at a time
    cbz     x2, .Lmemcpy_done

.Lmemcpy_byte:
    ldrb    w4, [x1], #1
    strb    w4, [x0], #1
    subs    x2, x2, #1
    b.ne    .Lmemcpy_byte

.Lmemcpy_done:
    ret
