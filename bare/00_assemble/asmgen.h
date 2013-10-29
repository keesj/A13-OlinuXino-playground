
#define R0 0
#define R1 1
#define R2 2
#define R3 3

#define INST_COND_SHIFT 28
#define INST_COND_V(x) (x  << INST_COND_SHIFT)
#define INST_COND_MASK INST_COND_V(0xF)

/* The conditionals e.g. bits [31:28] */
#define INST_COND_EQ INST_COND_V(0x0) /* 0000  EQ  Equal  Equal  Z == 1  */
#define INST_COND_NE INST_COND_V(0x1) /* 0001  NE  Not equal  Not equal, or unordered  Z == 0  */
#define INST_COND_CS INST_COND_V(0x2) /* 0010  CS b  Carry set  Greater than, equal, or unordered  C == 1  */
#define INST_COND_CC INST_COND_V(0x3) /* 0011  CC c  Carry clear  Less than  C == 0  */
#define INST_COND_MI INST_COND_V(0x4) /* 0100  MI  Minus, negative  Less than  N == 1  */
#define INST_COND_PL INST_COND_V(0x5) /* 0101  PL  Plus, positive or zero  Greater than, equal, or unordered  N == 0  */
#define INST_COND_VS INST_COND_V(0x6) /* 0110  VS  Overflow  Unordered  V == 1  */
#define INST_COND_VC INST_COND_V(0x7) /* 0111  VC  No overflow  Not unordered  V == 0  */
#define INST_COND_HI INST_COND_V(0x8) /* 1000  HI  Unsigned higher  Greater than, or unordered  C == 1 and Z == 0  */
#define INST_COND_LS INST_COND_V(0x9) /* 1001  LS  Unsigned lower or same  Less than or equal  C == 0 or Z == 1  */
#define INST_COND_GE INST_COND_V(0xa) /* 1010  GE  Signed greater than or equal  Greater than or equal  N == V  */
#define INST_COND_LT INST_COND_V(0xb) /* 1011  LT  Signed less than  Less than, or unordered  N != V  */
#define INST_COND_GT INST_COND_V(0xc) /* 1100  GT  Signed greater than  Greater than  Z == 0 and N == V  */
#define INST_COND_LE INST_COND_V(0xd) /* 1101  LE  Signed less than or equal  Less than, equal, or unordered  Z == 1 or N != V  */
#define INST_COND_AL INST_COND_V(0xe)  /* 1110  None () d  Always (unconditional)  Always (unconditional)  Any  */
#define INST_COND_UNC INST_COND_V(0xf) /* 1111  the instruction is executed irrespective of the value of the condition flags. */

#define INST_CLASS_SHIFT 25
#define INST_CLASS_V(x) (x  << INST_CLASS_SHIFT)
#define INST_CLASS_MASK INST_CLASS_V(0x7)

/* The class bits [27:25] determine the instruction class , these value only hold if cond != INST_COND_AL */
#define INST_CLASS_DPMISC0 INST_CLASS_V(0x0) /*  00xb - Data-processing and miscellaneous instructions 0 */
#define INST_CLASS_DPMISC1 INST_CLASS_V(0x1) /*  00xb - Data-processing and miscellaneous instructions 0 */
#define INST_CLASS_LS0     INST_CLASS_V(0x2) /*  010b - Load/store word and unsigned byte */
#define INST_CLASS_LS1     INST_CLASS_V(0x3) /*  011b - Load/store word and unsigned byte and Media instructions */
#define INST_CLASS_BL0     INST_CLASS_V(0x4) /*  10xb -  Branch, branch with link, and block data transfer */
#define INST_CLASS_BL1     INST_CLASS_V(0x5) /*  10xb -  Branch, branch with link, and block data transfer */
#define INST_CLASS_CPSV0   INST_CLASS_V(0x6) /*  11xb -  Coprocessor instructions, and Supervisor Call */
#define INST_CLASS_CPSV1   INST_CLASS_V(0x7) /*  11xb -  Coprocessor instructions, and Supervisor Call */


/* Load and store operations */
#define INST_CLASS_LS_OP1_SHIFT  20
#define INST_CLASS_LS_OP1_V(x) (x  << INST_CLASS_LS_OP1_SHIFT)
#define INST_CLASS_LS_OP1_MASK INST_CLASS_LS_OP1_V(0x1F)

#define INST_CLASS_LS_RN_SHIFT  16 /* source register */
#define INST_CLASS_LS_RN_V(x) (x  << INST_CLASS_LS_RN_SHIFT)
#define INST_CLASS_LS_RN_MASK INST_CLASS_LS_OP1_V(0xF)

#define INST_CLASS_LS_RN_LITERAL  INST_CLASS_LS_RN_V(0xf) /* Literal e.g. not from a register */

#define INST_CLASS_LS_RT_SHIFT  12 /* destination register */
#define INST_CLASS_LS_RT_V(x) (x  << INST_CLASS_LS_RT_SHIFT)
#define INST_CLASS_LS_RT_MASK INST_CLASS_LS_OP1_V(0xF)

//http://blogs.arm.com/software-enablement/251-how-to-load-constants-in-assembly-for-arm-architecture/
//http://www.opensource.apple.com/source/lldb/lldb-69/source/Plugins/Process/Utility/ARMUtils.h
#define IMM12_SHIFT  0
#define IMM12_V(x) (x << IMM12_SHIFT)
#define IMM12_MASK IMM12_V(0xfff)

#define INST_CLASS_LS_RT_V(x) (x  << INST_CLASS_LS_RT_SHIFT)
#define INST_CLASS_LS_RT_MASK INST_CLASS_LS_OP1_V(0xF)

/*
Load Register (literal) calculates an address from the PC value and an immediate offset, loads a word from memory,
and writes it to a register. For information about memory accesses see Memory accesses on page A8-294.
*/

#define INST_CLASS_LS_OP1_LOAD_REG_LITERAL INST_CLASS_LS_OP1_V(0x19) /* 11001 */

#define LDR_LITERAL(cond,rt,value)  ( \
	(cond & INST_COND_MASK) \
	| INST_CLASS_LS0 /* A=0 */  \
	| INST_CLASS_LS_OP1_LOAD_REG_LITERAL \
	| INST_CLASS_LS_RN_LITERAL \
	| INST_CLASS_LS_RT_V(rt)\
	| IMM12_V(value) )

/* Data processing (LITERAL) */
#define INST_CLASS_DPMISC1_OP_SHIFT  20 /* op */
#define INST_CLASS_DPMISC1_OP_V(x) (x  << INST_CLASS_DPMISC1_OP_SHIFT)
#define INST_CLASS_DPMISC1_OP_MASK INST_CLASS_DPMISC1_OP_V(0x1F)

#define INST_CLASS_DPMISC1_OP_MOV_IM INST_CLASS_DPMISC1_OP_V(0x1a) /* 11010b */
//1110 001 1 1010 00000001000000101000b

#define INST_CLASS_DPMISC1_OP_MOV_RD_SHIFT  12 /* destination register */
#define INST_CLASS_DPMISC1_OP_MOV_RD_V(x)  (x << INST_CLASS_DPMISC1_OP_MOV_RD_SHIFT) 


#define MOV_LITERAL(cond,rd,value)  ( \
	(cond & INST_COND_MASK) \
	| INST_CLASS_DPMISC1 \
	| INST_CLASS_DPMISC1_OP_MOV_IM \
	| INST_CLASS_DPMISC1_OP_MOV_RD_V(rd) \
	| IMM12_V(value)  )
