# Assembly-Interpreter_VM
An assembly language interpreter that runs assembly language instructions with accordance to a simplified virtual machine architecture

Features of the Assembly Language Interpreter
Virtual Machine Components:
- Registers: 7 general-purpose registers (R0–R6), each 1 byte wide and capable of storing signed integers (-128 to 127).
- Memory: 64 bytes of addressable signed memory (0–63).
- Program Counter (PC): Tracks the currently executing instruction.
- Flags: Four single-bit flags:
- Carry Flag (CF)
- Overflow Flag (OF)
- Underflow Flag (UF)
- Zero Flag (ZF)

Instruction Execution:
- Instructions are read from a .asm file and executed sequentially.
- After each instruction, registers, memory, and flags are updated accordingly.
- Final state of the virtual machine (registers, flags, memory) is printed or saved.

Basic Input/Output and Data Movement
- IN Rdst: Reads an integer input from the user and stores it in register Rdst. Updates flags accordingly.
- OUT Rsrc: Outputs the value stored in register Rsrc to the console or output file.
- MOV Instruction Variants:
  - MOV literal, Rdst
    Moves a constant value to Rdst.
    Example: MOV 5, R0
  
  - MOV Rsrc, Rdst
    Copies the value from Rsrc to Rdst.
    Example: MOV R1, R0
  
  - MOV [Rsrc], Rdst
    Indirectly accesses memory at the address stored in Rsrc and moves the value into Rdst.
    Example: MOV [R1], R3

Arithmetic Operations:
- ADD Rsrc, Rdst: Adds the value of Rsrc to Rdst and stores the result in Rdst.
- SUB Rsrc, Rdst: Subtracts the value of Rsrc from Rdst and stores the result in Rdst.
- MUL Rsrc, Rdst: Multiplies the value of Rdst by Rsrc and stores the result in Rdst.
- DIV Rsrc, Rdst: Divides Rdst by Rsrc and stores the result in Rdst.
- Flags are updated accordingly (OF, UF, ZF, CF).

Increment and Decrement:
- INC Rdst: Increments the value in Rdst by 1.
- DEC Rdst: Decrements the value in Rdst by 1.
- Flags updated after operation.

Bitwise Rotation and Shifting:
- ROL Rdst, count: Rotates bits in Rdst to the left by the specified count.
- ROR Rdst, count: Rotates bits in Rdst to the right by the specified count.
- SHL Rdst, count: Shifts bits in Rdst to the left by the specified count, fills with zeros.
- SHR Rdst, count: Shifts bits in Rdst to the right by the specified count, fills with zeros.

Memory Operations:
- LOAD Rdst, addr: Loads value from memory address addr into Rdst.
- LOAD Rdst, [Raddr]: Loads value from memory address stored in Raddr into Rdst.
- STORE Rsrc, addr: Stores the value in Rsrc into memory address addr.
- STORE Rsrc, [Raddr]: Stores the value in Rsrc into memory address pointed to by Raddr.

