/**
 * @file 	dal.h
 * @brief	Contém a classe DAL e a implementação de seus métodos
 * @author 	Samuel Lucas de Moura Ferino
 * @since 	07/12/2017
*/

#ifndef _DAL_H_
#define _DAL_H_

#include <memory>   /// std::unique_ptr e std::make_unique
#include <iostream> /// std::ostream 
#include <string>   /// std::string

/**
 * @class 	DAL
**/
template < typename Key, typename Data, typename KeyComparator >
class DAL{
	protected :
	
	//	using Key = int; /// Alias para Chave .
		
		/**
		 * @struct 	NodeAL
		 * @brief	Estrutura do nó , representando o par chave - informação .
		**/
		struct NodeAL {
			Key id;	 	//!< A chave é um inteiro simples .
			Data info;	//!< A informação é uma cadeia de caracteres .

//			NodeAL(Key _id, Data _info):id(_id), info(_info){}
			bool operator!=(const NodeAL & _a) 
			{
				return	( (_a.id == id) and (_a.info == info) );
				
			}
		};


		static const int SIZE = 50; //!< Tamanho default da lista .
		int mi_Length; //!< Comprimento atual da lista .
		int mi_Capacity;  //!< Capacidade máxima de armazenamento .
		std::unique_ptr<NodeAL []> mpt_Data;  //!< Área de armazenamento : vetor alocado dinamicamente .
  		
  		/**
  		 * @brief	Método de busca auxiliar .  (BUSCA LINEAR)
		 * @param 	_x 	Chave do elemento a ser buscado
		 * @return 	Se encontrado retorna o valor da posição dele
		 * 			caso contrário, retorna -1
		*/
		int _search ( const Key & _x ) const
		{
			KeyComparator compare; //!< Instânciando o functor KeyComparator

			for(int i = 0; i < mi_Length; ++i)
			{
				if(  (not compare(mpt_Data[i].id, _x ))  and (not compare( _x, mpt_Data[i].id )) )
				{
					return i;
				}	
			}

			return -1;	
		}

	public:

		/**
		 * @brief 	Construtor padrão
		 * @param 	_MaxSz Tamanho inicial do dicionário	
		*/ 
		DAL ( int _MaxSz = SIZE ): mi_Length(0), mi_Capacity(_MaxSz) 
		{
			/// ALOCAÇÃO DINÂMICA
			mpt_Data = std::make_unique< NodeAL [] >(_MaxSz); 
		}

		/**
		 * @brief 	Destrutor padrão
		*/ 
		virtual ~DAL() { /* Empty*/ };
		
		/**
		 * @brief 	Remove da lista, ou seja, pega o último elemento e copia nele
	 	 * @param 	_x 	Chave do elemento
	 	 * @param 	_s 	Contéudo do elemento 
		 * @return 	True se "apagou" e false se não "apagou"	
		*/ 
		bool remove( const Key & _x , Data & _s )
		{
			/// TEM AO MENOS 1 ELEMENTO
			if(mi_Length > 0)
			{			
				bool find = search(_x, _s); //!< Existência do elemento no dicionario

				/// CASO TENHA ENCONTRADO
				if(find == true)
				{
					mpt_Data[find] = mpt_Data[mi_Capacity-1];
					--mi_Length;
					return true;
				}	
				/// CASO NÃO TENHA ENCONTRADO
				else	
					return false;	
			}
			/// NÃO TEM ELEMENTOS PARA QUE POSSA APAGAR
			else 
				return false;	
		} 

		/**
		 * @brief	Busca publica .
		 * @param 	_x 	Chave a ser buscada no dicionario
		 * @param 	_s 	Informação a ser buscada no dicionario
		 * @return 	True se encontrou e false se não encontrou	
		*/   
		bool search( const Key & _x , Data & _s ) const 
		{
			/// TEM AO MENOS 1 ESPAÇO PARA INSERIR ELEMENTOS
			if(mi_Length > 0)
			{
				int position = _search(_x); //!< Posição do elemento

				/// CHAVE ENCONTRADA 
				if( position >= 0 )
				{
					if( mpt_Data[position].info == _s )
						return true;
					else 
						return false;
				}
				/// CHAVE NÃO ENCONTRADA 
				else
					return false;		
			}
			else
				return false;		
		} 
		
		/**
		 * @brief	Insere na lista 
		 * @param 	_newKey		Chave do novo elemento
		 * @param 	_newInfo	Informação do novo elemento
 		 * @return 	True se inseriu caso contrário, false	
		*/ 
		bool insert( const Key & _newKey , const Data & _newInfo )
		{
			/// MENOR QUE O TAMANHO DO DICIONÁRIO 	
			if(mi_Length < mi_Capacity)
			{
				// PRIMEIRO INSERT, POR ISSO PODE SER EM QUALQUER POSIÇÃO
				if( mi_Length == 0)
				{
					mpt_Data[0].id =  _newKey;
					mpt_Data[0].info = _newInfo;
					++mi_Length;
					return true;
				}	
				else
				{
					int position = _search(_newKey); //!< Posição do elemento no dicionário

					// ELEMENTO ENCONTRADO, ENTÃO SUBSCREVO O CONTEÚDO DELE
					if(position != -1)
					{	

						mpt_Data[position].info = _newInfo;
						return true;
					}	
					// ELEMENTO NÃO ENCONTRADO, ENTÃO PROCURO A PRÓXIMA POSIÇÃO LIVRE 
					else
					{	
						int  _next_position_free;  //!< Próxima posição livre no dicionário	
						bool existence_sucessor;	//!< Existência de sucessor

						existence_sucessor = sucessor(mpt_Data[0].id, _next_position_free);
						
						/// EXISTE UM SUCESSOR, ENTÃO SALVA A CHAVE E O CONTEÚDO NESSA POSIÇÃO
						if(existence_sucessor)
						{				
							mpt_Data[_next_position_free].id = _newKey;
							mpt_Data[_next_position_free].info = _newInfo;
							++mi_Length;
							return true;
						}
						/// NÃO EXISTE UM SUCESSOR
						else
							return false;
					}	
				}	
			}
			/// MAIOR QUE O TAMANHO DO DICIONÁRIO 	
			else
				return false;	
		} 
		
		/**
		 * @brief	Recupera a menor chave do dicionário .
		*/ 
		Key min(void) const
		{	
			/// TEM AO MENOS 1 ELEMENTO 
			if( mi_Length > 0)
			{	
				/// TEM APENAS 1 ELEMENTO 
				if(mi_Length == 1){
					return 0;
				}

				Key less_element = Key();  //!< Guarda o menor elemento (construtor default int = 0)

				for(int i = 0; i < mi_Length; ++i)
				{
					/// COMPARA-SE AS CHAVES 	
					if( mpt_Data[i].id < less_element )
					{	
						less_element = mpt_Data[i].id;
					}
				}
				
				return less_element; 	
			}
			return -1;	

		} 
		
		/**
		 * @brief Recupera a maior chave do dicionário .
		*/ 
		Key max(void)const
		{
			/// TEM AO MENOS 1 ELEMENTO
			if(mi_Length > 0)
			{	
				/// TEM APENAS 1 ELEMENTO 
				if(mi_Length == 1)
				{
					return 0;
				}

				Key major_element = Key(); //!< Guarda o maior elemento

				for(int i = 0; i < mi_Length; ++i)
				{
					if( mpt_Data[i].id > major_element ) 
					{		
						major_element =  mpt_Data[i].id;
					}	
				}

				return major_element;
			}
			else	
				return -1;	
		} 

		/**
		 * @brief	Recupera em _y a chave sucessora a _x , se existir ( true ).
		 * @param 	_x 	Chave 1
		 * @param 	_y  Chave 2
		*/  
		bool sucessor ( const Key & _x , Key & _y ) const
		{
			/// TEM AO MENOS 1 ELEMENTO
			if(mi_Length > 0)
			{	
				int position = _search(_x); //!< Posição do elemento

				/// CHAVE ENCONTRADA E NÃO É O ÚLTIMO 
				if((position >= 0) and (position < (mi_Capacity-1)) )
				{
					_y = position+1;
					return true;
				}
				/// CHAVE NÃO ENCONTRADA OU É O ÚLTIMO
				else
					return false;
			}
			/// NÃO TEM ELEMENTOS
			else
				return false;
		}

		/**
		 * @brief 	Recupera em _y a chave antecessora a _x , se existir ( true ).
		 * @param 	_x 	Chave 1
		 * @param 	_y  Chave 2
		*/  
		 bool predecessor ( const Key & _x , Key & _y ) const
		{
			/// TEM AO MENOS 1 ELEMENTO
			if(mi_Length > 0)
			{	
				int position = _search(_x); //!< Posição do elemento

				/// CHAVE ENCONTRADA E NÃO É O PRIMEIRO 
				if(position > 0) 
				{
					_y = position-1;
					return true;
				}
				/// CHAVE NÃO ENCONTRADA OU É O PRIMEIRO 
				else
					return false;
			}
			/// NÃO TEM ELEMENTOS
			else
				return false;	
		}


		/**
		 * @brief 	Sends back to the output stream an ascii representation for the list .
	 	 * @param 	_os Objeto ostream
	 	 * @param 	_oList Lista a ser immpressa			
		*/ 
		inline friend std::ostream& operator<< ( std::ostream & _os , const DAL & _oList ) 
		{

			_os << " [ " ;

			/// PERCORRENDO O DICIONÁRIO E IMPRIMINDO
			for ( int i(0) ; i < _oList.mi_Length ; ++ i )
				_os << " { id : " << _oList.mpt_Data[i].id << " , info : "
					<< _oList.mpt_Data[i].info << " } " ;

			_os << " ] " ;

			return _os ;
		}
};

#endif