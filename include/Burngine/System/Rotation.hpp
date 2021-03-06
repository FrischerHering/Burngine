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

#ifndef ROTATION_HPP_
#define ROTATION_HPP_

#include <Burngine/Export.hpp>
#include <Burngine/System/Math.hpp>

namespace burn {

	class BURNGINE_API_EXPORT Rotation {
	public:

		/**
		 * @brief Default ctor: No rotation
		 */
		Rotation();

		/**
		 * @brief Create with initial quaternion
		 */
		Rotation(const Quaternion& quat);

		/**
		 * @brief Create with initial euler (in degrees!)
		 */
		Rotation(const Vector3f& eulerDegrees);

		/**
		 * @brief Get rotation as quaternion
		 */
		const Quaternion& asQuaternion() const;

		/**
		 * @brief Get rotation as matrix
		 */
		const Matrix4f& asMatrix() const;

		/**
		 * @brief Set by euler rotation in degrees
		 */
		void setByEulerDegrees(const Vector3f& euler);

		/**
		 * @brief Set by euler rotation in radians
		 */
		void setByEulerRadians(const Vector3f& euler);

		/**
		 * @brief Set by a rotation around an axis in degrees
		 */
		void setByAxisAngleDegrees(	const Vector3f& axis,
									const float& degrees);

		/**
		 * @brief Set by a rotation around an axis in radians
		 */
		void setByAxisAngleRadians(	const Vector3f& axis,
									const float& radians);

	private:

		/**
		 * @brief Updates matrix to fit quaterion
		 */
		void updateMatrix();

	private:
		Quaternion m_quaternion;    ///< Rot. represented as quaternion
		Matrix4f m_matrix;    ///< Rot. represented as Matrix
	};

	/**
	 * @brief Common accumulation of two rotations
	 */
	inline Rotation operator*(	const Rotation& left,
								const Rotation& right) {
		return Rotation(left.asQuaternion() * right.asQuaternion());
	}

} /* namespace burn */

#endif /* ROTATION_HPP_ */
