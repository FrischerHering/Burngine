//////////////////////////////////////////////////////////////////////////////
//
// Burngine is distributed under the GNU LGPL v3 License
// ====================================================
//
//    Copyright (C) 2014 Dominik David (frischer-hering@gmx.de)
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU Lesser General Public
//    License as published by the Free Software Foundation;
//    version 3.0 of the License
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
//    USA
//
//////////////////////////////////////////////////////////////////////////////

#ifndef DIRECTIONALLIGHT_HPP_
#define DIRECTIONALLIGHT_HPP_

#include <Burngine/Export.hpp>
#include <Burngine/Graphics/Scene/PointLight.hpp>

namespace burn {

	/**
	 * @brief Light source without a position but only a direction.
	 * Illuminates the whole scene.
	 * -> Sun
	 */
	class BURNGINE_API_EXPORT DirectionalLight : public PointLight {
	public:

		/**
		 * @brief Get the light's direction. Without applied rotation
		 * the direction is straight downwards (0, -1, 0)
		 */
		Vector3f getDirection() const;

	private:

	};

} /* namespace burn */

#endif /* DIRECTIONALLIGHT_HPP_ */
