#pragma once


/*
 None-virtual member idiom

 no public virtual member for derived class to override
 instead, base calss provide a public none-virtual memeber function,
 and then a private virtual func to do it

*/

class GameCharacter
{
public:
	/*virtual int healthValue() const {
		return 1;
	}*/

	int healthValue() const { return doHealthValue(); }

private:

	//provide a default implementation, but derived class can override it
	virtual int doHealthValue() const { return 1; }
};


class BadGuy : public GameCharacter
{
public:
	//int healthValue() const override
	//{
	//	return 2;
	//}

	//Derived class can override base class's private virtual function
	int doHealthValue() const override
	{
		return 3;
	}

private:

};
