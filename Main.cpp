#include <GL/glew.h>

#include <SFML/Graphics.hpp>

#include <mgl/GLSLProgram.hpp>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>

namespace
{
	constexpr unsigned int screenWidth{800};
	constexpr unsigned int screenHeight{600};

	bool readFileContents(const std::string& filename, std::vector<char>& buffer)
	{
		std::ifstream stream{filename, std::ios_base::in | std::ios_base::binary};
		if (!stream) return false;
		
		stream.seekg(0, std::ios_base::end);
		auto size(stream.tellg());

		if (size > 0)
		{
			stream.seekg(0, std::ios_base::beg);
			buffer.resize(static_cast<std::size_t>(size));
			stream.read(&buffer[0], size);
		}
		buffer.push_back('\0');
		stream.close();
		return true;
	}
}

int main()
{
	// Configure and create output window (SFML)
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.attributeFlags = sf::ContextSettings::Core;

	sf::Window window{{screenWidth, screenHeight}, "SFML - Modern OpenGL", sf::Style::Close, settings};
	window.setVerticalSyncEnabled(true);

	// Initialize OpenGL wrangler library (GLEW)
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW." << std::endl;
		return 1;
	}

	// Configure OpenGL
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glViewport(0, 0, static_cast<GLsizei>(screenWidth), static_cast<GLsizei>(screenHeight));

	mgl::GLSLProgram program;
	if (!program.compileShaderFromFile("assets/shaders/texture.vert", mgl::ShaderType::Vertex))
		return 1;
	if (!program.compileShaderFromFile("assets/shaders/texture.frag", mgl::ShaderType::Fragment))
		return 1;
	if (!program.link())
		return 1;
	program.registerUniform("model");
	program.registerUniform("view");
	program.registerUniform("projection");

	// Vertex data
	const GLfloat vertices[] =
	{
		// Front
	    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	    // Back
	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	    // Left
	    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

	    // Right
	     0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	     0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

	    // Bottom
	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	    // Top
	    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

	// Generate and configure buffers
	GLuint vbo, ebo, vao;
	glGenBuffers(1, &vbo);
	glCreateVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	// Load texture
	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	auto image(std::make_unique<sf::Image>());
	if (!image->loadFromFile("assets/textures/bricks.jpg"))
	{
		std::cerr << "Failed to load texture" << std::endl;
		return 1;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getSize().x, image->getSize().y, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, image->getPixelsPtr());
	glGenerateMipmap(GL_TEXTURE_2D);

	image.reset(nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);

	glm::vec3 cubePositions[] = 
	{
		glm::vec3( 0.0f,  0.0f,  0.0f),
		glm::vec3( 0.0f,  0.0f,  1.5f),
		glm::vec3( 0.0f,  0.0f, -1.5f),
		glm::vec3( 0.0f,  1.5f,  0.0f),
		glm::vec3( 0.0f, -1.5f,  0.0f),
		glm::vec3( 1.5f,  0.0f,  0.0f),
		glm::vec3(-1.5f,  0.0f,  0.0f)
	};

	// Game timer
	sf::Clock clock;
	sf::Time elapsedTime{sf::Time::Zero};

	// Game loop
	while (window.isOpen())
	{
		elapsedTime = clock.getElapsedTime();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		program.bind();

		// Rotate camera around world origin over time
		glm::mat4 view;
		GLfloat radius{5.f};
		auto camX(static_cast<GLfloat>(sin(elapsedTime.asSeconds()) * radius));
		auto camZ(static_cast<GLfloat>(cos(elapsedTime.asSeconds()) * radius));
		view = glm::lookAt(glm::vec3(camX, 0.f, camZ), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));

		// Perspective projection (fov 45 degress, near plane at 0.1f, far plane at 100.f);
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.f), static_cast<float>(screenWidth) /
			static_cast<float>(screenHeight), 0.1f, 100.f);

		// Get uniform locations
		GLuint modelLoc = program.getUniformLocation("model");
		GLuint viewLoc = program.getUniformLocation("view");
		GLuint projLoc = program.getUniformLocation("projection");

		// Update uniforms
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Bind texture
		glBindTexture(GL_TEXTURE_2D, texture);

		for (auto i(0u); i < 7; i++)
		{
			// Translate the cube to its specific position
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			if (i == 0)
			{
				auto angle(elapsedTime.asSeconds() * 80.f);
				model = glm::rotate(model, glm::radians(-angle), glm::vec3(0.6f, 1.f, 0.9f));
			}

			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			// Draw the cube with specified VAO
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
		}

		window.display();
	}

	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	

	return 0;
}