#include <iostream>
#include "vector.hpp"
#include "sort.hpp"
#include "pair.hpp"
#include <fstream>
#include <cstdlib>
#include <string>

int main(){
	//Ускорение считывания
	std::ios_base::sync_with_stdio(false);
    
    std::cin.tie(nullptr);

	NVector::TVector<NMytypes::TPair<int, char[65]>> elems;
	NMytypes::TPair<int, char[65]> elem;
	int key;
	char value[65];	
	//Поиск максимального элемента
	int max_elem = -1;
	while (std::cin >> key >> value) {
		elem.set_pair(key,value);
		elems.push_back(elem);
		if (elem.key > max_elem) max_elem = elem.key;
	}

	NSort::counting_sort(elems, max_elem);

	for (size_t i = 0; i < elems.size(); ++i) {
		elems[i].print_pair();
	}
	return 0;
}