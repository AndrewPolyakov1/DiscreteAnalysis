#include <iostream>
#include <string>
#include <algorithm>


int TrippleMin(int a, int b, int c) {
    return (std::min(a, b) < std::min(b, c)) ? std::min(a, b) : std::min(b, c);
}

int MinPath(int* array, int n) {
    array[0] = 0;
    array[1] = 0;
    for (int i = 2; i <= n; i++) {
	   if (i % 2 == 0 && i % 3 == 0) {
		  array[i] = i + TrippleMin(array[i / 2], array[i / 3], array[i - 1]);
		  continue;
	   }
	   if (i % 3 == 0) {
		  if (array[i / 3] < array[i - 1]) {
			 array[i] = i + array[i / 3];
		  } else {
			 array[i] = i + array[i - 1];
		  }
		  continue;
	   }

	   if (i % 2 == 0) {
		  if (array[i / 2] < array[i - 1]) {
			 array[i] = i + array[i / 2];
		  } else {
			 array[i] = i + array[i - 1];
		  }
		  continue;
	   }
	   array[i] = i + array[i - 1];
    }
    return array[n];
}

void ReconstructPath(int* array, int n) {
    int temp = n;
    while (temp > 1) {
	   if ((temp % 3 == 0) && (temp % 2 == 0)) {
		  if (array[temp / 3] <= array[temp / 2] && array[temp / 3] <= array[temp - 1]) {
			 std::cout << "/3" << ' ';
			 temp /= 3;
		  } else if (array[temp / 2] <= array[temp / 3] && array[temp / 2] <= array[temp - 1]) {
			 std::cout << "/2" << ' ';
			 temp /= 2;
		  } else {
			 std::cout << "-1";
			 temp--;
		  }
		  continue;
	   }
	   if (temp % 3 == 0) {
		  if (array[temp / 3] <= array[temp - 1]) {
			 std::cout << "/3" << ' ';
			 temp /= 3;
		  } else {
			 std::cout << "-1" << ' ';
			 temp--;
		  }
		  continue;
	   }
	   if (temp % 2 == 0) {
		  if (array[temp / 2] <= array[temp - 1]) {
			 std::cout << "/2" << ' ';
			 temp /= 2;
		  } else {
			 std::cout << "-1" << ' ';
			 temp--;
		  }
		  continue;
	   }
	   std::cout << "-1" << ' ';
	   temp--;
    }
    std::cout << std::endl;
}