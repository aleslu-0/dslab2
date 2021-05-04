#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Object {
private:
	string name;
	int age;
	int homeNode;
public:
	Object(string x, int y){
		name = x;
		age = y;
	}
	string getName(){
		return(name);
	}
	int getAge(){
		return(age);
	}
	void setName(string x){
		name = x;
	}
	void setAge(int x){
		age = x;
	}
};

class LinearTable {
private:	
	vector<Object*> t;
	int capacity = t.capacity();
	int size;
	int probe;
	int collision;
	int collisionChain;
public:
	LinearTable() {
		t.resize(11);
		size = 0;
		probe = 0;
		collision = 0;
		collisionChain = 0;
		capacity = t.capacity();
		for(int i = 0; i < 11; i++){
			t[i] = nullptr;
		}
	};
	int getTableSize() {
		return t.capacity();
	}
	int getTotalCol() {
		return collision;
	}
	int getColChain() {
		return collisionChain;
	}
	void addObject(string x, int y){
		int chain = 0;
		if ((size / capacity) >= 0.6) {		
			reHash(x);
		}
		int index = asciiHash(x);
		//int index = djb2Hash(x);
		//int temp = 0;
		//for(int i = 0; i < x.size(); i++){
		//	temp = temp + int(x[i]);
		//}
		//int index = (temp) % capacity;//name -> ascii, name * age % size

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

		for (int i = 0; i < tempArray.size(); i++) {
			string name = tempArray[i]->getName();
			int age = tempArray[i]->getAge();			

			int index = asciiHash(x);
			//int index = djb2Hash(x);
			

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
	vector<Object*> t;
	int capacity = t.capacity();
	int size;
	int probe;
	int collision;
	int collisionChain;
	int h;
public:
	HopScotchTable() {
		h = 4;
	};

	void addObject(string x, int y){
		int chain = 0;
		if ((size / capacity) >= 0.6) {
			reHash(x, y);
		}
		int index = asciiHash(x);

		if(t[index] == nullptr){
			Object* holder = new Object(x, y);
			t[index] = holder; 
			size++;
		}
		else {

			bool foundPlace = false;
			for (int i = index + 1; i < h + index; i++) {
				if (t[i] == nullptr) {
					Object* holder = new Object(x, y);
					t[i] = holder;
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
	void reHash(string x, int y) {
		//bruh
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

	void displayTable() {
		for (int i = 0; i < t.capacity(); i++) {
			if (t[i] != nullptr)
				cout << t[i]->getName() << " " << t[i]->getAge() << " " << i << endl;
		}
	}
};