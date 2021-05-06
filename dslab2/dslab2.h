#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "dslab2second.h"

using namespace std;


class LinearTable {
private:	
	vector<Object*> t;
	int capacity = t.capacity();
	int size;
	int collision;
	int collisionChain;
	bool ascii;
public:
	LinearTable(int enc) {
		t.resize(11);
		size = 0;
		collision = 0;
		collisionChain = 0;
		capacity = t.capacity();
		for(int i = 0; i < 11; i++){
			t[i] = nullptr;
		}
		ascii = enc;
	};
	bool getAscii() {
		return ascii;
	}
	int getTableSize() {
		return capacity;
	}
	int getTotalCol() {
		return collision;
	}
	int getColChain() {
		return collisionChain;
	}
	int getSize() {
		return size;
	}
	double getPercentage() {
		return (float(size) / float(capacity));
	}
	void addObject(string x, int y){
		int chain = 0;
		int index;
		if ((float(size) / float(capacity)) >= float(0.6)) {		
			reHash(x);
		}
		if(ascii)
			index = asciiHash(x);
		else
			index = djb2Hash(x);

		//check if index place is empty(add or check next) (extend vector if needed)
		if(t[index] == nullptr){
			Object* holder = new Object(x, y);
			t[index] = holder; 
			size++;
		}
		else {

			bool foundPlace = false;
			for (int i = index + 1; i < capacity; i++) {
				if (t[i] == nullptr) {
					Object* holder = new Object(x, y);
					t[i] = holder;
					size++;
					foundPlace = true;
					break;//breaks if it finds a slot
				}
				collision++;
				chain++;
				if(chain > collisionChain){
					collisionChain = chain;
				}
				//start from the beginning if it didnt find a slot
				//if the loop comes back to the original "firstplace" index then extend vector with next prime
			}
			if (!foundPlace) {
				for (int i = 0; i < index; i++) {
					if (t[i] == nullptr) {
						Object* holder = new Object(x, y);
						t[i] = holder;
						size++;
						foundPlace = true;
						break;//breaks if it finds a slot
					}
					collision++;
					chain++;
					if(chain > collisionChain){
						collisionChain = chain;
					}
				}
			}
		}
	}
	int nextPrime(int currentPrime) {
		currentPrime += currentPrime;
		bool isPrime = false;
		while (true) {
			for (int i = 2; i < currentPrime; i++) {
				if (currentPrime % i == 0)
					break;
				if (i == currentPrime - 1)
					isPrime = true;
			}
			if (isPrime == true)
				return currentPrime;
			currentPrime++;
		}
	}
		
	void displayTable() {
		for (int i = 0; i < t.capacity(); i++) {
			if(t[i] != nullptr)
				cout << t[i]->getName() << " " << t[i]->getAge() << " " << i << endl;
		} 
	}

	void reHash(string x){
		vector<Object*> tempArray;//are we suppose to use a temporrary array while moving the objects back into the original array?
		for (int i = 0; i < capacity; i++) {
			if (t[i] != nullptr) {
				tempArray.push_back(t[i]);
				t[i] = nullptr;
			}
		}
		t.resize(nextPrime(t.capacity()));
		capacity = t.capacity();
		cout << "Rehashing gave new size: " << t.capacity() << endl;
		for (int i = 0; i < tempArray.size(); i++) {
			string name = tempArray[i]->getName();
			int age = tempArray[i]->getAge();			
			int index;

			if(ascii)
				index = asciiHash(x);
			else
				index = djb2Hash(x);
			

			if (t[index] == nullptr) {
				t[index] = tempArray[i];
			}
			else {
				for (int b = index + 1; b < capacity; b++) {
					if (t[b] == nullptr) {
						t[b] = tempArray[i];
						break;
					}
				}
			}
		}
	}

	int asciiHash(string x) {
		int temp = 0;
		for (int i = 0; i < x.size(); i++) {
			temp = temp + int(x[i]);
		}
		int index = (temp) % capacity;//name -> ascii, name * age % size
		return index;
	}

	int djb2Hash(string x){
		unsigned long hash = 5381;
		for (auto c : x) {
			hash = (hash << 5) + hash + c; /* hash * 33 + c */
		}
		hash = hash % capacity;
		return hash;
	}
};
class HopScotchTable {
private:
	vector<Node*> t;
	/*Object* o;
	BitMap* b;*/
	int capacity = t.capacity();
	int size;
	int collision;
	int collisionChain;
	int h;
	bool ascii;
public:
	HopScotchTable(int enc) {
		t.resize(11);
		h = 4;
		size = 0;
		collision = 0;
		collisionChain = 0;
		capacity = t.capacity();
		ascii = enc;
		for (int i = 0; i < capacity; i++) {
			Node* holder = new Node();
			t[i] = holder;
		}
	}; //write logic to update the homenode to something shit i forgot

	int getTableSize() {
		return capacity;
	}
	int getTotalCol() {
		return collision;
	}
	int getColChain() {
		return collisionChain;
	}
	int getSize() {
		return size;
	}
	//void update(BitMap *bit, bool b, int p){
	//	bit->setElement(b, p);
	//}

	void addObject(string x, int y) {
		Object* oHolder = new Object(x, y);
		//BitMap bHolder = BitMap();////////////////////////?
		int chain = 0;
		int index = 0;
		if ((float(size) / float(capacity)) >= float(0.6)) {
			reHash(x, y);
		}
		if (ascii)
			index = asciiHash(x);
		else
			index = djb2Hash(x);

		bool foundPlace = false;

		if (t[index]->getObj() == nullptr) { //>:C
			t[index]->setObj(oHolder);
			oHolder->setHomeNode(chain);
			//t[index]->setBtm(bHolder);/////////////////////?
			//cout << index  << endl;
			t[index]->getBtm().setElement(1, chain);
			size++;
		}

		else {
			oHolder->setHomeNode(chain);
			//chain++;

			for (int i = 0; i < h; i++) {

				if (index + i > capacity - 1) {
					index = outOfBounds(index + i);
				}

				if (t[index + i]->getObj() == nullptr) {
					t[index + i]->setObj(oHolder);
					//t[index]->setBtm(bHolder);/////////////////////?
					//cout << index << endl;
					t[index + i]->getBtm().setElement(1, chain);//hm
					size++;
					foundPlace = true;
					break;//breaks if it finds a slot
				}
				collision++;
				chain++;
				if (chain > collisionChain) {
					collisionChain = chain;
				}
			}
			if (!foundPlace) {
				if (t[index]->getBtm().getAllTrue()) {
					reHash(x, y);
				}
				for (int i = 0; i < h; i++) {
					if (index + i > capacity - 1) {
						index = outOfBounds(index + i);
					}
					if (t[index]->getBtm().getElement(i) == true) {
						if (t[index + i]->getObj() == nullptr) {
							t[index + i]->setObj(oHolder);
							//t[index]->setBtm(bHolder);/////////////////////?
							//cout << index << endl;
							t[index + i]->getBtm().setElement(1, chain);//hm
							size++;
							break;
						}
						else {
							addObject(t[index + i]->getObj()->getName(), t[index + i]->getObj()->getAge());
							addObject(x, y);
						}
					}
				}

			}
		}
	}
	int outOfBounds(int i) {
		int reset = 0;
		reset = i - capacity;
		return reset;
	}

	int nextPrime(int currentPrime) {
		currentPrime += currentPrime;
		bool isPrime = false;
		while (true) {
			for (int i = 2; i < currentPrime; i++) {
				if (currentPrime % i == 0)
					break;
				if (i == currentPrime - 1)
					isPrime = true;
			}
			if (isPrime == true)
				return currentPrime;
			currentPrime++;
		}
	}
	void reHash(string x, int y) {
		vector<Node*> tempArray;

		for (int i = 0; i < capacity; i++) {
			if (t[i] != nullptr) {
				tempArray.push_back(t[i]);
				t[i] = nullptr;
			}
		}
		size = 0;
		t.resize(nextPrime(t.capacity()));
		capacity = t.capacity();

		for (int i = 0; i < capacity; i++) {
			Node* holder = new Node();
			t[i] = holder;
		}

		cout << "Rehashing gave new size: " << t.capacity() << endl;

		for (int i = 0; i < tempArray.size(); i++) {
			addObject(tempArray[i]->getObj());
		}

		//for (int i = 0; i < tempArray.size(); i++) {
		//	int index;

		//	if(ascii)
		//		index = asciiHash(x);
		//	else
		//		index = djb2Hash(x);
		//	

		//	if (t[index]->getObj() == nullptr) {
		//		
		//		//t[index] = addObject(tempArray[i]->getObj());
		//		t[index]->setObj(tempArray[i]->getObj());
		//	}
		//	else {
		//		for (int b = index + 1; b < capacity; b++) {
		//			if (t[b]->getObj() == nullptr) {
		//				
		//				//t[b] = addObject(tempArray[i]->getObj());
		//				t[b]->setObj(tempArray[i]->getObj());
		//				break;
		//			}
		//		}
		//	}
		//}
	}

	Node* addObject(Object* BABE) {
		int chain = 0;
		int index;
		if ((float(size) / float(capacity)) >= float(0.6)) {
			reHash(BABE->getName(), BABE->getAge());
		}
		if (ascii)//this shit fucked
			index = asciiHash(BABE->getName());
		else
			index = djb2Hash(BABE->getName());

		bool foundPlace = false;
		if (t[index] == nullptr) {
			t[index]->setObj(BABE);
			BABE->setHomeNode(chain);
			t[index]->getBtm().setElement(1, chain);
			size++;
		}

		else {
			BABE->setHomeNode(chain);
			chain++;

			for (int i = 0; i < h; i++) {

				if (index + i > capacity - 1) {
					index = outOfBounds(index + i);/////////////////////////////
				}

				if (t[index + i] == nullptr) {///////////////////////////////
					t[index + i]->setObj(BABE);
					t[index + i]->getBtm().setElement(1, chain);//hm
					size++;
					foundPlace = true;
					break;//breaks if it finds a slot
				}
				collision++;
				chain++;
				if (chain > collisionChain) {
					collisionChain = chain;
				}
			}
			if (!foundPlace) {
				if (t[index]->getBtm().getAllTrue() == true) {
					reHash(BABE->getName(), BABE->getAge());
				}
				for (int i = 0; i < h; i++) {
					if (index + i > capacity - 1) {///////////////////////////////
						index = outOfBounds(index + i);
					}
					if (t[index]->getBtm().getElement(i) == true) {
						if (t[index + i] == nullptr) {///////////////////////////
							t[index + i]->setObj(BABE);
							t[index + i]->getBtm().setElement(1, chain);//hm
							size++;
							break;
						}
						else {
							addObject(t[index + i]->getObj()->getName(), t[index + i]->getObj()->getAge());
							addObject(BABE->getName(), BABE->getAge());
						}
					}
				}

			}
		}
		return t[index];
	}

	int asciiHash(string x) {
		int temp = 0;
		for (int i = 0; i < x.size(); i++) {
			temp = temp + int(x[i]);
		}
		int index = (temp) % capacity;//name -> ascii, name * age % size
		return index;
	}

	int djb2Hash(string x) {
		unsigned long hash = 5381;
		for (auto c : x) {
			hash = (hash << 5) + hash + c; /* hash * 33 + c */
		}
		hash = hash % capacity;
		return hash;
	}

	void displayTable() {
		for (int i = 0; i < t.capacity(); i++) {
			if (t[i] != nullptr)
				cout << t[i]->getObj()->getName() << " " << t[i]->getObj()->getAge() << " " << i << endl;
		}
	}
};

