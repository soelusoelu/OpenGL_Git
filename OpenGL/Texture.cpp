#include "Texture.h"

Texture::Texture(const TextureDesc& desc, const void* data) :
    mDesc(desc),
    mType(toType(mDesc.type)),
    mTexture(0) {
    //テクスチャを作成
    glGenTextures(1, &mTexture);
    //イメージの初期化
    initialize(data);
}

Texture::~Texture() {
    //テクスチャの削除
    glDeleteTextures(1, &mTexture);
}

const TextureDesc& Texture::desc() const {
    return mDesc;
}

void Texture::setData(const void* data) {
    glBindTexture(target(), mTexture);
    glTexSubImage2D(
        target(),
        0,
        0, 0,
        desc().width,
        desc().height,
        pixel().format, pixel().type, data
    );
    glBindTexture(target(), 0);
}

void Texture::getData(void* data) {
    glBindTexture(target(), mTexture);
    glGetTexImage(
        target(),
        0,
        pixel().format, pixel().type, data
    );
    glBindTexture(target(), 0);
}

unsigned int Texture::size() const {
    return desc().width * desc().height * pixel().size;
}

GLenum Texture::target() const {
    return mType.target;
}

GLuint Texture::texture() const {
    return mTexture;
}

void Texture::initialize(const void* data) {
    glBindTexture(target(), mTexture);
    //テクスチャイメージの設定
    glTexImage2D(
        target(),
        0,
        pixel().internalFormat,
        desc().width,
        desc().height,
        0,
        pixel().format, pixel().type, data
    );
    //デフォルトのテクスチャフィルタの設定
    glTexParameteri(target(), GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(target(), GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBindTexture(target(), 0);
}

const Texture::Pixel& Texture::pixel() const {
    static const Pixel pixelFormat = {
        GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, sizeof(GLubyte) * 4, false, false, false
    };
    return pixelFormat;
}

const Texture::Type& Texture::toType(TextureType type) {
    static const Type types = {
        GL_TEXTURE_2D, GL_TEXTURE_2D, 1
    };
    return types;
}
