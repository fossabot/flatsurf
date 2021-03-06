/**********************************************************************
 *  This file is part of flatsurf.
 *
 *        Copyright (C) 2019-2020 Julian Rüth
 *
 *  Flatsurf is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Flatsurf is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with flatsurf. If not, see <https://www.gnu.org/licenses/>.
 *********************************************************************/

#ifndef LIBFLATSURF_EDGE_SET_ITERATOR_HPP
#define LIBFLATSURF_EDGE_SET_ITERATOR_HPP

#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_facade.hpp>

#include "external/spimpl/spimpl.h"

#include "forward.hpp"

namespace flatsurf {

class EdgeSetIterator : public boost::iterator_facade<EdgeSetIterator, const Edge &, boost::forward_traversal_tag> {
  template <typename... Args>
  EdgeSetIterator(PrivateConstructor, Args &&...);

 public:
  using value_type = Edge;

  void increment();
  const value_type &dereference() const;
  bool equal(const EdgeSetIterator &other) const;

 private:
  using Implementation = ImplementationOf<EdgeSetIterator>;
  spimpl::impl_ptr<Implementation> impl;
  friend Implementation;
  friend EdgeSet;
};

}  // namespace flatsurf

#endif
