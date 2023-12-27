#pragma once

#include "Monstera/Renderer/OrthographicCamera.h"
#include "Monstera/Core/Timestep.h"

#include "Monstera/Events/ApplicationEvent.h"
#include "Monstera/Events/MouseEvent.h"


namespace Monstera {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectratio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		void SetZoomLevel(float level) { m_ZoomLevel = level; }
		float getZoomLevel() const { return m_ZoomLevel; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;

		OrthographicCamera m_Camera;
		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;

		// might need to adjust translation speed based on zoom level
		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraRotationSpeed = 180.0f; 

	};
}