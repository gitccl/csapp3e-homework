/**
 * Determine whether arguments can be subtracted without overflow.
 */
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