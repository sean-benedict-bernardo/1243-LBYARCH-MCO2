section .data
    OUTPUT_STR db "%lf", 10, 0 ; Format string for printf
    OUTPUT_DATA dq 0.0 ; Placeholder for output data

section .text
bits 64
default rel
extern printf

global euclidean_distance_asm
euclidean_distance_asm:
    ; Function to calculate Euclidean distance in assembly
    ; Arguments: X_1, X_2, Y_1, Y_2, Z, length

    ; we are using RCX as a counter
    ; so we will move the X_1 from RCX to R10
    ; for consistency we are move RDX to R11
    ; R8 and R9 remains unchanged
    MOV R10, RCX          ; X_1
    MOV R11, RDX          ; X_2

    MOV R12, [RSP + 40]   ; Z pointer
    MOV EAX, [RSP + 48]   ; length

    XOR RCX, RCX          ; Clear counter

    L1:

    ; Load values from X_1, X_2, Y_1, Y_2
    MOVSD XMM0, [R8 + RCX * 8] ; Load Y_1[i]
    MOVSD XMM1, [R9 + RCX * 8] ; Load Y_2[i]
    MOVSD XMM2, [R10 + RCX * 8] ; Load X_1[i]
    MOVSD XMM3, [R11 + RCX * 8] ; Load X_2[i]

    SUBSD XMM1, XMM0  ; Y_2[i] - Y_1[i]
    MULSD XMM1, XMM1 ; (Y_2[i] - Y_1[i])^2

    SUBSD XMM3, XMM2 ; X_2[i] - X_1[i]
    MULSD XMM3, XMM3 ; (X_2[i] - X_1[i])^2

    ADDSD XMM1, XMM3 ; Add the two squared differences
    SQRTSD XMM1, XMM1 ; Take the square root

    ; write to Z[i]
    MOVSD [R12 + RCX * 8], XMM1

    ; print the result
    INC RCX

    CMP RCX, RAX
    JL L1

    ret