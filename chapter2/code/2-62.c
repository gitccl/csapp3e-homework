
/**
 * 编写函数 int_shifts_are_arithmetic() ，在对 int 类型的数使用算术右移的机器上生成1，反之生成0。
 * 要求在任意字长的机器上都可以运行。
 */
int int_shifts_are_arithemetic(){
	int x = ~0;
	return !(x ^ (x >> 1));
}