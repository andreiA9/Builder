#ifndef FIRST_CLASS_H
#define FIRST_CLASS_H

#include "SecondClass.h"

class FirstClass
{
public:
	FirstClass() {}
	
	void print()
	{
		std::cout << "FirstClass::print()\n";
		m_secondClass.print();
	}

private:
	SecondClass m_secondClass;
};

#endif // FIRST_CLASS_H
