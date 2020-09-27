## Homework of chapter 2



### 2.58

> 判断系统是否为小端存储方式



```c
/**
 * @author ccl
 * 判断系统是否为小端存储方式
 */
int is_little_endian() {
	static long val = 1;
	return *(char * ) &val == 1;
}
```





### 2.59

>编写一个C表达式，它生成一个字，由x的最低有效字节和y中剩下的字节组成。对于运算数x=0x89ABCDEF 和 y=0x76543210, 就得到0x765432EF 。

```c
#define MASK 0xFF
#define generate_word( x , y ) ((x & MASK) | (y& (~MASK) ))
```



### 2.60

> 假设我们将一个 w 位的字中的字节从0( 最低位）到w/8 - 1( 最高位）编号。写出下面 C 函数的代码，它会返回一个无符号值，其中参数 x 第 i 个字节被替换成字节 b:

```c
unsigned replace_byte ( unsigned x , int i , unsigned char b ) {
	/* u 代表无符号类型 */
	unsigned mask = ~ ( 0xFFu << ( i << 3 ) );
	unsigned rb = ( unsigned ) b << ( i << 3 );
	return ( x & mask ) | rb;
}

```



### 2.61



- `x` 的每一位都等于1：`!~x`。
- `x` 的每一位都等于0：`!x`。
- `x` 的最低有效字节中的位都等于1
- `x` 的最高有效字节中的位都等于0



```c
#define MASK 0xFF

#define A( x ) (!(~x))
#define B( x ) (!x)

int C ( int x ) {
	return ( x & MASK ) == MASK;
}

int D ( int x ) {
	int shift = ( sizeof ( int ) - 1 ) << 3;
	return ! ( ( x >> shift ) & MASK );
}


```



### 2.62

> 编写函数 `int_shifts_are_arithmetic()` ，在对 `int` 类型的数使用算术右移的机器上生成1，反之生成0。要求在任意字长的机器上都可以运行。 

```c
int int_shifts_are_arithemetic(){
	int x = ~0;
	return !(x ^ (x >> 1));
}
```



### 2.63

> 函数 `srl()` 用算术右移来完成逻辑右移。函数 `sra()` 用逻辑右移来完成算术右移。不能使用右移或除法。 



```c
/**
 * 用逻辑右移实现算术右移
 * 将xsra的高k位置零即可
 */
unsigned srl ( unsigned x , int k ) {
	unsigned xsra = ( int ) x >> k;
	/* 将 xsra 的高k位置零 */
	int w = sizeof ( x ) << 3;
	unsigned mask = ~ ( ( (int) -1 ) << ( w - k ) );
	return xsra & mask;
}

/**
 * 用算术右移实现逻辑右移
 * 如果x >= 0, 答案就是xsrl
 * 如果x < 0, 将xsrl的高k位置1
 */
int sra ( int x , int k ) {
	int xsrl = ( unsigned ) x >> k;
	int w = sizeof ( x ) << 3;

	/* 构造一个mask, 如果x >= 0, mask = 0; 否则mask的高k位为1 */
	unsigned mask = ( ( (int) -1 ) << ( w - k ) ) ;
	int msb = ( x & (1 << (w - 1)) );
	mask &= (!msb) - 1;
	return xsrl | mask;
}
```





### 2.64

> 编写函数 `any_odd _one(x)` ，当 `x` 的二进制表示中的任一奇数位都为1时返回1，否则返回0。假设 w=32。 

```c
/**
 * Return 1 when any odd bit of x equals 1; 0 otherwise. Assume w=32
 */
int any_odd_one(unsigned x){
	/* 假设最低位为第0位 */
	return (x & 0xAAAAAAAA) != 0;
}
```



### 2.65

> 编写函数 `odd_ones(x)` ，当 `x` 的二进制表达含有奇数个1时返回1，否则返回零。设 w=32w=32。**代码中算术运算、位运算和逻辑运算最多只能包含12个。** 

```c
/**
 * Return 1 when x contains an odd number of 1s; 0 otherwise. Assume w=32.
 * 通过不断的异或来消除偶数个1
 */
int odd_ones ( unsigned x ) {
	x ^= x >> 16;
	x ^= x >> 8;
	x ^= x >> 4;
	x ^= x >> 2;
	x ^= x >> 1;
	return x & 0x1;
}
```



### 2.66 

>  生成一个掩码，取 `x` 的最高非零位。假设 w=32。**最多只能包含15个算术运算、位级运算和逻辑运算。** 

```c
/*
 * Generate mask indicating leftmost 1 in x. Assume w=32
 * For example, 0xFF00 -> 0x8000, and 0x6000 -> 0x4000.
 * If x = 0, then return 0
 */
int leftmost_one(unsigned x){
	/* 将x的最高非零位至最低为都置为1. 如 0x6000 -> 0x7FFF
	 * 然后取 x ^ (x >> 1)就能将最高位后的所有1置0
	 */
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	return x ^ (x >> 1);
}
```



### 2.67

>  编写一个过程 `int_size_is_32()` ，当在一个 `int` 是32位的机器上运行时产生1，而其他情况则产生0。不允许使用 `sizeof` 运算符。下面是一个错误的尝试： 

```c
int bad_int_size_is_32 () {
	int set_msb = 1 << 31;
	int beyond_msb = 1 << 32;
	return set_msb && ! beyond_msb;
}
```



> 请回答：
>
> 1. 这份代码在哪个方面没有遵守 C 语言标准？
> 1. 修改代码使得它在 `int` 至少为32位的任何机器上都能正确地运行。
> 1. 修改代码使得它在 `int` 至少为16位的任何机器上都能正确地运行。



1. 当int位32位时，左移32位超过了最大左移宽度，实际为 1 << (32 % 32) = 1 << 0 = 1



2. 

```c
/**
 * 判断 int 是否为32位
 * 该函数在 int 至少为32位的任何机器上都能正确地运行。
 */
int int_size_is_32 () {
	int set_msb = 1 << 31;
	int beyond_msb = set_msb << 1;
	return set_msb && ! beyond_msb;
}
```



3. 

```
/**
 * 判断 int 是否为32位
 * 该函数在 int 至少为16位的任何机器上都能正确地运行。
 */
int int_size_is_32_in16 () {
	/* 由于int可能为16位，因此最多只能左移15位 */
	int set_msb = ( ( 1 << 15 ) << 15 ) << 1;
	int beyond_msb = set_msb << 1;
	return set_msb && ! beyond_msb;
}
```





### 2.68

> 编写一个函数，生成一个掩码，将其最低 n 位置为 1 。其中 1 ≤ n ≤ w 。注意 n=w 的情况。



```c
int lower_one_mask(int n) {
	int w = sizeof(int) << 3;
	return ((unsigned) -1) >> ( w - n );
}
```



### 2.69

> 将x循环左移n位. Examples when x = 0x12345678 and w = 32. n=4 -> 0x23456781, n=20 -> 0x67812345.



```c
/**
 * Do rotating left shift. Assume O <= n < w
 * Examples when x = 0x12345678 and w = 32:
 * n=4 -> 0x23456781, n=20 -> 0x67812345
 * 循环左移n位
*/
unsigned rotate_left(unsigned x, int n){
	int w = sizeof(int) << 3;
	return x << n | (x >> (w - n - 1) ) >> 1  ;
}
```





### 2.70

>  编写一个函数，当 x 可以被表示为 n 位补码时返回1，否则返回0。其中 $1≤n≤w$ 。 

```c
/**
 * 例如n=8, 从截断的角度考虑.
 * int转为char值不变, 即 (char)x == x;
 * 对于任意的n，将x截断为n位后仍然和x相等，那么x就能用n位的二进制补码表示
 * 截断为n位就是 x << (w - n) >> (w - n)。(算术右移，不会改变原来的值)
 */
int fits_bits_1 ( int x , int n ) {
	int w = sizeof ( x ) << 3;
	int t = ( ( x << ( w - n ) ) >> ( w - n ) );
	return t == x;
}

/**
 * 再次的观察后可发现，x 能用 n 位的二进制补码表示的条件为
 * x 的前 w - n + 1 位要么全为 1, 要么全为 0.
 */
int fits_bits_2 ( int x , int n ) {
	int t = x >> ( n - 1 );
	return ! t || ! ~ t;
}

/**
 * 函数是正确的，但不符合条件，可以用于对拍。
 */
int fits_bits_3 ( int x , int n ) {
	int low = - ( 1U << ( n - 1 ) );
	int up = ( 1U << ( n - 1 ) ) - 1;
	return x >= low && x <= up;
}

```



### 2.71

> 从一个数x中提取一个字节，然后将其符号扩展为int。

```c
typedef unsigned packet_t;

/**
 * Extract byte from word. Return as signed integer.
 */
int xbyte ( packet_t word , int bytenum ) {
	int w = sizeof ( word );
	int shift = ( w - 1 - bytenum ) << 3;
	/* 先将待提取的字节移到最高位，然后算术右移即可 */
	int x = word << shift;
	return x >> ( ( w - 1 ) << 3 );
}
```



### 2.72



```c
void copy_int(int val, void* buf, int maxbytes) {
	if (maxbytes - (int) sizeof(val) >= 0) {
		memcpy(buf, (void*)&val, sizeof(val));
	}
}
```



### 2.73

>  实现饱和加法，将两个 `int` 类型的数 x 和 y 相加，若正溢出返回 `INT_MAX` ，负溢出返回 `INT_MIN` ，无溢出返回其和。 



```c
#include <limits.h>

int saturating_add(int x, int y) {
	int sum = x + y;
	int sig_mask = INT_MIN;
	/*
	 * if x > 0, y > 0 but sum < 0, it's a positive overflow
	 * if x < 0, y < 0 but sum >= 0, it's a negative overflow
	 */
	int pos_over = !(x & sig_mask) && !(y & sig_mask) && (sum & sig_mask);
	int neg_over = (x & sig_mask) && (y & sig_mask) && !(sum & sig_mask);

	(pos_over && (sum = INT_MAX) || neg_over && (sum = INT_MIN));

	return sum;
}
```



### 2.74

>  编写函数 `tsub_ok(int x, int y)` 来检测 x − y 是否溢出。 

```c
#include <limits.h>
int tsub_ok(int x, int y){
	int sub = x - y;
	int sig_mask = INT_MIN;
	/*
	 * pay attention to the case: (0 - INT_MIN)
	 * if x >= 0, y < 0 but sum < 0, it's a positive overflow.
	 * if x < 0, y >= 0 but sum >= 0, it's a negative overflow.
	 */
	int pos_over = !(x & sig_mask) && (y & sig_mask) && (sub & sig_mask);
	int neg_over = (x & sig_mask) && !(y & sig_mask) && !(sub & sig_mask);
	return !pos_over && !neg_over;
}
```





### 2.75



>  已知有函数 `int signed_high_prod(int x, int y)` 计算整型变量 `x` 和 `y` 相乘后高 $w$ 位的值。请编写 `unsigned unsigned_high_prod(unsigned x, unsigned y)` 来计算无符号型变量相乘后高 $w$ 位的值。 



设$x′$ 和 $y′$ 分别是 x 和 y 的无符号类型值. 书上的公式2-18如下

$$ x' * y' = x*y + (x_{w-1}*y + y_{w-1}*x)*2^w + (x_{w-1}*y_{w-1})*2^{2w}$$

 由于取得是高w位，因此一个数乘于$2^w$, 那么这个数就处于高$w$位中。同时$2^{2w}$不会改变位的表示. 

因此答案就是 $\text{signed_high_prod(x, y)} + x_{w-1}*y + y_{w-1}*x$

```c
unsigned unsigned_high_prod ( unsigned x , unsigned y ) {
	int w = sizeof(x) << 3;
	int sign_x = x >> ( w - 1 ) ;	// x_{w-1}
	int sign_y = y >> ( w - 1 ) ;    // y_{w-1}

	/* 后面两个乘法不用可以不用加(int)y * sign_x， sign_x要么为0要么为1 */
	return signed_high_prod ( ( int ) x , ( int ) y ) + y * sign_x + x * sign_y;
}
```



```c
/**
 * 下面两个函数用于对拍
 */
int signed_high_prod( int x, int y) {
	int64_t mul = (int64_t) x * y;
	return mul >> 32;
}


unsigned another_unsigned_high_prod(unsigned x, unsigned y) {
	uint64_t mul = (uint64_t) x * y;
	return mul >> 32;
}
```





### 2.76

> 库函数 `calloc` 有如下声明：`void *calloc(size_t nmemb, size_t size);` 。根据库文档：“函数 `calloc` 为一个数组分配内存，该数组有 `nmemb` 个元素，每个元素为 `size` 字节。内存设置为0。如果 `nmemb` 或 `size` 为0，则 `calloc` 返回 `NULL` 。”
>
> 编写 `calloc` 的实现，通过调用 `malloc` 执行分配，调用 `memset` 将内存设置为0。你的代码应该没有任何由算术溢出引起的漏洞，且无论数据类型 `size_t` 用多少位表示，代码都应该正常工作。
>
> 作为参考，函数 `malloc` 和 `memset` 声明如下：
>
> `void *malloc(size_t size); `
>
> `void *memset(void *s, int c, size_t n);`



判断乘法是否溢出即可.

```c
void *malloc(size_t size);
void *memset(void *s, int c, size_t n);

void *calloc(size_t nmemb, size_t size) {
	if(nmemb == 0 || size == 0) {
		return NULL;
	}
	int sz = nmemb * size ;
	if(sz / nmemb == size) // 乘法没有溢出
	{
		void* ptr = malloc(sz);
		if(ptr != NULL) {
			memset(ptr, 0, sz);
		}
		return ptr;
	}

	return NULL;
}
```





### 2.77

> 假设我们有一个任务：生成一段代码，将整数变量 `x` 乘以不同的常数因子 K 。为了提高效率，我们想只使用 `+` `-` `<<` 运算。对于下列 K 的值，写出执行乘法运算的 C 表达式，每个表达式中最多使用 3 个运算。
>
> - A. K=17
> - B. K=−7
> - C. K=60
> - D. K=−112



- `(x << 4) + x`

- `x - (x << 3)`
- `(x << 6) - (x << 2)`

- `(x << 4) - (x << 7)`





### 2.78

> 写出具有如下原型的函数的代码：
>
> ```c
> /* Divide by power of 2. Assume 0 <= k < w-1 */
> int divide_power2(int x, int k);
> ```



```c
/* Divide by power of 2. Assume 0 <= k < w-1 */
int divide_power2(int x, int k) {
	int w = sizeof(int) << 3;
	int neg = x >> (w - 1);
	neg && (x += (1 << k) - 1);
	return x >> k;
}
```



### 2.79

> 写出函数 mul3div4 的代码，对于整数参数x, 计算3 * x / 4, 但是要遵循位级整数编码规则。你的代码计算3*x 也会产生溢出。



```c
/* Divide by power of 2. Assume 0 <= k < w-1 */
int divide_power2(int x, int k) {
	int neg = x & INT_MIN;
	neg && (x += (1 << k) - 1);
	return x >> k;
}

int mul3div4(int x) {
	x = (x << 1) + x ;
	return divide_power2 (x, 2);
}
```





### 2.80 

>  写出函数 `threefourths` 的代码。对于整数参数 `x` ，计算 $\frac{3}{4}x$ 的值，向零舍入。它不会溢出。函数应该遵循位级整数编码规则。 

不溢出就需要先除以4，然后再乘于3，但是先出4再乘3就不对了，尾部的小数字原本在左移后是可以进位的，但是在右移的过程中会直接舍去！解决方法是将x分为两部分，前30位和后2位，分开计算再求和。

```c
former = x & ~0x3
later = x & 0x3
x = former + later
threefourths(x) = former/4*3 + later*3/4
```

`former`能被4整除，因此不会出现精度问题，`later`  无法被4整除，`later` 需要先乘3再除4.



```c
#include <limits.h>

int threefourths(int x) {
	int former = x & ~0x3;
	int later = x & 0x3;

	/* former / 4 * 3 */
	former >>= 2;
	former = (former << 1) + former;

	/* later * 3 / 4 */
	later = (later << 1) + later;
	int neg = x & INT_MIN;
	neg && (later += (1 << 2) - 1);
	later >>= 2;

	return former + later;
}
```





### 2.81

> 编写 C 表达式产生如下位模式，其中 $a^K$ 表示符号 a 重复 k 次。假设一个 w 位的数据类型。代码可以包含对参数 `j` 和 `k` 的引用，它们分别表示 j 和 k 的值，但是不能使用表示 w 的参数。 

- $1^{w-k}0^k$ : `-1 << k`
- $0^{w-k-j}1^k0^j$ : `(-1 << j) & (~(-1 << (k + j)))`



### 2.82

> 我们在一个int 类型值为32 位的机器上运行程序。这些值以补码形式表示，而且它们都是算术右移的。unsigned 类型的值也是32 位的。我们产生随机数 x 和 y, 并且把它们转换成无符号数，显示如下：
>
> ```c
> /* Create some arbitrary values */
> int x = random();
> int y = random();
> /* Convert to unsigned */
> unsigned ux = (unsigned) x;
> unsigned uy = (unsigned) y;
> ```
>
> 对千下列每个C表达式，你要指出表达式是否总是为1 。如果它总是为1, 那么请描述其中的数学原理。否则，列举出一个使它为0 的参数示例。



- A: `(x < y) == (-x > -y)`

- B: `((x + y) << 4) + y - x  = 17*y + 15*x​`

- C: `~x + ~y + 1 == ~(x + y)​`

- D: `(ux - uy) == -(unsigned) (y - x)​`

- E: `((x >> 2) << 2) <= x​`



- A: 错误. 当 `x = INT_MIN, y = 0` 时.
- B: 正确.
- C: 正确. $\text{~}x + \text{~}y + 1 = -x -y - 1= -(x + y) - 1 = \text{~}(x + y)$
- D: 正确. $  ux - uy = (uinsigned) (x - y) = -(unsigned)(y - x) $
- E: 正确. $(x >> 2) << 2 = x \& (\text{~}0x3)$ , 末尾的2位丢失了，所以小于或等于原来的值。 



### 2.83

> 一些数字的二进制表示是由形如0.yyy...无穷串组成的， 其中 y 是一个k位的序列。 例如1/3 的二进制数字表示是0.010101...(y=01)， 而1/5的二进制表示是0.00110011...(y=0011) 
>
> A 设 $Y = B2U_k(y)$，也就是说，这个数字具有二进制表示y。给出一个由Y和k 组成的公式表示这个无穷串的值。
> B 对于下面的y值， 串的数值是多少？
> a) 101
> b) 0110
> c) 010011 



A:  设 n 为原来的数。 $n << k = Y + n$ 即： $n = \frac{Y}{(2^k -1)}$ 

B:  a) n = 5 / 7. b) n = 6 / 15 = 2 / 5. c) n = 19 / 63



### 2.84

> 填写下列程序的返回值， 这个程序测试它的第一个参数是否小于或者等于第二个参数。 假定函数f2u返回一个32位无符号数字，其位表示与它的浮点参数相同。 你可以假设两个参数都不是NaN, 两种0, +0,-0被认为是相等的。 



```c
int float_le(float x, float y)
{
	unsigned ux = f2u(x);
	unsigned uy = f2u(y);

	unsigned sx = ux >> 31;
	unsigned sy = uy >> 31;
	
	/**
	 * +0 and -0
	 * x <= 0 && y >= 0
	 * x >= 0 && y >= 0 && ux <= uy
	 * x < 0 && y < 0 && ux >= uy
	 */
	return  ((ux << 1) == 0 && (uy << 1) == 0) || 	// 
		  	(sx && !sy) ||							// 
			(!sx && !sy && ux <= uy) ||				// 
			(sx && sy && ux >= uy) ;				// 
}
```





### 2.85





 