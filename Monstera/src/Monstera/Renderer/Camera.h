#pragma once

#include <glm/glm.hpp>

namespace Monstera {

	class Camera
	{
	public:
		Camera() = default;
		Camera(const glm:: mat4& projection)
			: m_Projection(projection) {}
		virtual ~Camera() = default;

		const glm::mat4& GetProjection() const { return m_Projection; }

		// TODO: Set Projection

	protected:
		glm::mat4 m_Projection = glm::mat4(1.0f);

	};

}