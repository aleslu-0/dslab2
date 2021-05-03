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
	int size = t.capacity();
public:
	LinearTable() {
		t.resize(11);
		for(int i = 0; i < 11; i++){
			t[i] = nullptr;
		}
	};
	int getTableSize() {
		return t.capacity();
	}
	void addObject(string x, int y){
		int temp;
		for(int i = 0; i < x.size(); i++){
			temp = temp + int(x[i]);
		}
		int index = (temp * y) % getTableSize();//name -> ascii, name * age % size

		//check if index palce is empty(add or check next) (extend vector if needed)
		if(t[index] == nullptr){//does this empty check work?
			Object* holder = new Object(x, y);
			t[index] = holder;
		}
		else{

			int firstPlace = index;

			for(int i = index + 1; i < size; i++){
				if(t[i] == nullptr){
					Object* holder = new Object(x, y);
					t[i] = holder;
					break;//breaks if it finds a slot
				}
				//start from the beginning if it didnt find a slot
				//if the loop comes back to the original "firstplace" index then extend vector with next prime
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
				if(i == currentPrime -1)
					isPrime = true;
			}
			if(isPrime == true)
				return currentPrime;	
			currentPrime++;
		}		
	}
};