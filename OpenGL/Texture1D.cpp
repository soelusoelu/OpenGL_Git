#include "Texture1D.h"

Texture1D::Texture1D(const TextureDesc& desc, const void* data) :
    Texture(desc) {
    initialize(data);
}

void Texture1D::texImage(const void* data, unsigned mipLevel, unsigned index) {
    glTexImage1D(
        target(index),
        mipLevel,
        pixel().internalFormat,
        mipSize(desc().width, mipLevel),
        0,
        pixel().format, pixel().type, data
    );
}

void Texture1D::texSubImage(const void* data, unsigned mipLevel, unsigned index) {
    glTexSubImage1D(
        target(index),
        mipLevel,
        0,
        mipSize(desc().width, mipLevel),
        pixel().format, pixel().type, data
    );
}

void Texture1D::framebufferTexture(GLuint drawBuffer, unsigned index) {
    (void)index;
    glFramebufferTexture1DEXT(
        GL_FRAMEBUFFER_EXT,
        GL_COLOR_ATTACHMENT0_EXT + drawBuffer,
        GL_TEXTURE_1D,
        texture(),
        0
    );
}
