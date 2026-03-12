// Hand-written AArch64 NEON float vector add
// void arm_vector_add_f32(float* dst, const float* a, const float* b, size_t n)
// x0 = dst, x1 = a, x2 = b, x3 = n

.globl _arm_vector_add_f32
.align 4
_arm_vector_add_f32:
    cbz     x3, .Lvadd_done

    // Process 16 floats (64 bytes) at a time using NEON
    cmp     x3, #16
    b.lt    .Lvadd_small

.Lvadd_16:
    // Load 16 floats from a and b
    ldp     q0, q1, [x1]           // a[0..7]
    ldp     q2, q3, [x1, #32]      // a[8..15]
    ldp     q4, q5, [x2]           // b[0..7]
    ldp     q6, q7, [x2, #32]      // b[8..15]

    // NEON float add
    fadd    v0.4s, v0.4s, v4.4s
    fadd    v1.4s, v1.4s, v5.4s
    fadd    v2.4s, v2.4s, v6.4s
    fadd    v3.4s, v3.4s, v7.4s

    // Store results
    stp     q0, q1, [x0]
    stp     q2, q3, [x0, #32]

    add     x0, x0, #64
    add     x1, x1, #64
    add     x2, x2, #64
    sub     x3, x3, #16
    cmp     x3, #16
    b.ge    .Lvadd_16

.Lvadd_small:
    // Process 4 floats at a time
    cmp     x3, #4
    b.lt    .Lvadd_tail

.Lvadd_4:
    ldr     q0, [x1], #16
    ldr     q1, [x2], #16
    fadd    v0.4s, v0.4s, v1.4s
    str     q0, [x0], #16
    sub     x3, x3, #4
    cmp     x3, #4
    b.ge    .Lvadd_4

.Lvadd_tail:
    // Process remaining floats one at a time
    cbz     x3, .Lvadd_done

.Lvadd_single:
    ldr     s0, [x1], #4
    ldr     s1, [x2], #4
    fadd    s0, s0, s1
    str     s0, [x0], #4
    subs    x3, x3, #1
    b.ne    .Lvadd_single

.Lvadd_done:
    ret
