#include <iostream>
#include "dyndata.h"
using namespace std;

int main()
{

	dyndata<char> a;
	a.setdata('a');
	cout<<a.getdate()<<endl;

	return 0;
}
