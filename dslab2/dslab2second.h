#include <iostream>
#include <vector>
#include <string>

using namespace std;

class BitMap {
private:
	vector<bool> bits;
public:
	BitMap() {
		for (int i = 0; i < 4; i++) {
			bits.push_back(0);
		}
	}
	void setElement(bool b, int p) {
		bits[p] = b;
	}
	bool getElement(int i) {
		return bits[i];
	}
	int getFirstTrue() {
		for (int i = 0; i < 4; i++) {
			if (bits[i]) {
				return i;
			}
		}
		return -1;
	}
	bool getAllTrue() {
		for (int i = 0; i < 4; i++) {
			if (bits[i] == false)
				return false;
		}
		return true;
	}
};

class Node {
private:
	Object* obj;
	BitMap* btm;
public:
	Node() {
		obj = nullptr;
		BitMap* temp = new BitMap;
		btm = temp;
	}
	Node(Object* bj) {
		obj = bj;
		BitMap* temp = new BitMap;
		btm = temp;
	}
	Object* getObj() {
		return(obj);
	}
	BitMap getBtm() {
		return(*btm);
	}
	void setObj(Object* o) {
		obj = o;
	}
	void setBtm(BitMap* b) {
		btm = b;
	}
};

class Object {
private:
	string name;
	int age;
	int homeNode;
public:
	Object(string x, int y) {
		name = x;
		age = y;
	}
	string getName() {
		return(name);
	}
	int getAge() {
		return(age);
	}
	void setName(string x) {
		name = x;
	}
	void setAge(int x) {
		age = x;
	}
	int getHomeNode() {
		return(homeNode);
	}
	void setHomeNode(int x) {
		homeNode = x;
	}
};

