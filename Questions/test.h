#pragma once

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
class Handle : public BaseHandle
{
public:
	Handle() {}
	Handle( BaseHandle t ): BaseHandle( t ) { }

	T * Get() const
	{
		return manager->GetAs< T >( *this );
	}

	T* operator -> () const
	{
		return Get();
	}
};

class Entity
{
public:
	virtual ~Entity() { std::cout << "\nEntity destructor called\n"; }
	class BaseHandle self;
};

class Object : public Entity
{
public:
	~Object() { std::cout << "\nObject destructor called\n"; }
	int data = 15;
};

class Component
{
public:
	int data = 10;
};

typedef Handle< Object > ObjectHandle;
typedef Handle< Component > ComponentHandle;

std::unique_ptr< HandleManager > BaseHandle::manager = nullptr;
