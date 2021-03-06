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

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <Burngine/Export.hpp>
#include <Burngine/Graphics/Scene/Model.hpp>
#include <Burngine/Graphics/Scene/PointLight.hpp>
#include <Burngine/Graphics/Scene/DirectionalLight.hpp>
#include <Burngine/Graphics/Scene/SpotLight.hpp>
#include <Burngine/Graphics/Scene/Billboard.hpp>
#include <Burngine/Graphics/Scene/Skybox.hpp>
#include <vector>

namespace burn {

	/**
	 * @brief System for SceneNodes, Lights and other entities.
	 */
	class BURNGINE_API_EXPORT Scene {
	public:

		Scene();

		/**
		 * @brief Attach a SceneNode
		 */
		void attachModel(Model* sceneNode);

		/**
		 * @brief Detach a SceneNode
		 */
		void detachModel(Model* const sceneNode);

		/**
		 * @brief Get a list of all attached scene nodes
		 */
		const std::vector<Model*>& getModels() const;

		/**
		 * @brief Attach directional light
		 */
		void attachLight(DirectionalLight* light);

		/**
		 * @brief Attach spot light
		 */
		void attachLight(SpotLight* light);

		/**
		 * @brief Attach point light
		 */
		void attachLight(PointLight* light);

		/**
		 * @brief Get a list of attached directional lights
		 */
		const std::vector<DirectionalLight*>& getDirectionalLights() const;

		/**
		 * @brief Get a list of attached spot lights
		 */
		const std::vector<SpotLight*>& getSpotLights() const;

		/**
		 * @brief Get a list of attached point lights
		 */
		const std::vector<PointLight*> getPointLights() const;

		void attachBillboard(Billboard* billboard);

		const std::vector<Billboard*>& getBillboards() const;

		void attachSkybox(Skybox* skybox);

		Skybox* getSkybox() const;

	private:
		std::vector<Model*> m_models;
		std::vector<DirectionalLight*> m_directionalLights;
		std::vector<SpotLight*> m_spotLights;
		std::vector<PointLight*> m_pointLights;
		std::vector<Billboard*> m_billboards;
		Skybox* m_skybox;
	};

} /* namespace burn */

#endif /* SCENE_HPP_ */
