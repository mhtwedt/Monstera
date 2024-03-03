#include "mdpch.h"
#include "Entity.h"

namespace Monstera
{

	Entity::Entity(entt::entity handle, Scene* scene)
		:m_EntityHandle(handle), m_Scene(scene)
	{
	}

}