#pragma once

#include "piece.hpp"
#include "coordinate.hpp"

using map64 = unsigned long long;

class Bitmap
{
	map64 m_white;
	map64 m_black;
	map64 m_pawn;
	map64 m_knight;
	map64 m_bishop;
	map64 m_rook;
	map64 m_queen;
	map64 m_king;

	short cal_cor(Coordinate cor)
	{
		return cor.y * 8 + cor.x;
	}

	map64& get_map(PieceType type)
	{
		using enum PieceType;

		switch (type)
		{
		case Pawn:
			return m_pawn;
		case Knight:
			return m_knight;
		case Bishop:
			return m_bishop;
		case Rook:
			return m_rook;
		case Queen:
			return m_queen;
		case King:
			return m_king;
		}
	}

	map64& get_map(PieceColor color)
	{
		using enum PieceColor;

		switch (color)
		{
		case White:
			return m_white;
		case Black:
			return m_black;
		}
	}

public:

	void move_piece(Coordinate from, Coordinate to)
	{
		if (!is_piece(from))
			throw "Can't move piece that doesn't exist.";

		auto& from_type { get_map(get_type(from)) };
		auto& to_type { get_map(get_type(to)) };

		auto& from_color { get_map(get_color(from)) };
		auto& to_color { get_map(get_color(to)) };

		from_type &= ~(1ull << cal_cor(from));
		from_color &= ~(1ull << cal_cor(from));

		to_type |= (1ull << cal_cor(to));
		to_color |= (1ull << cal_cor(to));
	}

	map64 get_mask(Coordinate cor)
	{
		return (m_black | m_white) & (1ull << cal_cor(cor));
	}

	bool is_type(PieceType type, Coordinate cor)
	{
		auto map { get_map(type) };
		return (map >> cal_cor(cor)) & 1;
	}

	PieceType get_type(Coordinate cor)
	{
		using enum PieceType;

		if ((m_pawn >> cal_cor(cor)) & 1)
			return Pawn;

		if ((m_knight >> cal_cor(cor)) & 1)
			return Knight;

		if ((m_bishop >> cal_cor(cor)) & 1)
			return Bishop;

		if ((m_rook >> cal_cor(cor)) & 1)
			return Rook;

		if ((m_queen >> cal_cor(cor)) & 1)
			return Queen;

		if ((m_king >> cal_cor(cor)) & 1)
			return King;

		throw "Trying to get type of a non-existing piece.";
	}

	bool is_color(PieceColor color, Coordinate cor)
	{
		auto map { get_map(color) };
		return (map >> cal_cor(cor)) & 1;
	}

	PieceColor get_color(Coordinate cor)
	{
		if (is_color(PieceColor::White, cor))
			return PieceColor::White;

		if (is_color(PieceColor::Black, cor))
			return PieceColor::Black;

		throw "Trying to get color of non-existing piece.";
	}

	bool is_piece(Coordinate cor)
	{
		return ((m_white | m_black) >> cal_cor(cor)) & 1;
	}

	Bitmap()
		: m_white(0x000000000000FFFFULL)
		, m_black(0xFFFF000000000000ULL)
		, m_pawn (0x00FF00000000FF00ULL)
		, m_knight(0x4200000000000042ULL)
		, m_bishop(0x2400000000000024ULL)
		, m_rook (0x8100000000000081ULL)
		, m_queen(0x0800000000000008ULL)
		, m_king (0x1000000000000010ULL)
	{}
};
