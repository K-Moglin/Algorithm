#include <iostream>
#include <vector>
#include "sort.h"

int main() {
	std::vector<int> nums(15);

	for (int& i : nums) {
		i = rand();
	}

	std::cout << "Raw Vector: ";
	for (int i : nums) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	bubbleSort(nums);

	std::cout << "Sorted Vector : ";
	for (int i : nums) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
	
	return 0;
}