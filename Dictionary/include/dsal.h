/**
 * @file 	dsal.h
 * @brief	Contém a classe DSAL e a implementação de seus métodos
 * @author 	Samuel Lucas de Moura Ferino
 * @since 	07/12/2017
*/

#ifndef _DSAL_H_
#define _DSAL_H_	

#include "dal.h"

/**
 * @class DSAL
*/ 
template < typename Key, typename Data, typename KeyComparator  >
class DSAL: public DAL< Key, Data, KeyComparator >
{
	private:

		/**
		 * @brief	Método  de busca  auxiliar. (BUSCA BINÁRIA)	
		 * @param 	_x 	Chave do elemento a ser buscado
		 * @return 	Se encontrado retorna o valor da posição dele
		 * 			caso contrário, retorna -1		
		 */ 
		int _search(const Key & _x ) const
		{
			KeyComparator compare; //!< Instânciando o functor 
			int i1 = 0; //!< Índice do início do intervalo
			int i2 = DAL<Key, Data, KeyComparator>::mi_Length - 1;	//!< Índice do fim do intervalo	
			int meio; //!< Índice do meio do intervalo 

			/// ENQUANTO ESTIVER NO RANGE DO mpt_Data PROCURA-SE PELO _x
			while(i1 <= i2)
			{
				meio =(i1+i2)/2; //!< Índice do meio do intervalo i1 a i2  

				/// O INTERVALO QUE O _x ESTÁ FICA A ESQUERDA, POR ISSO, DESLOCO O FIM PARA O MEIO 
				if(DAL<Key, Data, KeyComparator>::mpt_Data[meio].id > _x)
				{
					i1 = meio;
				}
				/// O INTERVALO QUE O _x ESTÁ FICA A DIREITA, POR ISSO, DESLOCO O FIM PARA O MEIO 
				else if( compare(DAL<Key, Data, KeyComparator>::mpt_Data[meio].id, _x) ) //!< Lê-se: mpt_Data[meio].id é menor que _x ?
				{
					i2 = meio;
				}
				else
				{
					/// ENCONTROU O ELEMENTO, ENTÃO RETORNA O SEU ÍNDICE
					if( (not compare(DAL<Key, Data, KeyComparator>::mpt_Data[meio].id, _x) ) 
					        	and(not compare(_x, DAL<Key, Data, KeyComparator>::mpt_Data[meio].id)) )
					{
						return meio;
					}	
				}	
			}
			/// NÃO ENCONTROU
			return -1; 	
		}

	public:
	
		/**
		 * @brief 	Construtor padrão
		 * @param 	_MaxSz Tamanho inicial do dicionário	
		*/ 
		DSAL(int _MaxSz ) : DAL<Key, Data, KeyComparator>( _MaxSz ) { /* Empty */ };

		/**
		 * @brief 	Destrutor padrão
		*/ 
		virtual ~DSAL() { /* Empty */ };
		
		
		///   Métodos  para  sobrescrever.
		/**
		 * @brief 	Remove da lista, ou seja, desloca todos para a esquerda até 
		 *          esse elemento, sobreescrevendo-o
	 	 * @param 	_x 	Chave do elemento
	 	 * @param 	_s 	Contéudo do elemento 
		 * @return 	True se encontrou e "apagou" e false se não encontrou	
		*/ 
		bool remove( const Key & _x, Data & _s)
		{
			/// TEM AO MENOS 1 ELEMENTO
			if(DAL<Key, Data, KeyComparator>::mi_Length > 0)
			{			
				int position = _search(_x); //!< Posição do elemento

				/// CASO TENHA ENCONTRADO
				if(position != -1)
				{
					/// A CHAVE É IGUAL E O CONTEÚDO TAMBÉM
					if(DAL<Key, Data, KeyComparator>::mpt_Data[position].info == _s)
					{								
						///    DESLOCA TODOS OS ELEMENTOS, DA DIREITA(FIM) PARA A ESQUERDA(INÍCIO), 
						/// DEIXANDO DE CONTAR O ÚLTIMO, E DIMINUI O TAMANHO LÓGICO 
						for(int i = position; i < DAL<Key, Data, KeyComparator>::mi_Length-1; ++i)
						{
							DAL<Key, Data, KeyComparator>::mpt_Data[i].info = DAL<Key, Data, KeyComparator>::mpt_Data[i+1].info;
							DAL<Key, Data, KeyComparator>::mpt_Data[i].id   = DAL<Key, Data, KeyComparator>::mpt_Data[i+1].id;
						}	

						--DAL<Key, Data, KeyComparator>::mi_Length;
						return true;
					}
					/// A CHAVE IGUAL, PORÉM O CONTÉUDO É DIFERENTE
					else
						return false;	
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
		 * @brief	Insere na lista 
		 * @param 	_novaId		Chave do novo elemento
		 * @param 	_novaInfo	Informação do novo elemento 	
		 * @return 	True se inseriu caso contrário, false	
		*/ 
		bool insert( const Key & _novaId, const Data & _novaInfo )
		{
			/// TEM AO MENOS 1 ESPAÇO PARA INSERIR UM ELEMENTO
			if(DAL<Key, Data, KeyComparator>::mi_Length < DAL<Key, Data, KeyComparator>::mi_Capacity)
			{

				int position = _search(_novaId); //!< Posição do elemento
				
				/// HÁ CHAVE IGUAL A _novaID, ENTÃO SOBESCREVO NESSA POSIÇÃO					
				if( position != -1 )
				{
					DAL<Key, Data, KeyComparator>::mpt_Data[position].info = _novaInfo;
					return true;
				}	
				/// NÃO HÁ CHAVE IGUAL A _novaID					
				else
				{	
					/// SÓ TEM UM ESPAÇO SOBRANDO, ENTÃO INSIRO NO FINAL REAL
					if( (DAL<Key, Data, KeyComparator>::mi_Capacity - DAL<Key, Data, KeyComparator>::mi_Length) == 1)
					{
						DAL<Key, Data, KeyComparator>::mpt_Data[DAL<Key, Data, KeyComparator>::mi_Capacity-1].info = _novaInfo;
						DAL<Key, Data, KeyComparator>::mpt_Data[DAL<Key, Data, KeyComparator>::mi_Capacity-1].id = _novaId;
					
						++DAL<Key, Data, KeyComparator>::mi_Length;  /// INCREMENTA A QUANTIDADE LÓGICA
						return true;
					}
					/// A MAIS DE UM ESPAÇO SOBRANDO, INSIRO NO FINAL LÓGICO 
					else
					{
						//int amount_ =  DAL<Key, Data, KeyComparator>::mi_Capacity - DAL<Key, Data, KeyComparator>::mi_Length; //!< Quantidade de espaços sobrando

						DAL<Key, Data, KeyComparator>::mpt_Data[DAL<Key, Data, KeyComparator>::mi_Length].info = _novaInfo;
						DAL<Key, Data, KeyComparator>::mpt_Data[DAL<Key, Data, KeyComparator>::mi_Length].id = _novaId;
					
						std::cout << "AAAAAAAAAAAAAAA"<< std::endl;	
						DAL<Key, Data, KeyComparator>::mi_Length++;  /// INCREMENTA A QUANTIDADE LÓGICA
						return true;

					}		
				}
			}	
			/// NÃO TEM ESPAÇO PARA INSERIR ELEMENTOS
			return false;
		}

		/**
		 * @brief	Recupera a menor chave do  dicionário.
		 * @return	Retorna a primeira posição pelo fato de está ordenado
		*/ 
		Key min(void) const
		{	
			if(DAL<Key, Data, KeyComparator>::mi_Length > 0)
				return DAL<Key, Data, KeyComparator>::mpt_Data[0].id;
			else
				return Key();
		} 

		/**
		 * @brief	Recupera a maior chave do  dicionário.
		 * @return	Retorna a última posição pelo fato de está ordenado
		*/ 
		Key max(void )const
		{
			if(DAL<Key, Data, KeyComparator>::mi_Length > 0)
				return DAL<Key, Data, KeyComparator>::mpt_Data[DAL<Key, Data, KeyComparator>::mi_Length-1].id;
			else
				return Key();
		} 
		/**
		 * @brief	Recupera em _y a chave sucessora a _x .
		 * @param 	_x 	Chave 1
		 * @param 	_y  Chave 2
		 * @return	True se existir sucessor caso contrário, false
		*/ 
		bool sucessor( const Key & _x, Key & _y ) const
		{
			int position = _search(_x); //!< Posição do elemento

			/// A CHAVE _X FOI ENCONTRADA E NÃO É A ÚLTIMA CHAVE
			if( (position != -1) and (position < DAL<Key, Data, KeyComparator>::mi_Length-1) )
			{	
				_y = DAL<Key, Data, KeyComparator>::mpt_Data[position].id;
				return true;
			}
			/// A CHAVE _X ŃÃO FOI ENCONTRADA OU(OR) É A ÚLTIMA CHAVE
			else
				return false;	 
		} 
	
		/**
		 * @brief 	Recupera em _y a chave antecessora a _x , se existir ( true ).
		 * @param 	_x 	Chave 1
		 * @param 	_y  Chave 2
		 * @return	True se existir sucessor caso contrário, false
		*/
		bool predecessor(const Key & _x, Key & _y ) const
		{
			int position = _search(_x); //!< Posição do elemento

			/// A CHAVE _X FOI ENCONTRADA E NÃO É A PRIMEIRA CHAVE
			if( (position != -1) and (position != 0) )
			{	
				_y = DAL<Key, Data, KeyComparator>::mpt_Data[position].id;
				return true;
			}
			/// A CHAVE _X ŃÃO FOI ENCONTRADA OU(OR) É A PRIMEIRA CHAVE
			else
				return false;	 
		} 
};

#endif 