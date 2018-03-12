/**
 * @file 	list.h
 * @brief	Contém a classe list(Lista duplamente Encadeada) e a implementação de seus métodos
 *          além das classes const_iterator e iterator com suas implementações 
 * @author 	Samuel Lucas de Moura Ferino (samuel1797@gmail.com)
 * @since 	24/11/17
*/

#ifndef _LIST_H
#define _LIST_H

#include <cassert>

namespace lc{
	template<typename T>
	/** 
	 * @brief	Classe list (Lista duplamente encadeada)
	*/
	class list{
		private:
			/** 
			 * @brief	Struct que define como são os Nós da classe list 
			*/
			struct Node{
				/** @brief	Conteúdo do nó */
				T data;
				/** @brief	Ponteiro para o próximo nó */
				Node* next;
				/** @brief	Ponteiro para o nó anterior */
				Node* prev;

				/** 
				 * @brief	Construtor da struct Nó
				 * @param 	_data Conteúdo do nó
				 * @param 	_next Ponteiro para o próximo nó
				 * @param 	_prev Ponteiro para o nó anterior
				*/ 
				Node( T _data=T(), Node* _next=nullptr, Node* _prev=nullptr): data(_data),
				        next(_next), prev(_prev){};
			};		

		public:

			using size_type = unsigned long;
			
			class const_iterator {
				public :
					/** 
					 * @brief 	Contrutor padrão
					*/
					const_iterator( ){ /*  Empty  */}
					/** 
					 * @brief 	Sobrecarga do operador *
					*/
					const T& operator* ( ) const
					{
						return current->data;
					}
					/** 
					 * @brief 	Sobrecarga do operador ++ (PELA ESQUERDA)
					*/
					const_iterator& operator++ ( ) 	// ++it;
					{
						assert(current->next != nullptr);
						current = current->next;
						return current;
					}
					/** 
					 * @brief 	Sobrecarga do operador ++ (PELA DIREITA)
					*/
					const_iterator operator++ ( int )  // it++;
					{
						assert(current->next != nullptr);
						current =  current->next;
						return current;
					} 	
					/** 
					 * @brief 	Sobrecarga do operador -- (PELA ESQUERDA)
					*/
					const_iterator & operator-- ( ) // --it;
					{
						assert(current->prev != nullptr);
						current = current->prev;
						return current;
					}
					/** 
					 * @brief 	Sobrecarga do operador -- (PELA DIREITA)
					*/
					const_iterator operator-- ( int )  // it--;
					{
						assert(current->prev != nullptr);
						current = current->prev;
						return current;
					} 
					/** 
					 * @brief 	Sobrecarga do operador ==
					 * @param	rhs Iterador a ser comparado	
					*/
					bool operator== ( const const_iterator & rhs ) const
					{
						if( rhs.size() == size())
						{

						}
						else
						{
							return false;
						}
					}
					/** 
					 * @brief 	Sobrecarga do operador !=
					 * @param	rhs Iterador a ser comparado	
					*/
					bool operator!= ( const const_iterator & rhs ) const
					{
						if( rhs.size() == size())
						{
							return false;
						}
						else
						{

						}	

					}
				protected:
					Node *current;
					const_iterator( Node * p ) : current( p ){}
					friend class list<T>;
			};
			
	//		class iterator : public const_iterator
	//		{
	//			public:
					/** 
					 * @brief 	Construtor	padrão	
					*/
	//				iterator( ) : const_iterator() { /* Empty */ }
					/** 
					 * @brief 	Sobrecarga do operador *	
					*/
	//				const T& operator * ( ) const
	//				{
	//					return current->data;					
	//				}
	//				T& operator * ( )
	//				{
	//					return current->data;
	//				}
					/** 
					 * @brief 	Sobrecarga do operador ++ (PELA ESQUERDA)
					*/
	//				iterator& operator ++( )
	//				{
	//					assert(current->next!= nullptr);
	//					current = current->next;
	//					return current;
	//				}
					/** 
					 * @brief 	Sobrecarga do operador ++ (PELA DIREITA)
					*/
	//				iterator operator ++ (int )
	//				{
	//					assert(current->next!= nullptr);
	//					current = current->next;
	//					return current;
	//				}
					/** 
					 * @brief 	Sobrecarga do operador -- (PELA ESQUERDA)
					*/
	//				iterator& operator-- ( )
	//				{
	//					assert(current->prev!= nullptr);
	//					current = current->prev;
	//					return current; 
	//				}
					/** 
					 * @brief 	Sobrecarga do operador -- (PELA DIREITA)
					*/
	//				iterator operator-- (int )
	//				{
	//					assert(current->prev!= nullptr);
	//					current = current->prev;
	//					return current;
	//				}

	//			protected :
	//				iterator( Node *p ) : const_iterator( p ){}
	//				friend class list<T>;
	//		};
			
			// [I] SPECIAL MEMBERS
			
			/** 
			 * @brief	Construtor padrão
			*/ 	
			list(){
			 	m_tail=new Node();
				m_head=new Node();

				m_tail->next=nullptr;
				m_tail->prev=m_head;
				m_head->next=m_tail;
				m_head->prev=nullptr;

				m_size=0;
			}

			/** 
			 * @brief	Construtói uma lista com elementos padrão
			 * @param	count Tamanho da lista
			*/ 	
			explicit list(size_type count):list()
			{
				for(unsigned int i = 0; i < count; ++i)
				{
					push_front(T());
				}
			}
		
		
        	/** 
			 * @brief	Destrutor
			*/ 	
			~list(){
				clear(); 
			}

/*			list(const list& _list)
			{
				Node* ptr_1 = _list.m_head->next;

				while (ptr_1->next != _list.m_tail)
				{	
					Node* ptr_2 = ptr_1;
					push_front(ptr_2->data);
					ptr_1 = ptr_1->next;
				}	
			}
		
			list& operator= (const list &)

		*/	

/*			
			bool operator==(const list& lhs)
			{
				if( lhs.size() == size())
				{
					Node* lhs_ptr  = lhs.m_head;
					aux_ptr = m_head;

					for( ;lhs_ptr != lhs.m_tail; lhs_ptr = lhs_ptr->next, rhs_ptr = rhs_ptr->next)
					{
						if( lhs_ptr->data != rhs_ptr-> data)
							return false;	
					}		

					return true;
				}
				else
					return false;
			}

			bool operator!=(const list& lhs)
			{
				if( lhs.size() == size() )
				{
					Node* lhs_ptr = lhs.m_head;
					Node* rhs_ptr = rhs.m_head;
					
					for(;lhs_ptr != lhs.m_tail;)
					{
						if( lhs_ptr->data != rhs_ptr->data)
							return true;	
					}
					
					return false;
				}
				else
					return true;	
			}
*/
		
			// [III] Capacity

			/**
			 * @brief	Retorna o tamanho da lista	
			 * @return	Tamanho da lista	
			*/ 
			int size( ) const
			{
				return m_size;
			}
				
			/**
			 * @brief	Verifica se lista está vazia
			 * @return	Se estiver vazia retorna true, senão false	
			*/ 
			bool empty( ) const
			{
				if( m_size == 0)
					return true;
				else
					return false;
			}
			
			// [IV] Modifiers
			/** 
			 * @brief	Apaga todos os elementos da lista(físicos e lógicos)
			*/
			void clear( )
			{
				while( not empty())
				{
					pop_front();
				}	
			}

			T & front( )
			{
				return (m_head->next)->data;
			}
			const T & front( ) const
			{
				return (m_head->next)->data;
			}
			T & back( )
			{
				return (m_tail->prev)->data;
			}
			const T & back( ) const
			{
				return (m_tail->prev)->data;
			}

			/**
			 * @brief	Adiciona um nó no fim da lista
			 * @param   value Contéudo do nó a ser adicionado	
			*/
			void push_back( const T & value )
			{
				if(m_head->next != m_tail){		
					/** @brief 	Nó a ser inserido no fim da lista */
					Node* novo_ultimo_no = new Node(value);	
					/** @brief 	Antigo último nó da lista */
					Node* antigo_ultimo_no = m_head->next;

					while( (antigo_ultimo_no->next) != m_tail)
					{
						antigo_ultimo_no=antigo_ultimo_no->next;
					}	

					novo_ultimo_no->next=m_tail;
					novo_ultimo_no->prev=antigo_ultimo_no;
					antigo_ultimo_no->next=novo_ultimo_no;
					m_tail->prev=novo_ultimo_no;
				}
				else
				{
					push_front(value);
				}
					
				++m_size;	
			}
			
			/**
			 * @brief	Adiciona um nó no início da lista
			 * @param   value Contéudo do nó a ser adicionado	
			*/
			void push_front( const int& value )
			{
				/** @brief 	Nó a ser inserido no início da lista */
				Node* novo_no = new Node(value);

				// NENHUM ELEMENTO NA LISTA
				if(m_head->next == m_tail)
				{
					novo_no->next=m_tail;
					novo_no->prev=m_head;

					m_head->next=novo_no;
					m_tail->prev=novo_no;

				}
				// AO MENOS UM ELEMENTO NA LISTA
				else
				{
					/** @brief	Primeiro nó da lista */
					Node* aux_head = m_head->next;
	
					novo_no->next=aux_head;
					novo_no->prev=m_head;
					aux_head->prev=novo_no;
					m_head->next=novo_no;

				}

				++m_size;
			}
			/**
			 * @brief	Remove o nó do início da lista
			*/
			void pop_front( )
			{
				if( (m_head->next) != m_tail)
				{					
					/** @brief	Nó que será excluído */
					Node* no_excluido=m_head->next;
					Node* proximo_no=no_excluido->next;
					m_head->next=proximo_no;
					proximo_no->prev=m_head;
					delete no_excluido;
					--m_size;
				}	
			}
			/**
			 * @brief	Remove o nó do fim da lista
			*/
			void pop_back( )
			{
				if(m_head->next != m_tail)
				{	
					/** @brief	Nó que será excluído */
					Node* no_excluido=m_head->next;

					while( (no_excluido->next) != m_tail)
					{
						no_excluido=no_excluido->next;
					}

					/** @brief	Nó anteiro ao nó que será excluído */
					Node* no_anterior=no_excluido->prev;
					no_anterior->next=m_tail;
					m_tail->prev=no_anterior;
					delete no_excluido;
					--m_size;	
				}
			}

		private:
			/** @brief	Ponteiro para o final da lista */
			Node* m_tail;
			/** @brief	Tamanho da lista */
			int m_size;
			/** @brief	Ponteiro para o inicio da lista */
			Node* m_head;

	};		
}

#endif