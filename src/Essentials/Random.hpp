#pragma once

#include <cstdint>
#include <random>
#include <stdexcept>

namespace sw
{
	class Random
	{
	public:
		explicit Random(uint32_t seed) :
				_gen(seed)
		{}

		template <typename T>
		T getAny(const std::vector<T>& items)
		{
			if (items.empty())
			{
				throw std::runtime_error("Cannot pick from an empty vector");
			}

			return items[generate(static_cast<size_t>(0), items.size() - 1)];
		}

		template <typename T>
			requires(std::is_integral_v<T>)
		T generate(T min, T max)
		{
			return std::uniform_int_distribution<T>(min, max)(_gen);
		}

	private:
		std::mt19937 _gen;
	};
}
