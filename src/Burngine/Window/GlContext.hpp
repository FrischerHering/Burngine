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

#ifndef GLCONTEXT_HPP_
#define GLCONTEXT_HPP_

#include <Burngine/Export.hpp>
#include <Burngine/System/NonCopyable.hpp>
#include <Burngine/Window/Window.hpp>

namespace burn {
	namespace priv {

		class GlContext : public NonCopyable {
		public:

			/**
			 * @brief Create a context without attaching a window
			 */
			static GlContext* create();

			/**
			 * @brief Create a context with a given window
			 */
			static GlContext* create(const Window* window);

			/**
			 * @brief Must be called before context creation.
			 * Creates shared context, thus we cannot lose OpenGL
			 * objects.
			 */
			static void globalInit();

			/**
			 * @brief Destroys shared context and possibly all allocated
			 * OpenGL objects if that was the last context
			 */
			static void globalCleanup();

			/**
			 * @brief Ensure that a valid context is active
			 */
			static void ensureContext();

		public:

			/**
			 * @brief Calls the destructor of the context implementation
			 * for proper cleanup
			 */
			virtual ~GlContext();

			/**
			 * @brief Swaps the buffers and thus displays the rendered
			 * content
			 */
			virtual void swapBuffers() = 0;

			/**
			 * @brief Active this context or deactivate it.
			 * Another one will be activated to ensure a context
			 *
			 * @param active Set to true to activate and false to deactivate
			 */
			void setActive(bool active = true);

		protected:

			/**
			 * @brief Make the platform specific context current
			 */
			virtual void makeCurrent() = 0;

		};

	} /* namespace priv */
} /* namespace burn */
#endif /* GLCONTEXT_HPP_ */
