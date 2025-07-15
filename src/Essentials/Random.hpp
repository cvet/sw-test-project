#pragma once

#include <cstdint>
#include <random>

namespace sw
{
	class Random
	{
	public:
		explicit Random(uint32_t seed) :
				_gen(seed)
		{}

		Random(const Random&) = delete;
		Random& operator=(const Random&) = delete;
		Random(Random&&) noexcept = default;
		Random& operator=(Random&&) noexcept = default;
		~Random() = default;

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
