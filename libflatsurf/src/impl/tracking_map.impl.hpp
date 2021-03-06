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

#ifndef LIBFLATSURF_TRACKING_MAP_IMPL_HPP
#define LIBFLATSURF_TRACKING_MAP_IMPL_HPP

#include "../../flatsurf/tracking_map.hpp"

#include "./tracking_storage.hpp"

namespace flatsurf {

template <typename K, typename V>
class ImplementationOf<TrackingMap<K, V>> : public TrackingStorage<TrackingMap<K, V>, K, V> {
  using Base = TrackingStorage<TrackingMap<K, V>, K, V>;

 public:
  using Base::Base;
};

}  // namespace flatsurf

#endif
