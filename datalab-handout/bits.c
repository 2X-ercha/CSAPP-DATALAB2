/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * name: 郭光沛
 * userid: 202001120131
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~(~x | ~y);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  /*
   * 0x12345678 >> (8*1) -> 0x??123456 (It's means Shift n) 
   * 0x??1234556 & 0xFF -> 0x00000056
   */
  return (x >> (n << 3)) & 0xFF;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  /*
   * 0x1 << 31 -> 0X80000000
   * 0X80000000 >> 31 -> 0XFFFFFFFF
   * 0XFFFFFFFF << (32 + ~n + 1) -> 0x1..00..(if n==0 -> (0xFFFFFFFF << (32%32)), so should << (32 + ~n) << 1)
   * ~0x1..00.. -> 0x0..11..
   * 0x0..11.. & (x >> n)
   */
  return (x >> n) & ~(0x1 << 31 >> 31 << (32 + ~n) << 1);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  // 定义掩码
  int mask_1 = 0x55 | (0x55 << 8);
  int mask1 = mask_1 | (mask_1 << 16);  // 01010101 01010101 01010101 01010101
  int mask_2 = 0x33 | (0x33 << 8);
  int mask2 = mask_2 | (mask_2 << 16);  // 00110011 00110011 00110011 00110011
  int mask_3 = 0x0F | (0x0F << 8);
  int mask3 = mask_3 | (mask_3 << 16);  // 00001111 00001111 00001111 00001111
  int mask4 = 0xFF | (0xFF << 16);      // 00000000 11111111 00000000 11111111
  int mask5 = 0xFF | (0xFF << 8);       // 00000000 00000000 11111111 11111111

  // example: 0xFD1592DA: 11111101 00010101 10010010 11011010
  x = (x & mask1) + ((x >> 1) & mask1);   // -> (10 10 10 01) (00 01 01 01) (01 01 00 01) (10 01 01 01)
  x = (x & mask2) + ((x >> 2) & mask2);   // -> ( 0100 0011 ) ( 0001 0010 ) ( 0010 0001 ) ( 0011 0010 )
  x = (x & mask3) + ((x >> 4) & mask3);   // -> (    111    ) (    011    ) (    011    ) (    101    )
  x = (x & mask4) + ((x >> 8) & mask4);   // -> (          01010          ) (          01000          )
  x = (x & mask5) + ((x >> 16) & mask5);  // -> (                        10010                        )
  return x;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  /*
  x |= x >> 16; x |= x >> 8;
  x |= x >> 4; x |= x >> 2;
  x |= x >> 1; return x & 0x1;
  */
  // In order to return 1, the msb must be 0 and the msb of the two's
  // additive inverse must be 0. This is because only 0 = -0 and the function
  // will only return 1 when x == 0.
  return ((x >> 31) | ((~x + 1) >> 31)) + 1;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return (0x1 << 31);
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  /*
   * x >>= n-1
   * now if x or x+1 is zero, ans = 1
   */
  x >>= n + ~0;
  return (!x | !(x + 1));
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  /*
  * -33 >> 4 = -3 (0xFFFFFFDF >> 4 = 0xFFFFFFFD(1101))
  * the target is 0xFFFFFFE(1110)
  * 33 is 0x21, 33 >> 4 -> 0x2
  * so if x<0, should give a offset
  * x<0 ans = ~((~x + 1) >> n) + 1
  * x>0 ans = x >> n
  */
  int flag = x >> 31;
  // return (~flag & (x >> n)) | (flag & (~((~x + 1) >> n) + 1));
  // return (~flag & (x >> n)) | (flag & (~(((~x + 1) >> n) & ~(1 << 31 )) + 1)); // 0x80000000,1
  // return (~flag & (x >> n)) | (flag & (~(((~x + 1) >> n) & ~(1 << 31 >> n << 1)) + 1)); // ops: 16
  return (~flag & (x >> n)) | (flag & ((~((~x + 1) >> n) | (1 << 31 >> n << 1)) + 1)); // 德摩率
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  return !((x >> 31 & 1) | !x); 
  // !(0x00000000 or 0x00000001) | (1 or 0);
  // 0 will be !(0 | 1) = 0
  // 1 will be !(0 | 0) = 1
  // -1 will be !(1 | 0) =0
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  // return ~((~x + y + 1) >> 31) & 0x1; 需要考虑异号溢出
  int signx = x >> 31;
  int signy = y >> 31;
  int flag = signx ^ signy;
  return (((!flag) & ~((~x + y + 1) >> 31)) | (flag & ~((~(x >> 1) + (y >> 1) + 1) >> 31))) & 0x1;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  int ans = 0;
  ans += ((!!(x >> 16)) << 4);        // 判断左16位是否为0， 否则ans = 1 << 4 = 16
  ans += ((!!(x >> (8 + ans))) << 3);
  ans += ((!!(x >> (4 + ans))) << 2);
  ans += ((!!(x >> (2 + ans))) << 1);
  ans += (!!(x >> (1 + ans)));
  return ans;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
  unsigned tmp = uf & 0x7FFFFFFF;
  unsigned result = uf ^ 0x80000000;
  if(tmp > 0x7F800000) result = uf;
  return result;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  unsigned sign;
  int tmpx = x;
  int f = 0;
  int delta = 0;
  int tail = 0;
  int E = 0;
  //特殊情况
  if (x == 0)
    return 0;
  if (x == 0x80000000)
    return 0xCF000000;
  //符号位
    sign = x & 0x80000000;
  //取绝对值
  if (sign)
    tmpx = -x;
  //计算移位数
  while ((tmpx >> E))
    E++;
  E = E - 1;
  //移位
    tmpx = tmpx << (31 - E);
  //尾数截掉八位
    tail = (tmpx >> 8) & 0x007FFFFF;
  //被截掉部分
    f = tmpx & 0xff;
  //向上舍入的情况
    delta = (f > 128) || ((f == 128) && (tail & 1));
    tail += delta;

  //阶码计算
    E = E + 127;
  
  //溢出判断
  if (tail >> 23) {
    tail = tail & 0x007FFFFF;
    E += 1;
  }
  return sign | E << 23 | tail;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  unsigned sign = uf >> 31 << 31;       // 符号位 0x0 or 0x1
  unsigned exp = uf >> 23 & 0xFF;       // 阶码
  unsigned frac = uf & ~(1 << 31 >> 8); // 尾数
  // 非规格化，不发生进位
  if (exp == 0 && frac < ~(1 << 31 >> 8))
    frac <<= 1;
  // 非规格化，发生进位
  else if (exp == 0 && frac == ~(1 << 31 >> 8)) {
    exp += 1;
    frac -= 1;
  }
  // 规格化, 进位到无穷
  else if (exp == 0xFE) {
    exp = 0xFF;
    frac = 0;
  }
  // 特殊值，无穷、NAN不变
  else if (exp == 0xFF)
    return uf;
  // 规格化，直接进位
  else
    exp += 1;
  return sign | (exp << 23) | frac;
}