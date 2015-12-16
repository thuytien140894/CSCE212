/* 
 * CS:APP Data Lab 
 * 
 * <Tien Ho - 00111065>
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
 *
 * This function makes use of the Demorgan's law.
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
 *
 * This function uses the mask of 0xFF and performs the bitwise AND with the 
 * word x shifted to the left n bytes to extract the byte n.
 */
int getByte(int x, int n) {
  int numberOfBits = n * 8;
  int mask = 0xFF; 
  int temp = x >> numberOfBits;

  return (mask & temp);
}

/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 * 
 * This function performs the bitwise AND between the mask and the integer x 
 * arithmetically shifted to the right n bytes in order to remove the repeating 
 * sign bit.
 */
int logicalShift(int x, int n) { 
  int mask = ~((1 << 31) & ((!!n) << 31)) >> ((!n|n) + (~1 + 1));

  return (x >> n) & mask;
}

/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 *
 * This functions iteratively performs the bitwise AND between the mask of 1
 * and the integer x shifted to the right 1 bit each time.  Each time 1 is 
 * encountered in x, the number of 1's is incremented.
 */
int bitCount(int x) {
  int numberOfOnes = 0;

  numberOfOnes += (x & 1);
  numberOfOnes += ((x >> 1) & 1);
  numberOfOnes += ((x >> 2) & 1);
  numberOfOnes += ((x >> 3) & 1);
  numberOfOnes += ((x >> 4) & 1);
  numberOfOnes += ((x >> 5) & 1);
  numberOfOnes += ((x >> 6) & 1);
  numberOfOnes += ((x >> 7) & 1);
  numberOfOnes += ((x >> 8) & 1);
  numberOfOnes += ((x >> 9) & 1);
  numberOfOnes += ((x >> 10) & 1);
  numberOfOnes += ((x >> 11) & 1);
  numberOfOnes += ((x >> 12) & 1);
  numberOfOnes += ((x >> 13) & 1);
  numberOfOnes += ((x >> 14) & 1);
  numberOfOnes += ((x >> 15) & 1);
  numberOfOnes += ((x >> 16) & 1);
  numberOfOnes += ((x >> 17) & 1);
  numberOfOnes += ((x >> 18) & 1);
  numberOfOnes += ((x >> 19) & 1);
  numberOfOnes += ((x >> 20) & 1);
  numberOfOnes += ((x >> 21) & 1);
  numberOfOnes += ((x >> 22) & 1);
  numberOfOnes += ((x >> 23) & 1);
  numberOfOnes += ((x >> 24) & 1);
  numberOfOnes += ((x >> 25) & 1);
  numberOfOnes += ((x >> 26) & 1);
  numberOfOnes += ((x >> 27) & 1);
  numberOfOnes += ((x >> 28) & 1);
  numberOfOnes += ((x >> 29) & 1);
  numberOfOnes += ((x >> 30) & 1);
  numberOfOnes += ((x >> 31) & 1);

  return numberOfOnes;
}

/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 * 
 * This functions uses the fact that the two's complement of 0 is 
 * always 0.  Therefore, if the bitwise OR between x and its two's complement
 * is 1, this implies x is nonzero and therefore is true.  Otherwise, it is 
 * false.
 */
int bang(int x) {
  int two_complement = ~x + 1;
  int mask = ~((two_complement | x) >> 31);

  return (mask & 1);
}

/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 *
 * This function shifts the integer 1 to the left 31 bit to obtain the 
 * smallest two's complement integer. 
 */
int tmin(void) {
  return 1 << 31;
}

/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 *
 * This function first determines the smallest and largest two's complement
 * integers that can be represented in n bits.  Then the difference between 
 * the integer x and TMIN and TMAX is calculated.  An integer that can be 
 * represented in n bit needs to be greater than TMIN and less than TMAX.
 */
int fitsBits(int x, int n) {
  int tmin = ~((1 << (n + (~1 + 1))) + (~1 + 1));
  int tmax = (1 << (n + (~1 + 1))) + (~1 + 1);
  int biggerThanTmin = !((x + (~tmin + 1)) >> 31);
  int smallerThanTmax = !((tmax + (~x + 1)) >> 31);

  return (biggerThanTmin & smallerThanTmax); 
}

/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 *
 * This function takes into account that arithmetically shifting 
 * two's complement integer that is less 0 will result in the 
 * ceiling(x/2^n) instead of te floor(x/2^n).  Therefore, a bias of 
 * (2^n -1) added to x is considered before shifting.  For x > 0,
 * the bias is 0, and normal arithmetic left shift is performed.
 */
int divpwr2(int x, int n) {
  int mask = 1 << 31;
  int tmp = (mask & x) >> 31;
  int bias = (1 << (n & tmp)) + (~1 + 1);

  return (x + bias) >> n; 
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 *
 * This function returns the two's complement of x, which is equivalent
 * to the multiplication of -1.
 */
int negate(int x) {
  return (~x + 1);
}

/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 *
 * This function returns 1 if x is not zero and x is a positive integer.
 */
int isPositive(int x) { 
  //not a zero and positive
  return (!!(x) & (!(x >> 31)));
}

/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 *
 * This function checks whether y is greater than x.  
 * If x and y have the same sign, then y - x needs to be positive.
 * If x and y have different signs, then x needs to be negative.
 */
int isLessOrEqual(int x, int y) {
  int x_sign = (x >> 31) & 1;
  int y_sign = (y >> 31) & 1;
  int same_sign = x_sign & !y_sign; 
  int different_sign = !(x_sign ^ y_sign) & !((y + ~x + 1) >> 31);

  return (same_sign | different_sign);
}

/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 *
 * This function returns the bit position of the most significant 1 in x
 * by iteratively performing a bitwise AND between the mask of 0x80000000
 * shifted to the right 1 bit at each time and x.  The bit position, which 
 * is initialized to 31, is decremented until the first 1 in x is encountered.    
 */
int ilog2(int x) { //the most significant bit
  int mostSignificantBit = 31;
  int mask = 1 << 31;

  mostSignificantBit += ~(!(x & mask)) + 1;
  mostSignificantBit += ~(!(x & (mask >> 1))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 2))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 3))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 4))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 5))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 6))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 7))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 8))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 9))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 10))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 11))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 12))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 13))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 14))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 15))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 16))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 17))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 18))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 19))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 20))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 21))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 22))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 23))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 24))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 25))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 26))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 27))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 28))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 29))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 30))) + 1;
  mostSignificantBit += ~(!(x & (mask >> 31))) + 1;

  return mostSignificantBit;
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
 *
 * This function tests for NaN when the exponent field is all 1s and the 
 * fraction field is nonzero.  The bitwise XOR is performed between the mask
 * of 0x80000000 and uf to negate the sign bit of the float.    
 */
unsigned float_neg(unsigned uf) {
  unsigned exponent = uf >> 23 & 0xFF;
  unsigned fraction = uf & 0x7FFFFF; 
  if (exponent == 0xFF && fraction != 0)
     return uf;

  unsigned mask = 1 << 31;
  return (uf ^ mask);
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 *
 * This function determines the sign, exponent, and fraction fields for 
 * conversion from the integer x to its floating point representation.
 * Rounding problems.  
 */
unsigned float_i2f(int x) {
  if (x == 0)
    return x;

  int sign = (1 << 31) & x;
  
  unsigned temp;
  if (sign != 0)
    temp = ~x + 1;
  else 
    temp = x;

  unsigned temp1 = temp;
  unsigned numberOfFrac = 0;

  while (temp != 1) 
  {
    temp = temp >> 1;
    numberOfFrac += 1;
  }
  
  unsigned fraction;
  if (numberOfFrac <= 23)
    fraction = (temp1 << (23 - numberOfFrac)) & 0x7FFFFF;
  else
  {
    unsigned tmp = (0x7FFFFF << (numberOfFrac - 23)) & temp1;
    fraction = tmp >> (numberOfFrac - 23);
  }

  unsigned exponent = (numberOfFrac + 127); 

  unsigned float_number = (sign | (exponent << 23) | fraction);

  return float_number;  
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
 *
 * This function considers three cases.  When the argument is denormalized, 
 * the fraction field is multiplied by 2. For normalized arguments, the  
 * exponent field is incremented by 1.  For NaN, infinity, and zero, 
 * the function returns the argument.
 */
unsigned float_twice(unsigned uf) {
  unsigned exponent = uf >> 23 & 0xFF;
  unsigned fraction = uf & 0x7FFFFF; 
  unsigned sign = (1 << 31) & uf;
  
  if (exponent == 0 && fraction != 0) 
    fraction = fraction << 1;
  else if (exponent != 0 && exponent != 0xFF)
    exponent++;
  else
    return uf;

  return sign | (exponent << 23) | fraction;
}
