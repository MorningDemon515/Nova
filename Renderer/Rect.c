#include "Renderer.h"

#include <glad/glad.h>

Rect* R_CreateRect(Renderer* r, Vector rect, Vector color)
{
    /*
    rect.x -> x
    rect.y -> y
    rect.z -> w
    rect.w -> h
    */

    Rect* r_ = (Rect*)malloc(sizeof(Rect));

    float vertices[] = {
        rect.z / 2.0f,    rect.w / 2.0f,           0.0f,
        rect.z / 2.0f ,     -rect.w / 2.0f,             0.0f,
        -rect.z / 2.0f ,     -rect.w / 2.0f,             0.0f,
        -rect.z / 2.0f ,       rect.w / 2.0f,           0.0f
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    r_->shader = CreateShader("Shaders/rect_v.txt", "Shaders/rect_f.txt");
    UseShader(r_->shader);
    SetShaderVec3(r_->shader, "Color", color);

    SetShaderMatrix(r_->shader, "tsl", Translation(Vec3(rect.x, rect.y, 0.0f)));
    SetShaderMatrix(r_->shader, "rot", MatIdentity());
    SetShaderMatrix(r_->shader, "proj", MatIdentity());
    SetShaderMatrix(r_->shader, "scale", MatIdentity());

    glGenVertexArrays(1, &r_->VAO);
    glGenBuffers(1, &r_->VBO);
    glGenBuffers(1, &r_->EBO);

    glBindVertexArray(r_->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, r_->VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r_->EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    r_->renderer = r;

    r_->x = rect.x;
    r_->y = rect.y;
    r_->w = rect.z;
    r_->h = rect.w;

    return r_;
}

void R_DeleteRect(Rect* r)
{
    DeleteShader(r->shader);
    glDeleteVertexArrays(1, &r->VAO);
    glDeleteBuffers(1, &r->VBO);
    glDeleteBuffers(1, &r->EBO);
    free(r);
}

void R_DrawRect(Rect* r)
{
     UseShader(r->shader);
     SetShaderMatrix(r->shader, "proj", r->renderer->proj);

     glBindVertexArray(r->VAO);
     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
     glBindVertexArray(0);
}

void R_SetRectPos(Rect* r, Vector pos)
{
    UseShader(r->shader);
    SetShaderMatrix(r->shader, "tsl", Translation(pos));
}

void R_SetRectRot(Rect* r, float angle)
{
    Quaternion q = QuatFromAxisAngle(Vec3(0.0f, 0.0f, 1.0f), angle);

    UseShader(r->shader);
    SetShaderMatrix(r->shader, "rot", QuatToMat(q.data));
}

void R_SetRectSize(Rect* r, float s)
{
     UseShader(r->shader);
    SetShaderMatrix(r->shader, "scale", Scale(Vec3(s, s, s)));
}
