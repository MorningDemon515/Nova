#ifndef SHADER_H
#define SHADER_H

#include "../Math/Math.h"

struct Shader
{
    char* buffer;
    unsigned int program;
};

typedef struct Shader Shader;

Shader* CreateShader(const char* vS, const char *fS);
void DeleteShader(Shader* s);

void UseShader(Shader* s);

void SetShaderInt(Shader* s, const char* name, int value);
void SetShaderFloat(Shader* s, const char* name, float value);

void SetShaderVec2(Shader* s, const char* name, Vector value);
void SetShaderVec3(Shader* s, const char* name, Vector value);
void SetShaderVec4(Shader* s, const char* name, Vector value);

void SetShaderMatrix(Shader* s, const char* name, Matrix value);

#endif // SHADER_H
