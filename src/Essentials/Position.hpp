#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>

namespace sw
{
	struct pos_t
	{
		constexpr pos_t() = default;

		constexpr pos_t(int32_t x, int32_t y) :
				x(x),
				y(y)
		{}

		constexpr bool operator==(const pos_t& other) const
		{
			return x == other.x && y == other.y;
		}

		constexpr bool operator!=(const pos_t& other) const
		{
			return !(*this == other);
		}

		constexpr pos_t operator+(const pos_t& other) const
		{
			return pos_t(x + other.x, y + other.y);
		}

		constexpr pos_t operator-(const pos_t& other) const
		{
			return pos_t(x - other.x, y - other.y);
		}

		constexpr pos_t& operator+=(const pos_t& other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		constexpr pos_t& operator-=(const pos_t& other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}

		int32_t distanceTo(const pos_t& other) const
		{
			// Chebyshev Distance
			return std::max(std::abs(x - other.x), std::abs(y - other.y));
		}

		int32_t x{};
		int32_t y{};
	};
}
