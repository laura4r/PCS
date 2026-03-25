#include <iostream>
#include "rational.hpp"

using namespace std ;

int main(){
	rational<int> nan(0,0) ;
	rational<int> inf(5,0) ;
	rational<int> a(15,6) ;
	rational<int> b(2,3) ;
	
	cout << nan << "\n" ;
	cout << inf << "\n" ;
	cout << a << "\n" ;
	cout << b << "\n" ;
	
}