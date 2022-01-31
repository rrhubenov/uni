// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// 
// Курсове Структури от данни и програмиране
//         Структури от данни
// Зимен семестър 2021/22 г.
// 
// Практически изпит
// 
// Име: Радослав Хубенов
// ФН: 45708
// Специалност: Информатика
// Курс: 3
// Административна група: 2
// Ден, в който се явявате на изпита: 31.01.22
// Начален час на изпита: 9:00
// Кой компилатор използвате: gcc

#include <cassert>
#include <iostream>

using namespace std;

enum class Drink {
	B,
	V,
	W,
	T,
	C,
	R,
	D,
	M
};

struct BarSlot {
	BarSlot* next;

	Drink* drinks;
	unsigned dcount;
	bool free;

	BarSlot(Drink* drinks, unsigned dcount): next(nullptr), drinks(drinks), dcount(dcount), free(true) {}

	void insert(Drink* drinks, unsigned dcount) {
		BarSlot* curr = this;

		while(curr->next != nullptr) {
			curr = curr->next;
		}

		curr->next = new BarSlot(drinks, dcount);
	}
};
struct Client {
	Client* next;
	Client* prev;

	Drink* drinks;
	unsigned dcount;

	Client(Drink* drinks, unsigned dcount): prev(nullptr), next(nullptr), drinks(drinks), dcount(dcount) {}

	void insert(Drink* drinks, unsigned dcount) {
		Client* curr = this;

		while(curr->next != nullptr) {
			curr = curr->next;
		}

		curr->next = new Client(drinks, dcount);
		curr->next->prev = curr;
	}

};

bool isCompat(BarSlot *bar, Client *client) {
	if(!bar->free) {
		return false;
	}
	bool dFound = false;

	for(unsigned i = 0; i < client->dcount; ++i) {
		for(unsigned j = 0; j < bar->dcount; ++j) {
			if(client->drinks[i] == bar->drinks[j]) {
				dFound = true;
				break;
			} 
		}
		if(!dFound) {
			return false;
		} else {
			dFound = false;
		}
	}

	return true;
}

bool place(BarSlot *bar, Client *clients) {
	Client* currC = clients;
	BarSlot* currB = bar;

	unsigned hops = 0;

	while(currB != nullptr && currC != nullptr){
		if(hops == 6) break;

		if(isCompat(currB, currC)) {
			hops = 0;
			currC = currC->next;
		} else {
			hops++;
		}
		currB = currB->next;
	}

	if(currC == nullptr) {
		return true;
	} else {
		return false;
	}

}

bool placeAll(BarSlot *bar, Client **groups, int groupCount) {
	bool canPlaceAll = true;

	for(unsigned i = 0; i < groupCount; ++i) {
		if(!place(bar, groups[i])) {
			canPlaceAll = false;
		}
	}

	return canPlaceAll;
}


int main()
{
	int cc, bs;

	cin >> cc >> bs;

	return 0;
}
