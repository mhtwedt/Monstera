#include "mdpch.h"

#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace Monstera
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Monstera::ShaderDataType::Float:		return GL_FLOAT;
			case Monstera::ShaderDataType::Float2:		return GL_FLOAT;
			case Monstera::ShaderDataType::Float3:		return GL_FLOAT;
			case Monstera::ShaderDataType::Float4:		return GL_FLOAT;
			case Monstera::ShaderDataType::Mat3:		return GL_FLOAT;
			case Monstera::ShaderDataType::Mat4:		return GL_FLOAT;
			case Monstera::ShaderDataType::Int:			return GL_INT;
			case Monstera::ShaderDataType::Int2:		return GL_INT;
			case Monstera::ShaderDataType::Int3:		return GL_INT;
			case Monstera::ShaderDataType::Int4:		return GL_INT;
			case Monstera::ShaderDataType::Bool:		return GL_BOOL;
		}

		MD_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;

	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		MD_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		MD_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		MD_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		MD_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		MD_PROFILE_FUNCTION();

		MD_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		MD_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}