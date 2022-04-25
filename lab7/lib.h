#include <iostream>
#include <string>
#include <algorithm>


int TrippleMin(int a, int b, int c) {
    return (std::min(a, b) < std::min(b, c)) ? std::min(a, b) : std::min(b, c);
}

// Iterate from 2 to n and find shortest path to every number. Base for dynamic is d0 = 0, d1 = 0
int MinPath(int* array, int n) {
    array[0] = 0;
    array[1] = 0;
    for (int i = 2; i <= n; i++) {
	   // If the number can be divided by 2 and 3
	   if (i % 2 == 0 && i % 3 == 0) {
		  // Choose best option by value from 3 previous points
		  array[i] = i + TrippleMin(array[i / 2], array[i / 3], array[i - 1]);
		  continue;
	   }
	   // If current number can be divided only by 3
	   if (i % 3 == 0) {
		  // Choose best option from 2 previous points
		  if (array[i / 3] < array[i - 1]) {
			 array[i] = i + array[i / 3];
		  } else {
			 array[i] = i + array[i - 1];
		  }
		  continue;
	   }
	   // If current number can be divided only by 2
	   if (i % 2 == 0) {
		  // Choose best option from 2 previous points
		  if (array[i / 2] < array[i - 1]) {
			 array[i] = i + array[i / 2];
		  } else {
			 array[i] = i + array[i - 1];
		  }
		  continue;
	   }
	   // we get here if current number can't be divided by 2 or 3, so there is only one previous point to choose
	   array[i] = i + array[i - 1];
    }

    // displays value of the shortest path from 1 to n
    return array[n];
}

// Get path to the minimal number going from 1 to n
void ReconstructPath(int* array, int n) {
    int temp = n;
    while (temp > 1) {
	   // if current number can be divided by 2 and 3
	   if ((temp % 3 == 0) && (temp % 2 == 0)) {
		  // then we choose best option by value from 3 previous points
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
	   // if current number can be divided only by 3
	   if (temp % 3 == 0) {
		  // then choose best option from 2 previous points
		  if (array[temp / 3] <= array[temp - 1]) {
			 std::cout << "/3" << ' ';
			 temp /= 3;
		  } else {
			 std::cout << "-1" << ' ';
			 temp--;
		  }
		  continue;
	   }
	   // if current number can be divided only by 2
	   if (temp % 2 == 0) {
		  // then choose best option from 2 previous points
		  if (array[temp / 2] <= array[temp - 1]) {
			 std::cout << "/2" << ' ';
			 temp /= 2;
		  } else {
			 std::cout << "-1" << ' ';
			 temp--;
		  }
		  continue;
	   }
	   // we get here if current number can't be divided by 2 or 3, so there is only one previous point to choose
	   std::cout << "-1" << ' ';
	   temp--;
    }
    std::cout << std::endl;
}