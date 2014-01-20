#ifndef PRIMARY_KEY_HPP_
#define PRIMARY_KEY_HPP_

namespace fp {

	template<typename Column>
	struct primary_key {
	public:
		constexpr primary_key(const Column& column) noexcept
		: column_(column)
		{ }

	public:
		template<typename U>
		constexpr friend bool operator==(const primary_key& k, const U& c) noexcept {
			return std::is_same<Column, U>::value;
		}

	private:
		const Column& column_;
	};

	template<typename Column>
	struct unique_key {
	public:
		constexpr unique_key(const Column& column) noexcept
		: column_(column)
		{ }

	public:
		template<typename U>
		constexpr friend bool operator==(const unique_key& k, const U& c) noexcept {
			return std::is_same<Column, U>::value;
		}

	private:
		const Column& column_;
	};

	template<typename Column>
	struct index_key {
	public:
		constexpr index_key(const Column& column) noexcept
		: column_(column)
		{ }

	public:
		template<typename U>
		constexpr friend bool operator==(const index_key& k, const U& c) noexcept {
			return std::is_same<Column, U>::value;
		}

	private:
		const Column& column_;
	};
}

#endif