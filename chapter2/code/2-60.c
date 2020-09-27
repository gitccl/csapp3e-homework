
/**
 * 假设我们将一个 w 位的字中的字节从0( 最低位）到w/8 - 1( 最高位）编号。写出下面 C 函数的代
 * 码，它会返回一个无符号值，其中参数 x 第 i 个字节被替换成字节 b:
 */
unsigned replace_byte ( unsigned x , int i , unsigned char b ) {
	/* u 代表无符号类型 */
	unsigned mask = ~ ( 0xFFu << ( i << 3 ) );
	unsigned rb = ( unsigned ) b << ( i << 3 );
	return ( x & mask ) | rb;
}

