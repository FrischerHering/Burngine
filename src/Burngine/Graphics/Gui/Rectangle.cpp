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

#include <Burngine/Graphics/Gui/Rectangle.hpp>
#include <Burngine/Graphics/Shader/BurnShaders.hpp>
#include <Burngine/Graphics/Shader/Shader.hpp>

namespace burn {

	Rectangle::Rectangle() {

		ensureContext();

		// Setup VBO
		updateVbo();

		// Setup VAO
		bindVao();
		m_vbo.bind();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		unbindVao();

	}

	void Rectangle::setDimensions(const Vector2f& dimensions) {
		m_dimensions = dimensions;
		updateVbo();
	}

	const Vector2f& Rectangle::getDimensions() const {
		return m_dimensions;
	}

	void Rectangle::updateVbo() {

		// Create data array
		Vector3f vboData[] = {
		Vector3f(0.f),
		Vector3f(m_dimensions.x, 0.f, 0.f),
		Vector3f(0.f, m_dimensions.y, 0.f),
		Vector3f(m_dimensions.x, m_dimensions.y, 0.f) };

		// Add data to VBO
		m_vbo.reset();
		m_vbo.addData(&vboData[0], sizeof(vboData));

		// Upload data
		bindVao();
		m_vbo.bind();
		unbindVao();

	}

	void Rectangle::render(const Matrix4f& projection) const {

		const Shader& shader = BurnShaders::getShader(BurnShaders::COLOR);
		shader.setUniform("gProjectionMatrix", projection);

		shader.activate();
		bindVao();
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		unbindVao();

	}

} /* namespace burn */
