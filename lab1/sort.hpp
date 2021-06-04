#pragma once
#include "vector.hpp"
#include "pair.hpp"



namespace NSort {
	void counting_sort(NVector::TVector<NMytypes::TPair<int, char[65]>>& elems, unsigned max_elem);

	NMytypes::TPair<int, char[65]>& max_elem(const NVector::TVector<NMytypes::TPair<int, char[65]>>& vector);

}
