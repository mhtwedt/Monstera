#pragma once

#include "Monstera/Core/Core.h"
#include "Monstera/Core/Log.h"
#include "Monstera/Scene/Scene.h"
#include "Monstera/Scene/Entity.h"

namespace Monstera {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();

	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;

	};


}