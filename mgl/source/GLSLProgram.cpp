#include <mgl/GLSLProgram.hpp>

// GL includes
#include <glm/gtc/type_ptr.hpp>

// STL includes
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>

// C includes
#include <cassert>

namespace
{
	// Tries to read the binary contents into a vector of chars.
	bool readFileContents(const std::string& filename, std::vector<char>& buffer)
	{
		// Try to open a file stream
		std::ifstream stream{filename, std::ios_base::in | std::ios_base::binary};
		if (!stream) return false;

		// Get the size of the file
		stream.seekg(0, std::ios_base::end);
		auto size(stream.tellg());

		// If file size greater than 0, read it in.
		if (size > 0)
		{
			stream.seekg(0, std::ios_base::beg);
			buffer.resize(static_cast<std::size_t>(size));
			stream.read(&buffer[0], size);
		}

		// Append null terminator
		buffer.emplace_back('\0');

		stream.close();
		return true;
	}

	GLenum shaderTypeToGlType(mgl::ShaderType type) noexcept
	{
		switch (type)
		{
			case mgl::ShaderType::Vertex: return GL_VERTEX_SHADER;
			case mgl::ShaderType::TessControl: return GL_TESS_CONTROL_SHADER;
			case mgl::ShaderType::TessEvaluation: return GL_TESS_EVALUATION_SHADER;
			case mgl::ShaderType::Geometry: return GL_GEOMETRY_SHADER;
			case mgl::ShaderType::Fragment: return GL_FRAGMENT_SHADER;
			default: return 0;
		}
	}
}

namespace mgl
{
	GLSLProgram::GLSLProgram()
		: m_Handle{glCreateProgram()}
	{ 
		for (auto i(0u); i < numShaders; i++) m_ShaderHandles[i] = 0;
	}

	GLSLProgram::~GLSLProgram()
	{
		release();
	}

	GLuint GLSLProgram::handle() const noexcept
	{
		return m_Handle;
	}

	bool GLSLProgram::isInvalidHandle() const noexcept
	{
		return m_Handle == 0;
	}

	bool GLSLProgram::registerUniform(const std::string& name) noexcept
	{
		if (m_Handle == 0) return false;
		m_UniformMap[name] = glGetUniformLocation(m_Handle, name.c_str());
		return true;
	}

	GLuint GLSLProgram::getUniformLocation(const std::string& name) const noexcept
	{
		const auto iter(m_UniformMap.find(name));
		if (iter == m_UniformMap.end()) return 0;
		return iter->second;
	}

	bool GLSLProgram::compileShaderFromFile(const std::string& filename, ShaderType type)
	{		
		if (isInvalidHandle() || isLinked())
		{
			std::cerr << "GLSLProgram::compileShaderFromFile() -> Invalid program state,"
				<< " already linked or invalid handle." << std::endl;
			return false;
		}

		std::vector<char> buffer;
		if (!readFileContents(filename, buffer))
		{
			std::cout << "GLSLProgram::compileShaderFromFile() -> Failed to read file contents:\n"
				<< filename << std::endl;
			return false;
		}

		return compileShader(&buffer[0], type);
	}

	bool GLSLProgram::compileShaderFromSource(const std::string& source, ShaderType type)
	{
		if (isInvalidHandle() || isLinked())
		{
			std::cerr << "GLSLProgram::compileShaderFromSource() -> Invalid program state,"
				<< " already linked or invalid handle." << std::endl;
			return false;
		}

		return compileShader(source.c_str(), type);
	}

	bool GLSLProgram::link()
	{
		if (isInvalidHandle())
		{
			std::cerr << "GLSLProgram::link() -> invalid handle" << std::endl;
			return false;
		}
		if (isLinked()) return true;

		auto loopShaders([this](bool attach, bool del = false)
		{
			for (auto i(0u); i < numShaders; i++)
			{
				auto shader(m_ShaderHandles[i]);
				if (shader == 0) continue;

				if (attach) glAttachShader(m_Handle, shader);
				else glDetachShader(m_Handle, shader);

				if (!attach && del) glDeleteShader(shader);
			}
		});

		// Attach shaders
		loopShaders(true);

		// Link program
		glLinkProgram(m_Handle);

		// Check for link errors.
		GLint isLinked;
		glGetProgramiv(m_Handle, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			std::string errorMsg{"GLSLProgram::link() -> Failed to link program:\n"};

			// Get info log length
			GLint infoLogLength;
			glGetProgramiv(m_Handle, GL_INFO_LOG_LENGTH, &infoLogLength);
			if (infoLogLength > 0)
			{
				auto* infoLog(new char[infoLogLength]);
				glGetProgramInfoLog(m_Handle, infoLogLength, nullptr, infoLog);
				errorMsg.append(infoLog);
				delete[] infoLog;
			}

			std::cerr << errorMsg << std::endl;
			loopShaders(false);	// detach shaders but don't delete shaders (reuse)!
			return false;
		}

		// Program linked successfully, shaders can be deleted to prevent leaks.
		loopShaders(false, true);
		m_IsLinked = true;
		return true;
	}

	bool GLSLProgram::isLinked() const noexcept
	{
		return m_IsLinked;
	}

	void GLSLProgram::bind()
	{
		if (isInvalidHandle() || !isLinked()) return;
		glUseProgram(m_Handle);
	}

	void GLSLProgram::unbind()
	{
		if (isInvalidHandle() || !isLinked()) return;
		glUseProgram(0);
	}

	bool GLSLProgram::compileShader(const char* source, ShaderType type)
	{
		// Create shader
		auto glShaderType(shaderTypeToGlType(type));
		assert(glShaderType != 0);

		auto shader(glCreateShader(glShaderType));
		if (shader == 0)
		{
			std::cerr << "GLSLProgram::compileShader() -> glCreateShader failed";
			return false;
		}

		// Compile shader code
		glShaderSource(shader, 1, static_cast<const GLchar**>(&source), nullptr);
		glCompileShader(shader);

		// Check for compilation errors
		GLint isCompiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			std::string errorMsg{"GLSLProgam::compileShader() -> failed to compile shader:\n"};

			// Get compilation error message
			GLint infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
			
			if (infoLogLength > 0)
			{
				auto* infoLog(new char[infoLogLength]);
				glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog);
				errorMsg.append(infoLog);
				delete[] infoLog;
			}

			std::cerr << errorMsg << std::endl;
			glDeleteShader(shader); // prevent leaking shaders
			return false;
		}

		// Register shader, override if shader type already present.
		auto shaderTypeIdx(static_cast<unsigned int>(type));
		if (m_ShaderHandles[shaderTypeIdx] != 0)
			glDeleteShader(m_ShaderHandles[shaderTypeIdx]);
		m_ShaderHandles[shaderTypeIdx] = shader;
		return true;
	}

	void GLSLProgram::release()
	{
		if (isInvalidHandle()) return;
		glDeleteProgram(m_Handle);
		m_Handle = 0;
	}

	void GLSLProgram::setUniform(const std::string& name, glm::mat2 val)
	{
		auto loc(getUniformLocation(name));
		if (loc > 0) glUniformMatrix2fv(loc, 1, GL_FALSE, glm::value_ptr(val));
	}

	void GLSLProgram::setUniform(const std::string& name, glm::mat3 val)
	{
		auto loc(getUniformLocation(name));
		if (loc > 0) glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(val));
	}

	void GLSLProgram::setUniform(const std::string& name, glm::mat4 val)
	{
		auto loc(getUniformLocation(name));
		if (loc > 0) glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(val));
	}

	void GLSLProgram::setUniform(const std::string& name, float val)
	{
		auto loc(getUniformLocation(name));
		if (loc > 0) glUniform1f(loc, val);
	}
}