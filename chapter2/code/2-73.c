#include <limits.h>

/**
 * refer to https://dreamanddead.gitbooks.io/csapp-3e-solutions/content/chapter2/2.73.html
 */
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