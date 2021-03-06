/**********************************************************************
 *  This file is part of flatsurf.
 *
 *        Copyright (C) 2019 Julian Rüth
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

#ifndef LIBFLATSURF_CONTOUR_DECOMPOSITION_HPP
#define LIBFLATSURF_CONTOUR_DECOMPOSITION_HPP

#include <memory>
#include <vector>

#include "external/spimpl/spimpl.h"

#include "forward.hpp"

namespace flatsurf {
template <class Surface>
class ContourDecomposition {
  static_assert(std::is_same_v<Surface, std::decay_t<Surface>>, "type must not have modifiers such as const");

  using T = typename Surface::Coordinate;

 public:
  ContourDecomposition(std::unique_ptr<Surface>, const Vector<T> &vertical);

  std::vector<ContourComponent<Surface>> components() const;

  template <typename S>
  friend std::ostream &operator<<(std::ostream &, const ContourDecomposition<S> &);

  std::shared_ptr<const FlatTriangulationCollapsed<T>> collapsed() const;

 private:
  using Implementation = ImplementationOf<ContourDecomposition>;
  spimpl::unique_impl_ptr<Implementation> impl;

  friend Implementation;
};
}  // namespace flatsurf

#endif
