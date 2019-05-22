/**********************************************************************
 *  This file is part of flatsurf.
 *
 *        Copyright (C) 2019 Julian Rüth
 *
 *  Flatsurf is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
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

#ifndef LIBFLATSURF_VECTOR_EANTIC
#define LIBFLATSURF_VECTOR_EANTIC

#include <e-antic/renfxx.h>
#include <boost/operators.hpp>
#include <iosfwd>

#include "flatsurf/forward.hpp"
#include "flatsurf/vector_along_triangulation_with_approximation.hpp"

namespace flatsurf {
class VectorEAntic : boost::additive<VectorEAntic>,
                     boost::multipliable<VectorEAntic, int>,
                     boost::equality_comparable<VectorEAntic> {
 public:
  using V = VectorEAntic;
  friend VectorArb;

  VectorEAntic();
  VectorEAntic(const eantic::renf_elem_class &x,
               const eantic::renf_elem_class &y);

  CCW ccw(const V &) const;
  ORIENTATION orientation(const V &) const;

  friend std::ostream &operator<<(std::ostream &os, const VectorEAntic &);
  V operator-() const;
  bool operator<(const Bound bound) const;
  bool operator>(const Bound bound) const;
  bool operator==(const VectorEAntic &) const;
  explicit operator bool() const;
  V &operator+=(const VectorEAntic &rhs);
  V &operator-=(const VectorEAntic &rhs);
  V &operator*=(const int rhs);
  // Note that the returned VectorArb is only valid as long as this element
  // is unchanged.
  operator const VectorArb &() const;

  // Note that the returned coordinate is only valid as long as this element is unchanged.
  const eantic::renf_elem_class &x() const;
  // Note that the returned coordinate is only valid as long as this element is unchanged.
  const eantic::renf_elem_class &y() const;

  using AlongTriangulation =
      VectorAlongTriangulationWithApproximation<VectorEAntic, VectorArb>;

 private:
  class Implementation;
  spimpl::impl_ptr<Implementation> impl;
};
}  // namespace flatsurf

#endif
