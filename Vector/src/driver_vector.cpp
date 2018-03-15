#include <iostream>

#include "vector.h"

int main( void )
{
    sc::vector< int > a;

    // Inserts and prints out the array.
    for( auto i(0) ; i < 10 ; ++i )
    {
        a.push_back( i+1 );
        std::cout << a << std::endl;
    }

	for( auto o = a.begin(); o != a.end(); ++o)
	{
		std::cout << std::endl<< "OI";
		std::cout << a[2] <<" ";
		std::cout << a.at(4);
	}
	std::cout << std::endl;
	

	sc::vector<int> b;
	b.push_back(1);
	
	a.pop_back();
	std::cout << "Tamanho: " << a.sizer() << std::endl;
	std::cout << "Esta vazio: "<< a.capacidade() <<std::endl;
	std::cout << "Primeiro eh o " << std::endl;	
    
	std::cout << a.datas();
	std::cout << "VEM comigo! " << a.front() <<" e " << a.back() << std::endl;
	
	a.erase(a.begin());	
		
	if(a !=b)
		std::cout << "CHEGUEEEEEEEEEEEEEEEEI!" << std::endl;	

	return 0;
}
