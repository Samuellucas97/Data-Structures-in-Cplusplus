/**
 * @file	account.h
 * @brief	Contains the struct Account and their implements methods 
 * @author	Samuel Lucas de Moura Ferino
 * @since	30/11/2017
*/

#ifndef _ACCOUNT_H
#define _ACCOUNT_H

#include <functional>
using std::pair;

#include <tuple>
using std::tuple;

#include <string>
using std::string;

/**
 * @namespace version_1
**/
namespace version_1{
	/**
	 * @struct Account
	**/
	struct Account
	{
		string nome_cliente;//!< Cliente name
		int codigo_banco;   //!< Code of bank
		int n_agencia;  	//!< Agency number
		int n_conta; 		//!< Account number
		double saldo; 		//!< Account balance 

		/// ALIAS
		using AcctKey = int;

		/**
		 * @brief 	Constructor 
		 * @param	_nome_cliente 	Client name
		 * @param	_codigo_banco 	Code of bank
		 * @param 	_n_agencia 		Agency number
		 * @param	_n_conta 		Account number
		 * @param 	_saldo 			Account balance
		**/
		Account(string _nome_cliente, int _codigo_banco, int _n_agencia, long int _n_conta, double _saldo): nome_cliente(_nome_cliente), 
		codigo_banco(_codigo_banco), n_agencia(_n_agencia), n_conta(_n_conta), saldo(_saldo){} 	

		/**
		 * @brief	Return an key
	     * @return 	Key  
		*/
		AcctKey get_key(void){ return n_conta; }

		/**
		 * @brief 	Overload of operator ==
		 * @return 	If equal return true otherwise return false	
		*/ 
		bool operator==(Account a)
		{
			if((a.nome_cliente == nome_cliente) && 
			   (a.codigo_banco == codigo_banco) &&
			   (a.n_agencia    == n_agencia)    &&
			   (a.n_conta      == n_conta)      &&
			   (a.saldo        == saldo)	)
			{
				return true;
			}
			else
				return false;
		}
	};

	/**
	 * @struct 	KeyHash 
	 * @brief 	VERSION 1
	**/
	struct KeyHash 
	{

		std::size_t operator()( const Account::AcctKey & k_ ) const
		{
			return std::hash< int>()( k_ );
		}
	};


	/**
	 * @struct 	KeyEqual 
	 * @brief 	VERSION 1
	**/
	struct KeyEqual 
	{
		bool operator ()( const version_1::Account::AcctKey& lhs_ , const version_1::Account::AcctKey& rhs_ ) const
		{
			return lhs_ == rhs_ ;
		}
	};		


}

/**
 * @namespace version_2
**/
namespace version_2{
	/**
	 * @struct Account
	**/
	struct Account
	{
		/// ALIAS
		using AcctKey = std::pair < std::string , int >;

		string nome_cliente;//!< Cliente name
		int codigo_banco;   //!< Code of bank
		int n_agencia;  	//!< Agency number
		int n_conta; 		//!< Account number
		double saldo; 		//!< Account balance
		
		/**
		 * @brief 	Constructor 
		 * @param	_nome_cliente 	Client name
		 * @param	_codigo_banco 	Code of bank
		 * @param 	_n_agencia 		Agency number
		 * @param	_n_conta 		Account number
		 * @param 	_saldo 			Account balance
		**/
		Account(string _nome_cliente, int _codigo_banco, int _n_agencia, long int _n_conta, double _saldo): nome_cliente(_nome_cliente), 
		codigo_banco(_codigo_banco), n_agencia(_n_agencia), n_conta(_n_conta), saldo(_saldo){} 	

		/**
		 * @brief	Return an key
	     * @return 	Key  
		*/
		AcctKey get_key(void){ return std::make_pair(nome_cliente,n_conta); }

		/**
		 * @brief 	Overload of operator ==
		 * @return 	If equal return true otherwise return false	
		*/ 
		bool operator==(Account a)
		{
			if((a.nome_cliente == nome_cliente) && 
			   (a.codigo_banco == codigo_banco) &&
			   (a.n_agencia    == n_agencia)    &&
			   (a.n_conta      == n_conta)      &&
			   (a.saldo        == saldo)
			)
			{
				return true;
			}
			else
				return false;
		}

	};

	/**
	 * @struct 	KeyHash 
	 * @brief	VERSION 2
	**/
	struct KeyHash 
	{
		std::size_t operator ()( const version_2::Account::AcctKey & k_ ) const
		{
			return (std::hash< std::string >()( k_.first ) ) xor (std::hash < int >()( k_.second ));
		}
	};

	/**
	 * @struct 	KeyEqual 
	 * @brief	VERSION 2
	**/
	struct KeyEqual 
	{
		bool operator ()( const version_2::Account::AcctKey & lhs_ , const version_2::Account::AcctKey & rhs_ ) const
		{
			return lhs_.first == rhs_.first and lhs_.second == rhs_.second;
		}
	};


}


/**
 * @namespace version_3
**/
namespace version_3{
	/**
	 * @struct Account
	**/
	struct Account
	{
		/// ALIAS
		using AcctKey = std::tuple< std::string , int , int , int >;

		string nome_cliente;//!< Cliente name
		int codigo_banco;   //!< Code of bank
		int n_agencia;  	//!< Agency number
		int n_conta; 		//!< Account number
		double saldo; 		//!< Account balance

		/**
		 * @brief 	Constructor 
		 * @param	_nome_cliente 	Client name
		 * @param	_codigo_banco 	Code of bank
		 * @param 	_n_agencia 		Agency number
		 * @param	_n_conta 		Account number
		 * @param 	_saldo 			Account balance
		**/
		Account(string _nome_cliente, int _codigo_banco, int _n_agencia, long int _n_conta, double _saldo): nome_cliente(_nome_cliente), 
		codigo_banco(_codigo_banco), n_agencia(_n_agencia), n_conta(_n_conta), saldo(_saldo){} 	

		AcctKey get_key(void){ return std::make_tuple(nome_cliente,codigo_banco,n_agencia,n_conta); }

		/**
		 * @brief 	Overload of operator ==
		 * @return 	If equal return true otherwise return false	
		*/ 
		bool operator==(Account a)
		{
			if((a.nome_cliente == nome_cliente) && 
			   (a.codigo_banco == codigo_banco) &&
			   (a.n_agencia    == n_agencia)    &&
			   (a.n_conta      == n_conta)      &&
			   (a.saldo        == saldo)	
			   )
			{
				return true;
			}
			else
				return false;
		}

	};


	/**
	 * @struct 	KeyEqual 
	 * @brief 	VERSION 3
	**/
//	struct KeyEqual 
//	{
//		bool operator ()( const version_1::Account::AcctKey& lhs_ , const Aversion_1::ccount::AcctKey& rhs_ ) const
//		{
//			return (lhs_.first == rhs_.first ) && (lhs_.second == rhs_.second) ;
//		}
//	};		
//}

	/**
	 * @struct 	KeyHash 
	 * @brief	VERSION 2
	**/
//	struct KeyHash 
//	{
//		std::size_t operator ()( const version_2::Account::AcctKey & k_ ) const
//		{
//			return (std::hash< std::string >()( std::get<0>(k_) ) ) xor (std::hash < int >()( std::get<1>(k_) )) xor (std::hash< int >()( std::get<2>(k_)) ) xor (std::hash< int >()( std::get<3>(k_)) );
//		}
//	};


}

#endif