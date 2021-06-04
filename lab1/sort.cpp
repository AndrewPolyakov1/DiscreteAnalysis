#include "sort.hpp"
#include <iostream>

namespace NSort {

    void counting_sort(NVector::TVector<NMytypes::TPair<int,  char[65]>>& elems, unsigned max_elem)
    {
        
        if(elems.is_empty()){
            return;
        }

        NVector::TVector<unsigned int> account(max_elem + 1, 0);

        //Accounting number of each key
        for (size_t i = 0; i < elems.size(); ++i) {
            
            account[elems[i].key]++;
        }


        //Подсчет частичных сумм(элементы, ключ которых не превышшает i)
        for (size_t i = 1; i < account.size(); ++i) {
            account[i] += account[i - 1];
        }

        NVector::TVector<NMytypes::TPair<int,  char[65]>> result(elems.size());

        for (int i = elems.size() - 1; i >= 0; --i) {
           
            result[account[elems[i].key] - 1] = elems[i];
            --account[elems[i].key];
        }


        for (size_t i = 0; i < elems.size(); ++i) {
            std::swap(result[i], elems[i]);
        }
    }
}