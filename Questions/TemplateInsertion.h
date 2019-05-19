#pragma once

#include <string>

class Action
{
public:
	Action( const std::string& actionName, const int actionId )
		: name( actionName )
		, id( actionId )
	{ 
	}

	template< typename T >
	void ExampleTemplateFunc()
	{

	}

private:
	const std::string name;
	const int id = 0;
};

class Projectile : public Action
{
public:
	Projectile( const std::string& actionName, const int actionId )
		: Action( actionName, actionId )
	{
	}
};

class ProjectileServer : Projectile
{
public:
	ProjectileServer( const std::string& actionName, const int actionId )
		: Projectile( actionName, actionId )
	{
	}
};

template< class T >
class Fireball : public T
{
public:
	Fireball( const std::string& actionName, const int actionId )
		: Projectile( actionName, actionId )
	{
		// The this-> here is required for GCC compilation
		std::cout << "Name = " << this->name;

		// The template specifier here is required for GCC compilation
		this->template ExampleTemplateFunc();
	}
};

class FireballClient : public Fireball< Projectile >
{
public:
	FireballClient( const std::string& actionName, const int actionId )
		: Fireball< Projectile >( actionName, actionId )
	{
	}
};

class FireballServer : public Fireball< ProjectileServer >
{
public:
	FireballServer( const std::string& actionName, const int actionId )
		: Fireball< ProjectileServer >( actionName, actionId )
	{
	}
};

static FireballServer fireballServer( "Fireball", 0 );