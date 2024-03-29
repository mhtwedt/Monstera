#pragma once

#include "Scene.h"

#include "entt.hpp"


namespace Monstera {
	
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default; // Copy constructor


		template<typename T, typename... Args> // variatic template
		T& AddComponent(Args&&... args) //we are forwarding this because entt basically can handle this
		{
			MD_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!"); // don't want to assert inside entt :)
			T& component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);

			return component;
		}

		template<typename T>
		T& GetComponent()
		{
			MD_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");

			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			MD_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");

			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
		operator entt::entity() const { return m_EntityHandle; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }

		bool operator==(const Entity& other) const
		{
			return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}

	private:
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr; // should be a weak reference, so the entity doesn't have ownership over the scene
	};

}