#ifndef TEXTURE_H
#define TEXTURE_H

struct Texture
{
    const char* path;
    unsigned int texture;
};

typedef struct Texture Texture;

Texture* CreateTex(const char* p);
void DeleteTex(Texture* t);

void SetTex(Texture* t, int unit);

#endif // TEXTURE_H
