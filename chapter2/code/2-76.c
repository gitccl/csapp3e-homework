void *malloc(size_t size);
void *memset(void *s, int c, size_t n);

/**
 * 实现calloc
 */
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