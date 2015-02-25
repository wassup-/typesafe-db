/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef NON_COPYABLE_HPP
#define NON_COPYABLE_HPP

namespace fp
{

struct non_copyable
{
private:
  non_copyable(non_copyable const &) = delete;
  non_copyable & operator=(non_copyable const &) = delete;

protected:
  non_copyable() = default;
};

}

#endif
