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
