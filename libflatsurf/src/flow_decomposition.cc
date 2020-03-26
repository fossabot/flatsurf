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

#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include <boost/algorithm/string/join.hpp>
#include <boost/lexical_cast.hpp>

#include <intervalxt/dynamical_decomposition.hpp>

#include "external/rx-ranges/include/rx/ranges.hpp"

#include "../flatsurf/contour_component.hpp"
#include "../flatsurf/contour_decomposition.hpp"
#include "../flatsurf/flat_triangulation.hpp"
#include "../flatsurf/flat_triangulation_collapsed.hpp"
#include "../flatsurf/flow_connection.hpp"
#include "../flatsurf/flow_decomposition.hpp"
#include "../flatsurf/half_edge.hpp"
#include "../flatsurf/path.hpp"
#include "../flatsurf/vector.hpp"
#include "../flatsurf/vertical.hpp"

#include "impl/contour_decomposition.impl.hpp"
#include "impl/flow_component.impl.hpp"
#include "impl/flow_component_state.hpp"
#include "impl/flow_decomposition.impl.hpp"
#include "impl/flow_decomposition_state.hpp"
#include "impl/interval_exchange_transformation.impl.hpp"

#include "util/assert.ipp"

using std::ostream;

using intervalxt::DynamicalDecomposition;

namespace flatsurf {

template <typename Surface>
FlowDecomposition<Surface>::FlowDecomposition(std::unique_ptr<Surface> surface, const Vector<T>& vertical) :
  impl(spimpl::make_unique_impl<Implementation>(std::move(surface), vertical)) {
  ASSERTIONS(([&]() {
    auto paths = components() | rx::transform([](const auto& component) { return Path(component.perimeter() | rx::transform([](const auto& connection) { return connection.saddleConnection(); }) | rx::to_vector()); }) | rx::to_vector();
    ImplementationOf<ContourDecomposition<Surface>>::check(paths, Vertical(this->surface(), vertical));
  }));
}

template <typename Surface>
std::shared_ptr<const Surface> FlowDecomposition<Surface>::surface() const {
  return impl->state->contourDecomposition.collapsed()->uncollapsed();
}

template <typename Surface>
bool FlowDecomposition<Surface>::decompose(std::function<bool(const FlowComponent<Surface>&)> target, int limit) {
  bool targetReached = true;
  for (auto& component : components())
    targetReached = targetReached && component.decompose(target, limit);
  return targetReached;
}

template <typename Surface>
std::vector<FlowComponent<Surface>> FlowDecomposition<Surface>::components() const {
  std::vector<FlowComponent<Surface>> components;
  for (auto& component : impl->state->components) {
    components.push_back(ImplementationOf<FlowComponent<Surface>>::make(impl->state, &component));
  }
  return components;
}

template <typename Surface>
ImplementationOf<FlowDecomposition<Surface>>::ImplementationOf(std::unique_ptr<Surface> surface, const Vector<T>& vertical) :
  state(std::make_shared<FlowDecompositionState<Surface>>(std::move(surface), vertical)) {
  for (auto& component : state->components)
    ImplementationOf<IntervalExchangeTransformation<FlatTriangulationCollapsed<T>>>::registerDecomposition(*component.iet, state);
}

template <typename Surface>
ostream& operator<<(ostream& os, const FlowDecomposition<Surface>& self) {
  std::vector<std::string> components;
  for (auto& component : self.components())
    components.push_back(boost::lexical_cast<std::string>(component));

  return os << "FlowDecompsition(components=[" << boost::algorithm::join(components, ", ") << "])";
}

}  // namespace flatsurf

// Instantiations of templates so implementations are generated for the linker
#include "util/instantiate.ipp"

LIBFLATSURF_INSTANTIATE_MANY_WRAPPED((LIBFLATSURF_INSTANTIATE_WITH_IMPLEMENTATION), FlowDecomposition, LIBFLATSURF_FLAT_TRIANGULATION_TYPES)