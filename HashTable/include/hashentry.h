/**
 * @file	hashentry.h
 * @brief	Contains the class HashEntry and their implements methods 
 * @author	Samuel Lucas de Moura Ferino
 * @since	30/11/2017
*/

#ifndef _HASHENTRY_H 
#define _HASHENTRY_H

/**
 * @class HashEntry
**/
template <  class KeyType, class DataType >
class HashEntry{
	public:
		/**
		 * @brief	Constructor default
		 * @param 	k_ Key of item
		 * @param 	d_ Data of item	
		*/ 
		HashEntry( KeyType k_ , DataType d_ ) : m_key(k_), m_data(d_){ /* Empty */ };
		KeyType m_key;    // ! < Stores the key for an entry .
		DataType m_data; // ! < Stores the data for an entry .
};

#endif