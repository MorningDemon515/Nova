#include "Shader.h"
#include <glad/glad.h>

#include <stdio.h>
#include <stdlib.h>

Shader* CreateShader(const char* vS, const char *fS)
{
    Shader* s = (Shader*)malloc(sizeof(Shader));

    const char* vSrc;
    const char* fSrc;

    FILE* fp1 = fopen(vS, "rb");
    FILE* fp2 = fopen(fS, "rb");

    fseek(fp1, 0, SEEK_END);
    long size1 = ftell(fp1);
    rewind(fp1);

    fseek(fp2, 0, SEEK_END);
    long size2 = ftell(fp2);
    rewind(fp2);

    s->buffer = (char*)malloc(size1 + 1 + size2 + 1);

    fread(s->buffer, 1, size1, fp1);
    s->buffer[size1] = '\0';

    fread(s->buffer + size1 + 1, 1, size2, fp2);
    s->buffer[size1 + 1 + size2] = '\0';

    fclose(fp1);
    fclose(fp2);

    vSrc = s->buffer;
    fSrc = s->buffer + size1 + 1;
    //----------------------------------------------------------------

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vSrc, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fSrc, NULL);
    glCompileShader(fragmentShader);

    s->program = glCreateProgram();
    glAttachShader(s->program, vertexShader);
    glAttachShader(s->program, fragmentShader);
    glLinkProgram(s->program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("Vertex Shader Error! : \n %s \n", infoLog);
    }

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("Vertex Shader Error! : \n %s \n", infoLog);
    }

    return s;
}

void DeleteShader(Shader* s)
{
    free(s->buffer);
    glDeleteProgram(s->program);
    free(s);
}

void UseShader(Shader* s)
{
    glUseProgram(s->program);
}

void SetShaderInt(Shader* s, const char* name, int value)
{
    glUniform1i(glGetUniformLocation(s->program, name), value);
}

void SetShaderFloat(Shader* s, const char* name, float value)
{
    glUniform1f(glGetUniformLocation(s->program, name), value);
}

void SetShaderVec2(Shader* s, const char* name, Vector value)
{
    glUniform2f(glGetUniformLocation(s->program, name), value.x, value.y);
}

void SetShaderVec3(Shader* s, const char* name, Vector value)
{
    glUniform3f(glGetUniformLocation(s->program, name), value.x, value.y,value.z);
}

void SetShaderVec4(Shader* s, const char* name, Vector value)
{
    glUniform4f(glGetUniformLocation(s->program, name), value.x, value.y,value.z, value.w);
}

void SetShaderMatrix(Shader* s, const char* name, Matrix value)
{
    glUniformMatrix4fv(
        glGetUniformLocation(s->program, name),
        1,
        GL_FALSE,
        &value.data[0][0]);
}
