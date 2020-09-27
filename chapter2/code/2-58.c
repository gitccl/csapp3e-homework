
/**
 * @author ccl
 * 判断系统是否为小端存储方式
 */
int is_little_endian() {
	static long val = 1;
	return *(char * ) &val == 1;
}
