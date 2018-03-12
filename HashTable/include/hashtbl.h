/**
 * @file	hashtbl.h
 * @brief	Contains the class HashTbl and their implements methods  
* @author	Samuel Lucas de Moura Ferino
 * @since	30/11/2017
*/

#ifndef _HASHTBL_H
#define _HASHTBL_H

#include <memory>
using std::unique_ptr;
using std::make_unique;

#include <forward_list>
using std::forward_list;

#include <iostream> 	/// std::cout
#include <functional>   /// std::equal_to and std::hash

/// OWN LIBRARIES
#include "hashentry.h"

/**
 * @class HashTbl
**/
template <  typename KeyType, 
            typename DataType, 
            typename KeyHash = std::hash<KeyType>,
            typename KeyEqual = std::equal_to<KeyType> >
class HashTbl{
	public:

		using Entry = HashEntry < KeyType , DataType >; // ! < Alias

		/**
		 * @brief 	Constructor default
		 * @param 	tbl_size_ Size of table hash
		*/ 
		HashTbl ( unsigned int tbl_size_ = DEFAULT_SIZE )
		{
			tbl_size_ = next_Prime(tbl_size_);
			m_size = tbl_size_;

			m_data_table = make_unique< forward_list<Entry> [] >(tbl_size_); /// INSTANCING THE VECTOR OF LISTS
		}

		/**
		 * @brief 	Destructor default
		*/
		virtual ~HashTbl () 
		{ 
			clear(); 
		}

		/**
		 * @brief 	Insert in the table, if there is already an element in the position 
		 *          previosly return false, else true
		 * @param 	k_ Key of new element
		 * @param 	d_ Element content
		*/
		bool insert ( const KeyType & k_ , const DataType & d_)
		{

			if (m_count == m_size)
			{
				rehash();		
			}

			KeyHash hashFunc; 			/// INSTANCING THE FUNCTOR 
			KeyEqual equalFunc;			/// INSTANCING THE FUNCTOR
			Entry new_entry(k_, d_);    /// BUILT THE NEW ELEMENT

			unsigned int end = hashFunc(k_)%m_size; //!< ADDRESS IN THE TABLE 
			
			//std::forward_list<Entry> list_colision = &m_data_table[end]; //!< RESPECTIVE LIST OF COLISION 

			//!< @brief	FIRST ADD 
			if(m_count == 0) 
			{
			//	list_colision.push_front(new_entry);
				m_data_table[end].push_front(new_entry);			
				++m_count;
				return true;
			}

			//!< @brief	BROWSING IN LIST OF COLISION RESPECTIVE THE KEY AND COMPARING 
			for(auto i = m_data_table[end].begin(); i !=  m_data_table[end].end(); ++i)
			{
				if(equalFunc(k_, i->m_key) )
				{
					m_data_table[end].push_front(new_entry);
				
					++m_count;
					return false;				
				}					
			}

			m_data_table[end].push_front(new_entry);
			++m_count;
			return false;				
			
		}

		/**
		 * @brief 	If find the o element, remove da table and return true otherwise return false 
		 * @param 	k_ Key of new element
		*/
		bool remove ( const KeyType & k_ )
		{				
			KeyHash hashFunc;	//!< INSTANTIATING THE FUNCTOR 
			KeyEqual equalFunc;	//!< INSTANCING THE FUNCTOR

			unsigned int end = hashFunc(k_)%m_size; //!< @brief	ADDRESS IN THE TABLE 

			/** @brief 	SEARCHING KEY IN THE LIST*/
			for(auto i = m_data_table[end].begin(); i !=  m_data_table[end].end(); ++i)
			{
				if(equalFunc(k_, i->m_key) )
				{
					m_data_table[end].pop_front();
					return true;				
				}					
			}

			return false;
		}

		/**
		 * @brief 	Search key in table, if find the o element return true other return false 
		 * @param 	k_ Key of new element
		 * @param 	d_ Information of new element
		*/
		bool retrieve ( const KeyType & k_ , DataType & d_ ) const
		{

			KeyEqual equalFunc;			/// INSTANTIATING THE FUNCTOR 
			KeyHash hashFunc;			/// INSTANTIATING THE FUNCTOR 

			unsigned int end = hashFunc(k_)%m_size; //!< ADDRESS IN THE TABLE 

			/** @brief 	SEARCHING KEY IN THE LIST*/
			for(auto i = m_data_table[end].begin(); i !=  m_data_table[end].end(); ++i)
			{
				if(equalFunc(k_, i->m_key) )
				{
					d_ = i->m_data;
					return true;				
				}					
			}

			return false;

		}
		/**
		 * @brief 	Method that clear all, including the lists of colisions
		*/ 
		void clear ( void )
		{
			for(unsigned int i = 0; i < m_size; ++i)
			{
				//std::forward_list<Entry> list_colision = &(m_data_table[i]); //!< List of colision in "i"
				//list_colision.clear();
				m_data_table[i].clear(); 
			}
			m_count = 0;	
		}

		/**
		 * @brief 	Method that return true of the table is empty otherwise return false
		*/
		bool empty ( void ) const 
		{
			if(m_count == 0)
				return true;
			else
				return false;
		}
		
		/**
		 * @brief 	Method that return the number de elements in the table
		*/
		unsigned long int count ( void ) const 
		{
			return m_count;
		}
		
		/**
		 * @brief 	Method that prints all elements of table on the screen
		*/
		void print ( void ) const 
		{
			std::cout << std::endl << 	" --- TABLE  HASH ---" << std::endl;

			if(m_count > 0)
			{
				for(unsigned int i = 0; i < m_size; ++i)
				{
					std::forward_list<Entry> list_colision = m_data_table[i];
					
					if(not list_colision.empty())
					{	
						for (auto j = list_colision.begin(); j != list_colision.end(); ++j)
						{
							std::cout << "[ KEY = "  << j->m_key 
							          << "  DATA = " << j->m_data << " ]" << std::endl;
						}
					}	
				}
			}
			else
				std::cout << "  [ TABLE IS EMPTY! ]" << std::endl;

		}

		friend std::ostream& operator<<(std::ostream& o, HashTbl<KeyType, DataType, KeyHash, KeyEqual> _table)
		{

			if(_table.m_count > 0)
			{
				for(unsigned int i = 0; i < _table.m_size; ++i)
				{
				
					std::forward_list<Entry> list_colision = _table.m_data_table[i];
					
					if(not list_colision.empty())
					{
						for (auto j = _table.list_colision.begin(); i != _table.list_colision.end(); ++i)
						{
							o << "KEY = " << j ->m_key 
							          << "DATA" << j->m_data  << std::endl;
						}
					}	
				}
			}
			else{
				o << "Tabela vazia! ";
			}

			return o;

		} 


	private:

		/**
		 * @brief 	Method that resize the table
		*/
		void rehash ()
		{
			if(m_count/m_size > 1)
			{
				KeyHash hashFunc;	/// INSTANTIATING THE FUNCTOR 
				std::unique_ptr < std::forward_list < Entry > [] > m_NEW_data_table; //!< New table hash
	
				unsigned int m_new_size = next_Prime(2*m_size); //!< Size of new table 

				m_NEW_data_table = make_unique< forward_list<Entry> [] >(m_new_size); /// INSTANCING THE NEW VECTOR OF LISTS

				for(unsigned int i = 0; i < m_size; ++i)
				{	
					/// WHILE THE OLD LIST OF COLISION IN POINT "I" IS NOT EMPTY, RECALCULATING THE ADDRESS OF ELEMENTS IN NEW TABLE
					while(not m_data_table[i].empty())	
					{	
						auto k  = m_data_table[i].front();
						m_data_table[i].pop_front();

						unsigned int end = hashFunc(k.m_key)%m_new_size; //!< CALCULATING NEW ADDRESS IN THE NEW TABLE 
						
						m_NEW_data_table[end].push_front(k); //!< ADD IN NEW TABLE
					}
				}

				m_data_table = std::move(m_NEW_data_table);
				m_size = m_new_size;	
			}	
		}

		unsigned int m_size ; // ! < Hash table size .
		unsigned int m_count=0 ; // ! < Number of elements currently stored in the table .
		
		/**
		 * @brief 	Method that find the next prime
		 * @param 	_size_table Possible size of table if it is prime
		*/		
		unsigned int next_Prime(unsigned int _size_table)
		{
			int dividers = 0;   // !< Number of dividers 

			for(unsigned int i = _size_table; ;++i)
			{
				for(unsigned int j = 2; j < i; ++j )
				{
					if(i%j == 0)
					{	
						++dividers;	
					}
				}

				/// IS AN NUMBER PRIME
				if( dividers == 0)
				{	
					return i;	
				}	
					
				/// RESET THE COUNT OF DIVIDERS TO 0
				dividers = 0;
			}

			/// LINE TO COMPILER(WARNING)
			return _size_table;	
		}

		// ! < The table : array of pointers to collision list .
		//std :: forward_list < Entry > * m_data_table ;
		std::unique_ptr < std::forward_list < Entry > [] > m_data_table ;
		// ! Hash table ’s default size : 11 table entries .
		static const short DEFAULT_SIZE = 11;
};

#endif 