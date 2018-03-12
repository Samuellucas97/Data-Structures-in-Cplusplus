/**
 * @file	main.cpp
 * @brief	Contains the function main 
 * @author	Samuel Lucas de Moura Ferino
 * @since	30/11/2017
*/

/// OWN LIBRARIES
#include "hashentry.h"
#include "hashtbl.h"
#include "account.h"

#include <tuple>	  /// std::tuple	
#include <utility>    /// std::pair


int main()
{
/*
	std::vector<Account> accounts = {
        Account( 1, 51, 98765, 2000.50, "John Lennon"),
        Account( 2, 10, 56789, 1500.25, "Ringo Starr"),
        Account( 3, 40, 54321, 10000.0, "Paul McCartney"),
        Account( 4, 91, 12345, 1111.75, "George Harrison"),
        Account( 5, 67, 13579, 2100.00, "Pete Best"),
        Account( 6, 76, 24680, 2010.00, "Stuart Sutcliffe"),
	}
*/
	// ----------------  *****************************  ----------------- // 
	// ----------------  TESTING METHODS OF TABLE HASH  ----------------  //   	 
	// ----------------  *****************************  ----------------- // 

	int key = 10; //!< 	Key of element
	int date = 7; //!<	Date of element
	HashTbl<int, int> a;  //!< Creating table hash empty

	std::cout << std::endl << " ******* TESTING OPERATIONS OF TABLE ******* " << std::endl << std::endl;
	std::cout << "Empty = " << a.empty() << std::endl;
	a.print();
	std::cout << std::endl;

	std::cout << "Insert   = "   << a.insert(10,7)         << std::endl;
	std::cout << "Insert   = "   << a.insert(10,7)         << std::endl;
	std::cout << "Insert   = "   << a.insert(1,9)          << std::endl;
	std::cout << "Count    = "   << a.count()              << std::endl;
	std::cout << "Retrieve = "   << a.retrieve(key, date)  << std::endl;
	a.print();
	std::cout << std::endl;

	std::cout << "Remove   = "   << a.remove(1)            << std::endl;
	a.print();
	std::cout << std::endl;
	
	a.clear();
	a.print();
	std::cout << std::endl;

	// ----------------  *****************************  ----------------- // 
	// -----------------------------------------------------------------  //   	 
	// ----------------  *****************************  ----------------- // 
	return 0;
}