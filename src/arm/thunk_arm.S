// Hand-written AArch64 thunk: indirect function call
// uint64_t arm_thunk_call(uint64_t (*fn)(uint64_t), uint64_t arg)
// x0 = function pointer, x1 = argument
//
// This is the minimal overhead indirect call — just a register move + blr.
// Compare against std::function, virtual dispatch, etc.

.globl _arm_thunk_call
.align 4
_arm_thunk_call:
    // Save link register (we need to return after the indirect call)
    stp     x29, x30, [sp, #-16]!
    mov     x29, sp

    // Move fn pointer to a temp register
    mov     x8, x0
    // Move arg into x0 (first argument for the callee)
    mov     x0, x1
    // Indirect branch-and-link to the function pointer
    blr     x8

    // Result is already in x0
    ldp     x29, x30, [sp], #16
    ret
