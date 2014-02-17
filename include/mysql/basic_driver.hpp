#ifndef MYSQL_DRIVER_INCLUDED_
#define MYSQL_DRIVER_INCLUDED_

#include "../core/non_copyable.hpp"

namespace mysql {

	class basic_driver : fp::non_copyable {
	public:
		basic_connection* connect(const std::string& host, const std::string& user, const std::string& pass);

		const std::string& name() const;
	private:
		std::unique_ptr<detail::basic_driver_impl> self_;
	};
}

#endif
