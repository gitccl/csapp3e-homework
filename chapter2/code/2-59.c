/**
 * 编写一个C表达式，它生成一个字，由x的最低有效字节和y中剩下的字节组成。对于运算数
 * x=0x89ABCDEF 和 y=0x76543210, 就得到0x765432EF 。
 */
#define MASK 0xFF
#define generate_word( x , y ) ((x & MASK) | (y& (~MASK) ))