#include "RenderPlugin.h"
#include "glm/glm.hpp"

#include "GLShader.h"

// This class is exported from the dynamic library
class OGL4COREPLUGIN_API Assignment01 : public RenderPlugin {
public:
    Assignment01(COGL4CoreAPI *Api);
    ~Assignment01(void);

    virtual bool Activate(void);
    virtual bool Deactivate(void);
    virtual bool Init(void);
    virtual bool Render(void);

private:
    APIVar<Assignment01, BoolVarPolicy> draw;
    glm::mat4 trafo;

	GLuint vbo_square, va_square;
	GLShader shader;

	std::string vShaderName;
	std::string fShaderName;

	FILE* fLog;
};

extern "C" OGL4COREPLUGIN_API RenderPlugin* OGL4COREPLUGIN_CALL CreateInstance(COGL4CoreAPI *Api) {
    return new Assignment01(Api);
}
