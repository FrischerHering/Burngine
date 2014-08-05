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

#include <Burngine/Window/GlContext.hpp>
#include <Burngine/Window/Window.hpp>

#if defined(BURNGINE_OS_WINDOWS)

#include <Burngine/Window/Win32/WglContext.hpp>
typedef burn::priv::WglContext GlContextType;

#endif

namespace burn {
namespace priv {

GlContext* GlContext::create() {
	return new GlContextType();
}

GlContext* GlContext::create(const Window* window){
	return window == NULL ? NULL : new GlContextType(window);
}

GlContext::~GlContext() {

}

void GlContext::clear(const Vector4f& color){
	makeCurrent();
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

} /* namespace priv */
} /* namespace burn */
