#pragma once

#include <unordered_set>

#include "test.h"

class TileMap
{
public:
	TileMap( int boundsX, int boundsY, unsigned gridSize ) : m_gridSize( gridSize ), m_boundsX( boundsX ), m_boundsY( boundsY )
	{
		int x = std::ceil( boundsX / gridSize );
		int y = std::ceil( boundsY / gridSize );
		spacialData.reserve( x * y );
	}

	void Insert( ObjectHandle obj )
	{

	}

	void Insert( ObjectHandle obj, int topLeftX, int topLeft, int botRightX, int botRightY )
	{

	}

	unsigned Hash( int x, int y )
	{
		const auto hashX = int( m_gridSize * ( float )x / ( float )m_boundsX );
		const auto hashY = int( m_gridSize * ( float )y / ( float )m_boundsY );
		return hashY * m_gridSize + hashX;
	}

protected:


private:
	int m_boundsX = 0;
	int m_boundsY = 0;
	unsigned m_gridSize = 0U;
	std::vector< std::unordered_set< ObjectHandle > > spacialData;
};