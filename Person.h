//U2410254 Tursunova Xurshida
#ifndef PERSON_H
#define PERSON_H
#include <iostream>
using namespace std;

//abstract class person
class Person
{
protected:
	string name;
public:
	Person(string name): name(name) {}

	virtual string getName() = 0;

    virtual void displayName(){}

	virtual ~Person() {}
};

class User :public Person {

public:
	User(string name ): Person(name){}

	string getName() final {
		return name;
	}

	void displayName() final{
		cout << "Name:" << name << endl;
	}

	~User() = default;
};

class Admin :public Person {

public:
	Admin(string name):Person(name){}

	string getName() final{
		return name;
	}

	void displayName() final{
		cout << "Name:" << name << endl;

	}

	~Admin() = default;
};

#endif