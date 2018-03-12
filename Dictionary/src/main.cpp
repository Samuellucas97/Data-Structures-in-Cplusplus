/**
 * @file 	main.cpp
 * @
*/
#include <iostream>
#include <string>
#include "dal.h"
#include "dsal.h" 

class MyKeyComparator 
{

	public:

		bool operator()(const int &lhs , const int &rhs ) const
		{
			return lhs < rhs;
		}
};


int main(void)
{
	
	DAL<int, std::string, MyKeyComparator> a(11); //!< Instânciando dicionário
	DSAL<int, std::string,MyKeyComparator> b(11); //!< Instânciando dicionário


	std::string _info = "Jack"; //!< Conteúdo do novo elemento  
	int _id   = 10;  //!< Chave do novo elemento
	int _id_2 = 1;
	std::string _info_2 = "Marjory";

	std::cout <<  std::endl << " ***************  TESTING METHODS (DAL)  ***************    " << std::endl;
	std::cout << a << std::endl;
	///// REMOVE
	std::cout << "Remove = " << a.remove(_id, _info) << std::endl;
	std::cout << a << std::endl;
	///// INSERT
	std::cout << "Insert = " << a.insert(_id, _info) << std::endl;
	std::cout << a << std::endl;
	std::cout << "Insert = " << a.insert(_id, _info) << std::endl;
	std::cout << a << std::endl;
	std::cout << "Insert = " << a.insert(_id_2, _info_2) << std::endl;
	std::cout << a << std::endl;
	///// MAX
	std::cout << "Max = " << a.max() << std::endl;
	///// REMOVE
	std::cout << "Remove = " << a.remove(_id, _info) << std::endl;
	std::cout << a << std::endl;
	///// MIN
	std::cout << "Min = " << a.min() << std::endl;
	std::cout << a << std::endl;
	///// SUCESSOR
	int f = 8, g;
	std::cout << "Sucessor = " << a.sucessor(f, g) << std::endl;
	std::cout << a << std::endl;
	std::cout << "Sucessor = " << a.sucessor(f=1, g) << std::endl;
	std::cout << a << std::endl;
	///// PREDECESSOR
	std::cout << "Predecessor = " << a.predecessor(f, g) << std::endl;
	std::cout << a << std::endl;
	std::cout << "Predecessor = " << a.predecessor(f=10, g) << std::endl;
	std::cout << a << std::endl;
	///// SEARCH
	std::cout << "Search = " << a.search(_id, _info) << std::endl;
	std::cout << a << std::endl;
	std::cout << "Search = " << a.search(13, _info) << std::endl;
	std::cout << a << std::endl;


	std::cout <<  std::endl << " ***************  TESTING METHODS (DSAL)  ***************    " << std::endl;
	std::cout << b << std::endl;
	///// REMOVE
	std::cout << "Remove = " << b.remove(_id, _info) << std::endl;
	std::cout << b << std::endl;
	///// INSERT
	std::cout << "Insert = " << b.insert(_id, _info) << std::endl;
	std::cout << b << std::endl;
	///// REMOVE
	std::cout << "Remove = " << b.remove(_id, _info) << std::endl;
	std::cout << b << std::endl;
	///// INSERT
	std::cout << "Insert = " << b.insert(_id, _info) << std::endl;
	std::cout << b << std::endl;
	//std::cout << "Insert = " << b.insert(_id_2, _info_2) << std::endl;
	//std::cout << b << std::endl;
	///// MAX
	std::cout << "Max = " << b.max() << std::endl;
	std::cout << b << std::endl;
	///// REMOVE
	//std::cout << "Remove = " << a.remove(_id, _info) << std::endl;
	//std::cout << b << std::endl;
	///// MIN
	std::cout << "Min = " << b.min() << std::endl;
	std::cout << b << std::endl;
	///// SUCESSOR
	//std::cout << "Sucessor = " << b.sucessor(f=8, g) << std::endl;
	//std::cout << b << std::endl;
	//std::cout << "Sucessor = " << b.sucessor(f=1, g) << std::endl;
	///std::cout << b << std::endl;
	///// PREDECESSOR
	std::cout << "Predecessor = " << b.predecessor(f, g) << std::endl;
	std::cout << b << std::endl;
	//std::cout << "Predecessor = " << b.predecessor(f=10, g) << std::endl;
	///std::cout << b << std::endl;

	//DAL < int , std::string , MyKeyComparator  >   myList( 50 );
	//DSAL < int , std::string , MyKeyComparator   >   myList( 50 );
	//std::cout << std::endl << ">>> Inserindo  {2015003129 ,  \"Jack \"}" << std::endl;
	//myList.insert( 2015003129 , "Jack" );
	//std::cout  << ">>> Inserindo  {2014065190 ,  \"John \"}" << std::endl;
	//myList.insert( 2014065190 , "John" );

	return 0;
}	


































