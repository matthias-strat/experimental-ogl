#pragma once

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/glm.hpp>
#include <GL/glew.h>

#include <map>
#include <string>

namespace mgl
{
	// Specifies the type of a shader.
	enum class ShaderType
	{
		Vertex,
		TessControl,
		TessEvaluation,
		Geometry,
		Fragment,
		NumShaders
	};

	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();
		GLSLProgram(const GLSLProgram&) = delete;
		GLSLProgram& operator=(const GLSLProgram&) = delete;

		// Returns the OpenGL object handle.
		GLuint handle() const noexcept;
		// Returns a value whether the OpenGL object handle is invalid.
		bool isInvalidHandle() const noexcept;

		// Compiles a shader from a physical file and saves its handle for linking.
		bool compileShaderFromFile(const std::string& filename, ShaderType type);
		// Compiles a shader from a string in memory and saves its handle for linking.
		bool compileShaderFromSource(const std::string& source, ShaderType type);		

		// Links all shaders added via compileShaderFrom* together.
		bool link();

		// Get a bool indicating whether the program is linked.
		bool isLinked() const noexcept;

		void bind();
		void unbind();

		bool registerUniform(const std::string& name) noexcept;
		GLuint getUniformLocation(const std::string& name) const noexcept;

		void setUniform(const std::string& name, glm::mat2 val);
		void setUniform(const std::string& name, glm::mat3 val);
		void setUniform(const std::string& name, glm::mat4 val);
		void setUniform(const std::string& name, float value);

	private:
		static constexpr unsigned int numShaders{static_cast<unsigned int>(ShaderType::NumShaders)};

		bool compileShader(const char* source, ShaderType shader);
		void release();

		GLuint m_Handle;
		std::map<std::string, GLuint> m_UniformMap;
		GLuint m_ShaderHandles[numShaders];
		bool m_IsLinked{false};
	};
}