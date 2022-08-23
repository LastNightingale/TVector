#include "TVector.h"
#include "Point.h"
#include <iostream>
#include <ctime>

int main()
{

	TVector<Point> pvector;
	pvector.PushBack(Point());
	pvector.PushBack(Point(3));
	pvector.EmplaceBack(5, 6);
	pvector.Print();
	pvector.PopBack();
	pvector.Print();
	pvector.EmplaceBack(1, 3);
	pvector.EmplaceBack();
	pvector.Print();
	pvector.EmplaceBack(4);
	pvector.Print();
	cout << pvector.Size() << endl;
	pvector[4] = Point(12);
	pvector.Print();
	for (Point iter : pvector)
	{
		cout << iter << endl;
	}
	cout << "=======================================" << endl;
	cout << pvector.Front() << endl;
	cout << pvector.Back() << endl;
	cout << "=======================================" << endl;
	
}