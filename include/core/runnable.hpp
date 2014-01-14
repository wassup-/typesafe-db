/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef RUNNABLE_HPP_
#define RUNNABLE_HPP_

#include "../assert.hpp"
#include "../forward.hpp"

#include <memory>

namespace fp {

	template<typename T>
	void run(const T&) = delete;

	namespace adl {

		template<typename T>
		void run(const T& fn) {
			using fp::run;
			run(fn);
		}
	}

	class Runnable {
	public:
		Runnable()
		: self_(nullptr)
		{ }

		Runnable(std::nullptr_t)
		: self_(nullptr)
		{ }

		template<typename T>
		Runnable(T&& x)
		: self_(std::make_shared<holder<T>>(fix::forward<T>(x)))
		{ }

		void run() const {
			FP_ASSERT(self_, "runnable is empty");
			self_->run();
		}

		explicit operator bool() const {
			return static_cast<bool>(self_);
		}

		friend void run(const Runnable& runnable) {
			runnable.run();
		}

		friend void swap(Runnable& l, Runnable& r) {
			using std::swap;
			swap(l.self_, r.self_);
		}
	private:
		struct impl {
			virtual ~impl() = default;
			virtual void run() const = 0;
		};

		template<typename T>
		struct holder : impl {
		public:
			holder(T&& x)
			: self_(std::move(x))
			{ }

			void run() const override {
				self_.run();
			}
		private:
			T self_;
		};

		std::shared_ptr<const impl> self_;
	};
}

#endif