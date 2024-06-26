/* 
 * CS:APP Data Lab 
 * 
 * <柯宇斌 2200013213>
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
/* Copyright (C) 1991-2022 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
/* 
 * bitXnor - ~(x^y) using only ~ and | 
 *   Example: bitXnor(6, -5) = 2
 *   Legal ops: ~ |
 *   Max ops: 7
 *   Rating: 1
 */
int bitXnor(int x, int y) {
  /*
   *~(x^y)=(x&y)|((~x)&(~y))
   *x&y=(~((~x)|(~y)))
   *~(x^y)=(~((~x)|(~y))))|(~(x|y)
   */
  return (~((~x)|(~y)))|(~(x|y));
}
/* 
 * bitConditional - x ? y : z for each bit respectively
 *   Example: bitConditional(0b00110011, 0b01010101, 0b00001111) = 0b00011101
 *   Legal ops: & | ^ ~
 *   Max ops: 4
 *   Rating: 1
 */
int bitConditional(int x, int y, int z) {
  /*
   *=(x&y)|((~x)^z)
   */
  return (x&y)|((~x)&z);
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 16
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
  /*
   *get i zijie using 0xff0000000
   *An=x&((0xff)<<(n<<3))     3 op
   *An=(x>>(n<<3))&0xff       3 op
   *Am=x&((0xff)<<(m<<3))     3 op
   *X1=x&(~((0xff)<<(n<<3))|((0xff)<<(n<<3))) 7 op
   */
   
    int varn=n<<3;
    int varm=m<<3;
    int var1=0xff;
    //取出字节
    
    int An=(x>>varn)&var1;
    int Am=(x>>varm)&var1;           
    int X1=x&(~((var1<<varn)|(var1<<varm)));
    int X2=X1+((An<<varm)|(Am<<varn));
    
    return X2;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int logicalShift(int x, int n) {
  /*
   *位移后保留后面的数利用之前的结论
   */
  return (~((0x1<<31)>>n<<1))&(x>>n);
}
/* 
 * cleanConsecutive1 - change any consecutive 1 to zeros in the binary form of x.
 *   Consecutive 1 means a set of 1 that contains more than one 1.
 *   Examples cleanConsecutive1(0x10) = 0x10
 *            cleanConsecutive1(0xF0) = 0x0
 *            cleanConsecutive1(0xFFFF0001) = 0x1
 *            cleanConsecutive1(0x4F4F4F4F) = 0x40404040
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 4
 */
int cleanConsecutive1(int x){
    /*
     *x,x<<1,x>>1，消去同为1的部分，
     * !!左侧为1会爆炸，所以>>1不能执行
     *
     */
     // return x^((x&(x<<1))|(x&(x>>1)));
    int var1 = (~x) | (~(x << 1));
    int var2 = var1 >> 1;
    return x & (var1 & var2);
   
}
/*
 * leftBitCount - returns count of number of consective 1's in
 *     left-hand (most significant) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Rating: 4
 */
int leftBitCount(int x) {
  /*
   *~x 最左侧0的个数
   *>>n后, x为0
   *二分,特判32
   *利用32-(n+1)=32+~n
   *不知道为什么N=N+1不能编译
   */
   int myx=~x;
   int var1=0x10;
   //int N=0x0;
   int bool1 = !!(myx>>var1);//为1则说明前16位有不为0的数
   //N=N+bool1<<4;
   int var2=0x8+(bool1<<4);
   int bool2 = !!(myx>>var2);
   int var3=0x4+(bool2<<3)+(bool1<<4);
   int bool3 = !!(myx>>var3);
   int var4=0x2+(bool3<<2)+(bool2<<3)+(bool1<<4);
   int bool4 = !!(myx>>var4); 
   int var5=0x1+(bool4<<1)+(bool3<<2)+(bool2<<3)+(bool1<<4);
   int bool5 = !!(myx>>var5); 
   int tp=!myx;//全为0是为1
   int final=32+(~(bool5+(bool4<<1)+(bool3<<2)+(bool2<<3)+(bool1<<4)))+tp;
  return final;
}
/* 
 * counter1To5 - return 1 + x if x < 5, return 1 otherwise, we ensure that 1<=x<=5
 *   Examples counter1To5(2) = 3,  counter1To5(5) = 1
 *   Legal ops: ~ & ! | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int counter1To5(int x) {
  /*
   *建构一个if器
   *
   *x^y=(x&~y)|(y&~x)
   */
   int val=5;
   int tmp=!((x&~val)|(val&~x));//x为5的时候是1
  return (x+2)+~((tmp<<2)+tmp);
}
/* 
 * sameSign - return 1 if x and y have same sign, and 0 otherwise
 *   Examples sameSign(0x12345678, 0) = 1, sameSign(0xFFFFFFFF,0x1) = 0
 *   Legal ops: ! ~ & ! ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int sameSign(int x, int y) {
  /*x>>31是符号位
   *y>>31是符号位
   取^后不相同为全1,否则为0
   */
  int var1=31;
  return !((x>>var1)^(y>>var1));
}
/*
 * satMul3 - multiplies by 3, saturating to Tmin or Tmax if overflow
 *  Examples: satMul3(0x10000000) = 0x30000000
 *            satMul3(0x30000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0x70000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0xD0000000) = 0x80000000 (Saturate to TMin)
 *            satMul3(0xA0000000) = 0x80000000 (Saturate to TMin)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 3
 */
int satMul3(int x) {
    /*
     *if器利用0xffffffff实现
     *符号当且仅当x1=x2,x1=x3溢出
     *
     */
    int x2 = x << 1;
    int x3 = x2 + x;
    int var1 = 1 << 31;
    int sgn1 = x & var1;//1负0正
    int sgn2 = x2 & var1;
    int sgn3 = x3 & var1;
    int sgn4 = ((sgn1^sgn2)|(sgn1^sgn3)) >> 31;//溢出为全1
    int final1 = (sgn1 >> 31);//sgn为1的时候为全1,否则为0;
    int final_ans_1 = (final1 & var1) + ((~final1) & (~var1));//sgn1为100000，否则为011111
    int final_ans = (sgn4 & final_ans_1) + ((~sgn4) & x3);
    return final_ans;
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
    /*
     *x+y-为1，符号相同不会溢出
     */
    int var1 = 1 << 31;
    int sgnx = x & var1;
    int sgny = y & var1;
    int sgn1 = !((sgnx) | (sgny ^ var1));//|两边仅仅在sgnx=0,sgny=var1是为0，此时sgn1为1
    int sgn2 = ((sgny) | (sgnx ^ var1))>>31;
    int val2 = x + (~y + 1);
    int sgn3 = (!(val2 & var1)) & (!!val2);//为正则1
    return (sgn2)&(sgn1 | sgn3);
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
    /*
     =x+(~y+1)
     y=Tmin,x>0特判
     */
    int newy = ~y;
    int var1 = 1 << 31;
    int xy = (x&(~var1)) + (newy&(~var1))+1;
    int sgnx = x & var1;
    int sgny = y & var1;
    int sgnxy = xy & var1;
    int final_1 = !(sgnx ^ sgny);//同号则为1
    int final_2 = !(sgnx ^ sgnxy);//同号则为1
    return (final_1) | final_2;
}

/*
 * trueFiveEighths - multiplies by 5/8 rounding toward 0,
 *  avoiding errors due to overflow
 *  Examples: trueFiveEighths(11) = 6
 *            trueFiveEighths(-9) = -5
 *            trueFiveEighths(0x30000000) = 0x1E000000 (no overflow)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 4
 */
int trueFiveEighths(int x)
{
  /*
   *显然前面位和后3位可以分开考虑
   *ANS1后，var1完全正常;只考虑var2;
   *负数需要特判
   *正数var2=
   */
    int var1=x>>3;
    int sgn =x>>31;//负数为全1
    int var2=x&0x7;
    int ANS1=var1+(var1<<2);
    int ANS2=(var2+(var2<<2)+(sgn&(0x7)))>>3;
    return ANS1+ANS2;
}
/* 
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {
    /*
      *考虑NaN,无穷,非规格化数，准规格化数，纯规格化数
      *近似问题:
      *00->0
      *01->0
      *10->0
      *11->1+0//从而只有后两位是11的时候要加1
      *准规格数0x00FFFFFF/2后实际上是0x00800000;刚好无需特判
     */
     //unsigned  s_ = uf&0x80000000;
     int var1 = 0x80000000;
     int var2 = 0x7F800000;
     int var3 = 0x007FFFFF;
     int var4 = 0x00000003;
     int var5 = 0x00800000;//用于阶码-1
     int var6 = 0x00400000;//用于非规格化数补1的情况
     int sgn = uf & var1;
     int pow = uf & var2;
     int pre = uf & var3;
     int up = !((uf & var4) ^ var4);
     if (!(pow ^ var2))return uf;//Nan,无穷
     if (!pow)return sgn + (pre >> 1) + up;//非规格化数x
     if (pow ^ var5)return sgn + pow - var5 + pre;  //大于1,纯规格化数
     return sgn + (var6 + (pre >> 1) + up);//临界
     
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
  /*
   *f为1+8+23;后23位只需找到最早的1即可
   *利用-x=~x+1.
   *包括一个舍入
   */
       //unsigned  s_ = uf&0x80000000;
    int n = 32;
    int var1 = 0x80000000;
    int sgn = x & var1;
    int var2 = 0x007fffff;
    int up = 0;
    int low8 = 0;
    if (sgn)x = ~x + 1;//负数则转换为正数
    if (!x)return 0x0;
    while ((!(x & var1)))x = x << 1, n--;
    //n表示第一个非0位及其右边的位数
    low8 = x & 0xff;
    up = (low8 > 128) || ((!(low8 ^ 128)) && (x & 0x00000100));
    x = x >> 8;//消去位数
    n--;
    return ((n + 127) << 23) + (x & var2) + up + sgn;
}
/* 
 * float64_f2i - Return bit-level equivalent of expression (int) f
 *   for 64 bit floating point argument f.
 *   Argument is passed as two unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   double-precision floating point value.
 *   Notice: uf1 contains the lower part of the f64 f
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 20
 *   Rating: 4
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    /*
     *1+11+(20+32)  -1024
     *2^31=2147483648
     *pow=31特判,pow<0直接为0
     *！向0舍入！
     *注意无需考虑非规格化数
     */
    int Tmin = 0x80000000;
    int sgn = uf2 & Tmin;
    int pow = ((uf2>>20) & 0x7ff) - 0x000003ff;
    unsigned small = Tmin + ((uf2 & (0x000fffff)) << 11) + ((uf1 >> 21) & 0x000007ff);
    //unsigned small2 = uf1 & 0x001fffff;
    if (pow > 30) {
        return Tmin;//sgn本身就是Tmin
    }
    if (pow & Tmin) {//pow<0
        return 0;
    }
    small = small >> (31 - pow);//有效的整数位
    if (sgn)return ~small + 1;
    return small;
}
/* 
 * float_negpwr2 - Return bit-level equivalent of the expression 2.0^-x
 *   (2.0 raised to the power -x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^-x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 20 
 *   Rating: 4
 */
unsigned float_negpwr2(int x) {
    /*
     *当x<=-128为+INF
     *当x<=126时，正常表达
     *当x<=149,非规格化数
     */
    if(x>149)return 0;
    else if(x>126)return 1<<(149-x);
    else if(x>-128)return (127-x)<<23;
    else return 255<<23;
}
