#pragma once

#include "Monstera/Renderer/Texture.h"

namespace Monstera {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t getWidth() const override { return m_Width;}
		virtual uint32_t getHeight() const { return m_Height; };

		virtual void Bind(uint32_t slot = 0) const override;
	private:
		std::string m_Path;
		
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
	};

}