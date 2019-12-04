#include "Texture2D.h"

Texture2D::Texture2D(const TextureDesc& desc, const void* data) :
    Texture(desc) {
    initialize(data);
}

void Texture2D::texImage(const void* data, unsigned mipLevel, unsigned index) {
    if (pixel().complessedFormat) {
        //���k�C���[�W
        glCompressedTexImage2DARB(
            target(index),
            mipLevel,
            pixel().internalFormat,
            mipSize(desc().width, mipLevel),
            mipSize(desc().height, mipLevel),
            0,
            imageSize(mipLevel),
            data
        );
    } else {
        //�����k�C���[�W
        glTexImage2D(
            target(index),
            mipLevel,
            pixel().internalFormat,
            mipSize(desc().width, mipLevel),
            mipSize(desc().height, mipLevel),
            0,
            pixel().format, pixel().type, data
        );
    }
}

void Texture2D::texSubImage(const void* data, unsigned mipLevel, unsigned index) {
    if (pixel().complessedFormat) {
        //���k�C���[�W
        glCompressedTexSubImage2DARB(
            target(index),
            mipLevel,
            0, 0,
            mipSize(desc().width, mipLevel),
            mipSize(desc().height, mipLevel),
            pixel().format,
            imageSize(mipLevel),
            data
        );
    } else {
        //�����k�C���[�W
        glTexSubImage2D(
            target(index),
            mipLevel,
            0, 0,
            mipSize(desc().width, mipLevel),
            mipSize(desc().height, mipLevel),
            pixel().format, pixel().type, data
        );
    }
}

void Texture2D::framebufferTexture(GLuint drawBuffer, unsigned index) {
    glFramebufferTexture2DEXT(
        GL_FRAMEBUFFER_EXT,
        GL_COLOR_ATTACHMENT0_EXT + drawBuffer,
        target(index),
        texture(),
        0
    );
}
