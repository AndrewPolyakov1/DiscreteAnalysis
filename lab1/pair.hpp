#pragma once

#include <cstring>

namespace NMytypes {
	template<class T, class U >
	struct TPair
	{
		T key;
		U value;
		TPair(): key(0), value("") {}
		TPair(T fir, U sec): key(fir), value(sec) {}
		~TPair() {}

		void print_pair() {
			printf("%d %s\n", this->key, this->value);
		}
		void set_pair(T key, U val){
			this->key = key;
			strcpy(this->value, val);
		}


	};
}
