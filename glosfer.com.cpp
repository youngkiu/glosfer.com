// glosfer.com.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

/* https://www.linkedin.com/jobs/view/476326312/ */

#include "stdafx.h"
#include <math.h>

int get_max_xy(int n)
{
	int max_xy;
	int pow10;

	if (n >= 9) {
		max_xy = 0;
		pow10 = 1;
		while (n > 9) {
			max_xy += (9 * pow10);
			pow10 *= 10;
			n -= 9;
		}
		max_xy += ((n + 1) * pow10);
		max_xy -= 1;
	}
	else {
		max_xy = n;
	}

	return max_xy;
}

bool check_digit_sum(int x, int y, int n)
{
	int abs_x, abs_y;
	int digit_sum = 0;

	abs_x = abs(x);
	abs_y = abs(y);

	while (abs_x) {
		digit_sum += (abs_x % 10);
		abs_x /= 10;
	}
	while (abs_y) {
		digit_sum += (abs_y % 10);
		abs_y /= 10;
	}

	if (digit_sum > n) {
		return false;
	}

	return true;
}

bool check_valid(int x, int y, int n)
{
	if (check_digit_sum(x, y, n) == false) {
		return false;
	}

	if ((check_digit_sum(x - 1, y, n) == true) ||
		(check_digit_sum(x + 1, y, n) == true) ||
		(check_digit_sum(x, y - 1, n) == true) ||
		(check_digit_sum(x, y + 1, n) == true)) {
		return true;
	}

	return false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int n = 19;
	int max_xy;
	int x, y;
	int valid_point = 0;

	max_xy = get_max_xy(n);
	for (y = 0; y <= max_xy; y++) {
		for (x = 1; x <= max_xy; x++) {
			if (check_valid(x, y, n) == true) {
				valid_point++;
			}
		}
	}

	valid_point *= 4;	// quadrantal
	valid_point += 1;	// (0, 0)

	printf("Number of Point: %d \n", valid_point);

	return 0;
}

