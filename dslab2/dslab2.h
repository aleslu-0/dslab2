#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Object {
private:
	string name;
	int age;
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
public:
	LinearTable() {
		t.resize(11);
		size = 0;
		capacity = t.capacity();
		for(int i = 0; i < 11; i++){
			t[i] = nullptr;
		}
	};
	int getTableSize() {
		return t.capacity();
	}
	void addObject(string x, int y){
		if ((size / capacity) >= 0.6) {
			reHash(x, y);
		}
		int temp = 0;
		for(int i = 0; i < x.size(); i++){
			temp = temp + int(x[i]);
		}
		int index = (temp) % capacity;//name -> ascii, name * age % size

		//check if index place is empty(add or check next) (extend vector if needed)
		if(t[index] == nullptr){//does this empty check work?
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
				//start from the beginning if it didnt find a slot
				//if the loop comes back to the original "firstplace" index then extend vector with next prime
			}
			//if (!foundPlace) {
			//	for (int i = 0; i < index; i++) {
			//		if (t[i] == nullptr) {
			//			Object* holder = new Object(x, y);
			//			t[i] = holder;
			//			size++;
			//			foundPlace = true;
			//			break;//breaks if it finds a slot
			//		}
			//	}
			//}
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
				cout << t[i]->getName() << " " << t[i]->getAge() << " " << i << endl;//lets try it without the display table
		} 
	}

	void reHash(string x, int y){
		vector<Object*> tempArray;//are we suppose to use a temporrary array while moving the objects back into the original array?
				//tempArray.resize(size);
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
			int temp = 0;

			for (int i = 0; i < name.size(); i++) {
				temp = temp + int(name[i]);
			}
			int index = (temp) % capacity;

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
		addObject(x, y);
	}
};