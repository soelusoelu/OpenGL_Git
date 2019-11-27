#include "Texture3D.h"

Texture3D::Texture3D(const TextureDesc& desc, const void* data) :
    Texture(desc) {
    initialize(data);
}

void Texture3D::texImage(const void* data, unsigned mipLevel, unsigned index) {
    glTexImage3D(
        target(index),
        mipLevel,
        pixel().internalFormat,
        mipSize(desc().width, mipLevel),
        mipSize(desc().height, mipLevel),
        mipSize(desc().depth, mipLevel),
        0,
        pixel().format, pixel().type, data
    );
}

void Texture3D::texSubImage(const void* data, unsigned mipLevel, unsigned index) {
    glTexSubImage3D(
        target(index),
        mipLevel,
        0, 0, 0,
        mipSize(desc().width, mipLevel),
        mipSize(desc().height, mipLevel),
        mipSize(desc().depth, mipLevel),
        pixel().format, pixel().type, data
    );
}
