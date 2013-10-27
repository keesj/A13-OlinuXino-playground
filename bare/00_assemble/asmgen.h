

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
#define INST_CLASS_V(x) (x  << INST_COND_SHIFT)
#define INST_CLASS_MASK INST_COND_V(0x7)

/* The class bits [27:25] determine the instruction class , these value only hold if cond != INST_COND_AL */
#define INST_CLASS_DPMISC0 (0x0) /*  00xb - Data-processing and miscellaneous instructions 0 */
#define INST_CLASS_DPMISC1 (0x1) /*  00xb - Data-processing and miscellaneous instructions 0 */
#define INST_CLASS_LS0   (0x2) /*  010b - Load/store word and unsigned byte */
#define INST_CLASS_LS1   (0x3) /*  011b - Load/store word and unsigned byte and Media instructions */
#define INST_CLASS_BL0   (0x4) /*  10xb -  Branch, branch with link, and block data transfer */
#define INST_CLASS_BL1   (0x5) /*  10xb -  Branch, branch with link, and block data transfer */
#define INST_CLASS_CPSV0 (0x6) /*  11xb -  Coprocessor instructions, and Supervisor Call */
#define INST_CLASS_CPSV1 (0x7) /*  11xb -  Coprocessor instructions, and Supervisor Call */

/* DPMISC0 */
