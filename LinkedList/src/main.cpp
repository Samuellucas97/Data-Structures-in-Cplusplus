/**
 * @file 	main.cpp
 * @brief	Contém a função principal que testa as classes: list, const_iterator e iterator.
 * @author 	Samuel Lucas de Moura Ferino (samuel1797@gmail.com)
 * @since 	24/11/17
*/

#include <iostream>
#include "list.h"

int main()
{
	lc::list<int> a;	
	
	/// TESTE DAS OPERAÇÕES NA LISTA
	a.push_front(10);
	a.push_front(10);
	a.push_front(7);
	a.push_back(9);
	std::cout << " front = " << a.front();
	std::cout << std::endl << "Tamanho da lista a é " << a.size() << std::endl;
	std::cout << "A lista a está vazia? " << a.empty() << std::endl;
	a.pop_front();
	std::cout << std::endl << "Tamanho da lista a é " << a.size() << std::endl;
	a.pop_back();
	std::cout << std::endl << "Tamanho da lista a é " << a.size() << std::endl;
	/// --------------------------------------------------------------------
	lc::list<int> b(3);
	b.push_back(9);
	std::cout << " back = " << a.back();

	std::cout << std::endl << "Tamanho da lista b é " << b.size() << std::endl;
	b.pop_back();
	std::cout << std::endl << "Tamanho da lista b é " << b.size() << std::endl;
	/// --------------------------------------------------------------------
		

	std::cout << "FINISH!" << std::endl;
	return 0;

}