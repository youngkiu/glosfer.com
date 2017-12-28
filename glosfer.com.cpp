// glosfer.com.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

/* https://www.linkedin.com/jobs/view/476326312/ */

#include "stdafx.h"
#include <math.h>
#include <stdio.h>

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

int get_num_of_digit(int x)
{
	int num_of_digit = 0;

	while (x) {
		num_of_digit++;
		x /= 10;
	}

	return num_of_digit;
}

int get_digit_num(int x, int digit)
{
	int i;

	for (i = 0; i < (digit - 1); i++) {
		x /= 10;
	}
	for (i = 0; i < (digit - 1); i++) {
		x *= 10;
	}

	return x;
}

bool check_valid(int x, int y, int n)
{
	int num_of_x_digit;
	int num_of_y_digit;
	int xi, yi;
	int x0, y0;

	if (check_digit_sum(x, y, n) == false) {
		return false;
	}

	num_of_x_digit = get_num_of_digit(x);
	num_of_y_digit = get_num_of_digit(y);

	for (xi = num_of_x_digit; xi > 0; xi--) {
		x0 = get_digit_num(x, xi);
		for (yi = num_of_y_digit; yi > 0; yi--) {
			y0 = get_digit_num(y, yi);

			if ((check_digit_sum(x0 - 1, y0, n) == false) &&
				(check_digit_sum(x0, y0 - 1, n) == false)) {
				return false;
			}
		}
	}

	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int n = 19;
	int max_xy;
	int x, y;
	int valid_point_count = 0;
	bool point_valid;
	FILE *stream;

	if ((fopen_s(&stream, "Point.csv", "w")) != 0) {
		printf("The file 'Point.csv' was not opened\n");
		return -1;
	}

	max_xy = get_max_xy(n);
	fprintf(stream, " ");
	for (x = 1; x <= max_xy; x++) {
		fprintf(stream, ", %d", x);
	}
	fprintf(stream, "\n");
	for (y = 0; y <= max_xy; y++) {
		fprintf(stream, "%d", y);

		for (x = 1; x <= max_xy; x++) {
			point_valid = check_valid(x, y, n);
			if (point_valid == true) {
				valid_point_count++;
			}

			fprintf(stream, "%s", (point_valid == true) ? ", 1" : ", 0");
		}
		fprintf(stream, "\n");
	}
	fclose(stream);

	valid_point_count *= 4;	// quadrantal
	valid_point_count += 1;	// (0, 0)

	printf("Number of Point: %d \n", valid_point_count);

	return 0;
}
