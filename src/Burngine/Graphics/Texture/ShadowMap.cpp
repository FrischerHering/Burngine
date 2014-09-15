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

#include <Burngine/Graphics/Texture/ShadowMap.hpp>
#include <Burngine/System/Error.hpp>
#include <Burngine/Graphics/Scene/SceneNode.hpp>

#define DEFAULT_RESOLUTION 512

namespace burn {

	bool ShadowMap::create(const Vector2ui& resolution) {

		m_shadowMap.loadFromData(resolution, Texture::RG16F, Texture::DATA_RG,
		NULL);

		if(!m_framebuffer.create(resolution, true, m_shadowMap)){
			burnWarn("Cannot create shadow map framebuffer.");
			return false;
		}

		return true;
	}

	void ShadowMap::render(	const std::vector<SceneNode*>& sceneNodes,
							const Matrix4f& view,
							const Matrix4f& projection,
							bool useRawZ) {

		if(!m_shadowMap.isLoaded()){
			if(!create(Vector2ui(DEFAULT_RESOLUTION, DEFAULT_RESOLUTION))){
				burnErr("Could not create shadow map with default resolutions!");
			}
		}

		for(size_t i = 0; i < sceneNodes.size(); ++i)
			sceneNodes[i]->renderShadowMap(view, projection, useRawZ);

	}

} /* namespace burn */
