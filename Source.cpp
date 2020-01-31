#include "Car.h"
#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "");
	car::AutoPark my{};	
	my.Menu();
	system("pause");
	return 0;
}