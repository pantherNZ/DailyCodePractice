#pragma once

class Object
{
public:
	int data = 15;
};

class Component
{
public:
	int data = 10;
};

template< class T >
class Handle;

class HandleManager
{
public:
	template< class T >
	T* GetAs( Handle< T > handle )
	{
		return ( T* )data;
	}

	void* data;
};

class BaseHandle
{
public:
	static std::unique_ptr< HandleManager > manager;
};

template< class T >
class Handle : BaseHandle
{
public:
	T* Get() const
	{
		return manager->GetAs< T >( *this );
	}

	T* operator -> () const
	{
		return Get();
	}
};

typedef Handle< Object > ObjectHandle;
typedef Handle< Component > ComponentHandle;

std::unique_ptr< HandleManager > BaseHandle::manager = nullptr;
