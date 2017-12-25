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

bool find_path(int x0, int y0, int n)
{
	int x0_org, y0_org;
	bool find_x_path;
	bool find_y_path;

	x0_org = x0;
	y0_org = y0;

	find_x_path = true;
	while (x0 >= 10) {
		if (check_digit_sum(x0 - 1, y0_org, n) == false) {
			find_x_path = false;
			break;
		}

		x0 -= 10;
	}

	find_y_path = true;
	while (y0 >= 10) {
		if (check_digit_sum(x0_org, y0 - 1, n) == false) {
			find_y_path = false;
			break;
		}

		y0 -= 10;
	}

	if ((find_x_path == false) && (find_y_path == false)) {
		return false;
	}

	return true;
}

bool check_valid(int x, int y, int n)
{
	int prev_x0;
	int prev_y0;
	int pow10;

	if (check_digit_sum(x, y, n) == false) {
		return false;
	}

	pow10 = 10;
	do
	{
		prev_x0 = x - (x % pow10);
		prev_y0 = y - (y % pow10);

		if (find_path(prev_x0, prev_y0, n) == true)
			return true;

		pow10 *= 10;
	} while ((x >= pow10) && (y >= pow10));

	return false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int n = 19;
	int max_xy;
	int x, y;
	int valid_point = 0;
	bool valid;
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
			valid = check_valid(x, y, n);
			if (valid == true) {
				valid_point++;
			}

			fprintf(stream, "%s", (valid == true) ? ", 1" : ", 0");
		}
		fprintf(stream, "\n");
	}
	fclose(stream);

	valid_point *= 4;	// quadrantal
	valid_point += 1;	// (0, 0)

	printf("Number of Point: %d \n", valid_point);

	return 0;
}

