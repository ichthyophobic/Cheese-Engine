#pragma once

#include "coordinate.hpp"
#include "bitmap.hpp"
#include "piece.hpp"
#include "move.hpp"

enum class MoveType : unsigned char
{
	Normal,
	Casteling,
	EnPassant,
	Promotion,
};

using usize = unsigned long long;

class Move
{
	Coordinate m_from;
	Coordinate m_to;
	PieceType m_captured_type;
	PieceColor m_captured_color;
	MoveType m_type;
	PieceType m_promotion_type;

public:

	Move() {}
};

class MovesCache
{
	Move* m_ptr;
	usize m_size;
	usize m_capacity;

	void size_check()
	{
		if (m_size != m_capacity)
			return;

		auto new_capacity { m_capacity * 2 };
		auto new_ptr { new Move[new_capacity] };

		for (usize i {}; i < m_size; ++i)
			new_ptr[i] = move(m_ptr[i]);

		delete[] m_ptr;

		m_capacity = new_capacity;
		m_ptr = new_ptr;
	}

public:

	bool is_empty() { return m_size == 0; }

	void push(Move m)
	{
		size_check();
		m_ptr[m_size++] = move(m);
	}

	Move pop()
	{
		if (is_empty())
			throw "Can't pop from empty moves cache.";

		return move(m_ptr[--m_size]);
	}

	MovesCache(usize capacity)
		: m_size(0)
		, m_capacity(capacity ? capacity : ++capacity)
	{
		m_ptr = new Move[capacity];
	}
};
