// Assignment01.cpp 
//

#include "stdafx.h"
//#include "GL/gl.h"
#include "GL/gl3w.h"	// OpenGL Version >= 3.
#include "glm/gtc/matrix_transform.hpp"
#include "Assignment01.h"


Assignment01::Assignment01(COGL4CoreAPI *Api) : RenderPlugin(Api) {
    this->myName = "Assignment01";
    this->myDescription = "Show HSV chromatic circle"; // Description Assignment 01
    draw = true;
	fLog = stderr;
}

Assignment01::~Assignment01() {

}

bool Assignment01::Activate(void) {
    draw.Set(this,"draw", nullptr);
    draw.Register(nullptr);
    
    this->AddManipulator("trafo", &this->trafo);

	// quad representation by four vertices (using GL_TRIANGLE_STRIP |\|)
	const static float quadVerts[8] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	// generate vertex array object
	glGenVertexArrays(1, &va_square);
	// generate vertex buffer object
	glGenBuffers(1, &vbo_square);
	// bind vertex array object
	glBindVertexArray(va_square);
	// bind vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, vbo_square);
	// use vertex attribute array index 0
	glEnableVertexAttribArray(0);
	// copy vertex data to vertex buffer object
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* 4 * 2, quadVerts, GL_STATIC_DRAW);
	// define type of vertex data
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// get plugin path
	std::string pluginPath = this->GetCurrentPluginPath();
	fprintf(fLog,"%s\n",pluginPath.c_str());

	// vertex shader
	vShaderName = pluginPath + std::string("/resources/verta1.c");

	// fragment shader for RGB square (as shown in the slides of the tutorial)
	//fShaderName = pluginPath + std::string("/resources/fraga1_rgb.c");

	// ASSIGNMENT 01: Uncomment fShaderName for your fragment shader implementing hsv to rgb conversion (comment previous fShaderName)
	fShaderName = pluginPath + std::string("/resources/fraga1_hsv.c");

	fprintf(fLog,"%s\n",vShaderName.c_str());
	fprintf(fLog,"%s\n",fShaderName.c_str());

	if (!shader.CreateProgramFromFile(vShaderName.c_str(),fShaderName.c_str(),fLog)) {
		fprintf(fLog,"Cannot create shader!\n");
		shader.PrintInfo(fLog);
	}

    return true;
}

bool Assignment01::Deactivate(void) {

	glDeleteBuffers(1, &vbo_square);
	glDeleteVertexArrays(1, &va_square);
	shader.RemoveAllShaders();

    return true;
}

bool Assignment01::Init(void) {
	if (gl3wInit()) {
		fprintf(stderr, "Error: Failed to initialize gl3w.\n");
		return false;
	}

    return true;
}

bool Assignment01::Render(void) {
    glClearColor( 0.0, 0.0, 0.0, 1.0 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    //glMatrixMode(GL_MODELVIEW);
    //glLoadMatrixf(glm::value_ptr(this->trafo));
	glm::mat4 pvMatrix = glm::ortho(-0.f, 1.f, -0.f, 1.f);
    if (this->draw) {
		shader.Bind();
		glUniformMatrix4fv(shader.GetUniformLocation("pvm"), 1, GL_FALSE, glm::value_ptr(pvMatrix)); // using OGL4Core
		glBindVertexArray(va_square);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
		shader.Release();
    }

    return false;
}

