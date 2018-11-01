#pragma once

namespace Reflex
{
	namespace Core
	{
		template< class T >
		class Handle : public BaseHandle
		{
		public:
			Handle( const std::weak_ptr< T >& ptr );

			template< class V >
			Handle( const std::shared_ptr< V >& ptr );

			T* Get() const;
			T* operator->() const;

			explicit operator bool() const;
			bool operator==( const Handle< T >& other ) const;
			bool operator!=( const Handle< T >& other ) const;
			bool IsValid() const;

			template< class V >
			Handle( const Handle< V >& handle ) = delete;

			std::weak_ptr< T > m_ptr;
		};
	}
}

#include <type_traits>

namespace Reflex
{
	namespace Core
	{
		// Forward declaration of common handle types
		typedef Handle< class Object > ObjectHandle;

		// Template functions
		template< class T >
		Handle< T >::Handle( const std::weak_ptr< T >& ptr )
			: m_ptr( ptr )
		{

		}

		template< class T >
		template< class V >
		Handle< T >::Handle( const std::shared_ptr< V >& ptr )
			: m_ptr( std::static_pointer_cast< T >( ptr ) )
		{

		}

		template< class T >
		T* Handle< T >::Get() const
		{
			return m_ptr;
		}

		template< class T >
		T* Handle< T >::operator ->() const
		{
			return m_ptr.lock().get();
		}

		template< class T >
		Handle< T >::operator bool() const
		{
			return IsValid();
		}

		template< class T >
		bool Handle< T >::operator==( const Handle< T >& other ) const
		{
			return m_ptr == other.m_ptr;
		}

		template< class T >
		bool Handle< T >::operator!=( const Handle< T >& other ) const
		{
			return !( *this == other );
		}

		template< class T >
		bool Handle< T >::IsValid() const
		{
			return !m_ptr.expired();
		}
	}
}

// Hash function for handles allows it to be used with hash maps such as std::unordered_map etc.
namespace std
{
	template< class T >
	struct hash< Reflex::Core::Handle< T > >
	{
		std::size_t operator()( const Reflex::Core::Handle< T >& k ) const
		{
			return hash< uint32_t >()( k->Get() );
		}
	};
}