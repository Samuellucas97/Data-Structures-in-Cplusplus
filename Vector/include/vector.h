#ifndef VECTOR_H
#define VECTOR_H

#include <cstdlib>
#include <iostream>
#include <cstddef> // size_t
#include <stdexcept> // std::out_of_bounds
#include <iterator> // bidirectional_iterator_tag
#include <cassert>

namespace sc {
	template < typename T >
	class MyIterator
	{
	    private:
	        T* m_ptr; // Pointer into the array.
	   
	    public:
	        // Belowe we have the iterator_traits common interface
	        typedef std::ptrdiff_t difference_type; //<! Difference type used to calculated distance between iterators.
	        typedef T value_type;           //<! Value type the iterator points to.
	        typedef T* pointer;             //<! Pointer to the value type.
	        typedef T& reference;           //<! Reference to the value type.
	        typedef const T& const_reference;           //<! Reference to the value type.
	        typedef std::random_access_iterator_tag iterator_category; //<! MyIterator category.

	        /// Default constructor.
	        MyIterator( T* ptr): m_ptr(ptr){ }

			/// Default constructor.
	        MyIterator( ){ }
	
		    /**
		     * @brief	Sobrecarga do operador *
		    */
	        T& operator*(void) const
	        {
	            assert( m_ptr != nullptr );
	            return *m_ptr;
	        }

		    /**
		     * @brief	Sobrecarga do operador -
		    */
	        difference_type operator-( const MyIterator& other )
	        {
	            return m_ptr - other.m_ptr;
	        }

	        
		    /**
		     * @brief	Sobrecarga do operador ++
		    */
	        MyIterator operator++(void)
	        {
	            assert( m_ptr != nullptr );
	            ++m_ptr;
	            return *this;
	        }

		    /**
		     * @brief	Sobrecarga do operador ++
		    */
		    MyIterator operator++(int)
	        {
	            MyIterator temp( *this );
	            ++m_ptr;
	            return temp;
	        }

				
		    /**
		     * @brief	Sobrecarga do operador --
		    */ 
	        MyIterator operator--(void)
	        {
	            assert( m_ptr != nullptr );
	            --m_ptr;
	            return *this;
	        }

		    /**
		     * @brief	Sobrecarga do operador --
		    */
	        MyIterator operator--(int)
	        {
	            MyIterator temp( *this );
	            --m_ptr;
	            return temp;
	        }

	        MyIterator operator=(const MyIterator& other)
	        {
	        	return m_ptr = other.m_ptr;
	        }

		    /**
		     * @brief	Sobrecarga do operador !=
		    */
		    bool operator!=(const MyIterator& other) const
	        {
	            return m_ptr != other.m_ptr;
	        }
	       
		    /**
		     * @brief	Sobrecarga do operador ==
		    */
		    bool operator==(const MyIterator& other) const
	        {
	            return m_ptr == other.m_ptr;
	        }
	};

    /// sequence container based on a dynamic size array.
    template < typename T >
    class vector
    {
        public:
            //=== Alias
            typedef size_t size_type; //!< size type alias.
			using iterator = MyIterator< T >; // Veja Code 3
			using const_iterator = MyIterator< const T >; // Veja Code 3
			typedef T value_type;
            typedef const value_type& const_reference;
            typedef value_type& reference;
            typedef value_type* pointer;
            typedef std::ptrdiff_t difference_type;
	
            //=== Special methods
            /// Default constructor.
            explicit vector( size_type cap_ = 1 )
                : data( new T[ cap_ ] )
                , size( 0 )
                , capacity( cap_ )
            { /* empty */ }

            //=== Public interface

			/** 
			 * @brief	Reserva um espaço na memória 
			*/
            void reserve( size_type new_cap )
            {
                // if current storage area is large enough, nothing to do here.
                if ( new_cap <= capacity )
                    return;

                // 1) allocate the new storage area.
                T* temp = new T[ new_cap ];
                // 2) Copy/Tranfer/backup elements from the origina storage area
                // into the new storage.
                for( auto i(0u) ; i < size ; ++i )
                    temp[ i ] = data[ i ];
                // 3) Free the old memory
                delete [] data;
                // 4) Reassign the data storage.
                data = temp;
                // 5) update the real capacity
                capacity = new_cap;

                // debug only
                for ( auto i(size) ; i < capacity ; ++i )
                    data[i] = T();
            }
     
			/** 
			 * @brief  Insere no final lógico do vector 
			*/
	        void push_back( const T& value )
            {
                // Test whether we have enough space for a insertion.
                if ( size == capacity )
                    reserve( 2 * capacity );

                // Insert the new element at the end.
                data[ size++ ] = value;
            }

			/** 
			 * @brief  Retira no final lógico do vector 
			*/
			void pop_back()													
			{
				if(size !=capacity)
				{
					--size;
				}	
			}

			/** 
			 * @brief	Verifica se o vector está vazio 
			 * @return	Se o vetor está vazio(True) ou não(False)		
			*/
			bool empty( void ) const
			{
				if ( sizer() == 0 )
					return true;
				
				return	false;
			}

			size_type sizer( void ) const
			{
				return size;
			}

			size_type capacidade( void ) const
			{
				return capacity;
			}


			iterator begin( void )
			{
				return iterator( &data[0]);
			}
	
			iterator end( void )
			{
				return iterator( &data[size-1]);
			}
		
			const_iterator cbegin( void ) const
			{
				return const_iterator(&data[0]);
			}

			const_iterator cend( void ) const
			{
				return const_iterator(&data[size]);
			}

			/** 
			 * @brief	Retorna, de forma constante, o elemento no vector solicitado de acordo com a posição 
			*/
			const_reference operator []( size_type indice) const
			{
				return data[indice];	
			}

			/** 
			 * @brief	Retorna o elemento no vector solicitado de acordo com a posição 
			*/
			reference operator []( size_type indice)
			{
				return data[indice];
			}

			/** 
			 * @brief	Retorna, de forma constante, o elemento no vector solicitado de acordo com a posição, verificando 
			se a posição indicada é menor que o tamanho do vector 
			*/
			const_reference at( size_type indice) const
			{
				if( indice > sizer())
					throw std::out_of_range("vector::at() -> acesso fora do vector!");
				
				return data[indice];
			}
			/** 
			 * @brief	Retorna o elemento no vector solicitado de acordo com a posição, verificando 
			se a posição indicada é menor que o tamanho do vector
			*/
			
			reference at( size_type indice)
			{
				if( indice > sizer())
					throw std::out_of_range("vector::at() -> acesso fora do vector!");
				
				return data[indice];
			}
		
  			/** 
			 * @brief	Retorna, de forma constante, o primeiro elemento do vector 
			*/
            const_reference front( void ) const
            {
                return *cbegin();
            }			
		
  			/** 
			 * @brief	Retorna, de forma constante, o último elemento do vector 
			*/
            const_reference back( void ) const
           {
                return *cend();
           }


           pointer datas( void ) const
           {
                return data;
           }
			
			iterator erase( iterator k)
		   {
		//		if (k <= end() and k >= begin())
			//	{
					
					for(auto o = end() - k; o !=0;k++)
					{
											
						*k = *++k; 
					}
					
					--size;	
				//}	
			}	


			/**
			 * @brief	Sobrecarga do operador !=
			*/
			bool operator !=( const vector & v1) const
			{
				if(v1.sizer() == sizer())
				{
					
					for(unsigned int i = 0; i < size; i++)
					{
						if( data[i] != v1[i] )
							return true;		
					}

					return false;	

				}
				else
					return true;
			}

			/**
			 * @brief	Sobrecarga do operador ==
			*/
			bool operator ==( const vector & v1) const
			{
				if(v1.sizer() == sizer())
				{
					
					for(unsigned int i = 0; i < size; i++)
					{
						if( data[i] != v1[i] )
							return false;		
					}

					return true;	

				}
				else
					return false;
			}

			/** 
			 * @brief	Sobrecarga do operador de inserção 
			*/
			friend std::ostream& operator<<( std::ostream& os_, const vector<T> &v )
            {
                os_ << "[ ";
                for( auto i(0u) ; i < v.size ; ++i )
                    os_ << v.data[i] << " ";
                os_ << "| ";
                for( auto i(v.size) ; i < v.capacity ; ++i )
                    os_ << v.data[i] << " ";
                os_ << "]";
                return os_;
            }
			
        private:

            //=== Members
       	    T * data;           //!< Storage area.
			size_type size;     //!< Number of elements in the vector (logical size).
            size_type capacity; //!< Max capacity of vector.
    };
}
#endif
