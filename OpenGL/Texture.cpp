#include "Texture.h"

Texture::Texture(const TextureDesc& desc) :
    mDesc(desc),
    mType(toType(mDesc.type)),
    mTexture(0),
    mDepthTexture(0),
    mStencilTexture(0) {
    //テクスチャを作成
    glGenTextures(1, &mTexture);
    //デプスバッファで使用するか
    if (pixel().depthFormat) {
        mDepthTexture = mTexture;
        mType.target = GL_TEXTURE_2D;
        mType.arrayTarget = GL_TEXTURE_2D;
        mType.arraySize = 1;
    }
    //ステンシルバッファで使用するか
    if (pixel().stencilFormat) {
        mStencilTexture = mTexture;
        mType.target = GL_TEXTURE_2D;
        mType.arrayTarget = GL_TEXTURE_2D;
        mType.arraySize = 1;
    }
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
    const GLubyte* base = reinterpret_cast<const GLubyte*>(data);
    for (unsigned i = 0; i < arraySize(); ++i) {
        for (unsigned mip = 0; mip < desc().mipLevels; ++mip) {
            texSubImage(base, mip, i);
            base += imageSize(mip);
        }
    }
    glBindTexture(target(), 0);
}

void Texture::getData(void* data) {
    glBindTexture(target(), mTexture);
    GLubyte* base = reinterpret_cast<GLubyte*>(data);
    for (unsigned i = 0; i < arraySize(); ++i) {
        for (unsigned mip = 0; mip < desc().mipLevels; ++mip) {
            getTexImage(base, mip, i);
            base += imageSize(mip);
        }
    }
    glBindTexture(target(), 0);
}

unsigned int Texture::size() const {
    unsigned size = 0;
    for (unsigned mip = 0; mip < mDesc.mipLevels; ++mip) {
        size += imageSize(mip);
    }
    return size * arraySize();
}

GLenum Texture::target() const {
    return mType.target;
}

GLenum Texture::target(unsigned index) const {
    return mType.arrayTarget + index;
}

GLuint Texture::texture() const {
    return mTexture;
}

void Texture::attachDepthStencil() {
    //デプスバッファ用のテクスチャを設定
    glFramebufferTexture2DEXT(
        GL_FRAMEBUFFER_EXT,
        GL_DEPTH_ATTACHMENT_EXT,
        GL_TEXTURE_2D,
        mDepthTexture,
        0
    );
    //ステンシルバッファ用のテクスチャを設定
    glFramebufferTexture2DEXT(
        GL_FRAMEBUFFER_EXT,
        GL_STENCIL_ATTACHMENT_EXT,
        GL_TEXTURE_2D,
        mStencilTexture,
        0
    );
}

void Texture::attachFramebuffer(GLuint drawBuffer, unsigned index) {
    framebufferTexture(drawBuffer, index);
}

void Texture::generateMipmap() {
    glEnable(target());
    glBindTexture(target(), mTexture);
    glGenerateMipmapEXT(target());
    glBindTexture(target(), 0);
    glDisable(target());
}

void Texture::initialize(const void* data) {
    glBindTexture(target(), mTexture);
    //テクスチャイメージの設定
    const GLubyte* base = reinterpret_cast<const GLubyte*>(data);
    for (unsigned i = 0; i < arraySize(); ++i) {
        for (unsigned mip = 0; mip < desc().mipLevels; ++mip) {
            texImage(base, mip, i);
            if (data) {
                base += imageSize(mip);
            }
        }
    }
    //デフォルトのテクスチャフィルタの設定
    glTexParameteri(target(), GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(target(), GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBindTexture(target(), 0);
}

const Texture::Pixel& Texture::pixel() const {
    static const Pixel pixelFormat[] = {
        { GL_INTENSITY8,                    GL_LUMINANCE,         GL_UNSIGNED_BYTE,                    sizeof(GLubyte) * 1,     false, false, false }, //TEXTURE_FORMAT_I8         = 0
        { GL_LUMINANCE8_ALPHA8,             GL_LUMINANCE_ALPHA,   GL_UNSIGNED_BYTE,                    sizeof(GLubyte) * 2,     false, false, false }, //TEXTURE_FORMAT_IA8        = 1
        { GL_RGBA8,                         GL_RGBA,              GL_UNSIGNED_BYTE,                    sizeof(GLubyte) * 4,     false, false, false }, //TEXTURE_FORMAT_RGBA8      = 2
        { GL_INTENSITY16,                   GL_LUMINANCE,         GL_UNSIGNED_SHORT,                   sizeof(GLushort) * 1,    false, false, false }, //TEXTURE_FORMAT_I16        = 3
        { GL_LUMINANCE16_ALPHA16,           GL_LUMINANCE_ALPHA,   GL_UNSIGNED_SHORT,                   sizeof(GLushort) * 2,    false, false, false }, //TEXTURE_FORMAT_IA16       = 4
        { GL_RGBA16,                        GL_RGBA,              GL_UNSIGNED_SHORT,                   sizeof(GLushort) * 4,    false, false, false }, //TEXTURE_FORMAT_RGBA16     = 5
        { GL_INTENSITY16F_ARB,              GL_LUMINANCE,         GL_HALF_FLOAT_ARB,                   sizeof(GLfloat) / 2 * 1, false, false, false }, //TEXTURE_FORMAT_I16F       = 6
        { GL_LUMINANCE_ALPHA16F_ARB,        GL_LUMINANCE_ALPHA,   GL_HALF_FLOAT_ARB,                   sizeof(GLfloat) / 2 * 2, false, false, false }, //TEXTURE_FORMAT_IA16F      = 7
        { GL_RGBA16F_ARB,                   GL_RGBA,              GL_HALF_FLOAT_ARB,                   sizeof(GLfloat) / 2 * 4, false, false, false }, //TEXTURE_FORMAT_RGBA16F    = 8
        { GL_INTENSITY32F_ARB,              GL_LUMINANCE,         GL_FLOAT,                            sizeof(GLfloat) * 1,     false, false, false }, //TEXTURE_FORMAT_I32F       = 9
        { GL_LUMINANCE_ALPHA32F_ARB,        GL_LUMINANCE_ALPHA,   GL_FLOAT,                            sizeof(GLfloat) * 2,     false, false, false }, //TEXTURE_FORMAT_IA32F      = 10
        { GL_RGB32F_ARB,                    GL_RGB,               GL_FLOAT,                            sizeof(GLfloat) * 3,     false, false, false }, //TEXTURE_FORMAT_RGB32F     = 11
        { GL_RGBA32F_ARB,                   GL_RGBA,              GL_FLOAT,                            sizeof(GLfloat) * 4,     false, false, false }, //TEXTURE_FORMAT_RGBA32F    = 12
        { GL_R11F_G11F_B10F_EXT,            GL_RGB,               GL_UNSIGNED_INT_10F_11F_11F_REV_EXT, sizeof(GLuint),          false, false, false }, //TEXTURE_FORMAT_R11G11B10F = 13
        { GL_COMPRESSED_RGB_S3TC_DXT1_EXT,  GL_RGB,               GL_UNSIGNED_BYTE,                    sizeof(GLubyte) * 8,     true,  false, false }, //TEXTURE_FORMAT_DXT1       = 14
        { GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, GL_RGBA,              GL_UNSIGNED_BYTE,                    sizeof(GLubyte) * 16,    true,  false, false }, //TEXTURE_FORMAT_DXT3       = 15
        { GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, GL_RGBA,              GL_UNSIGNED_BYTE,                    sizeof(GLubyte) * 16,    true,  false, false }, //TEXTURE_FORMAT_DXT5       = 16
        { GL_DEPTH_COMPONENT16,             GL_DEPTH_COMPONENT,   GL_UNSIGNED_SHORT,                   sizeof(GLushort) * 1,    false, true,  false }, //TEXTURE_FORMAT_D16        = 17
        { GL_DEPTH_COMPONENT32,             GL_DEPTH_COMPONENT,   GL_FLOAT,                            sizeof(GLfloat) * 1,     false, true,  false }, //TEXTURE_FORMAT_D32F       = 18
        { GL_DEPTH24_STENCIL8_EXT,          GL_DEPTH_STENCIL_EXT, GL_UNSIGNED_INT_24_8_EXT,            sizeof(GLubyte) * 4,     false, true,  true }   //TEXTURE_FORMAT_D24S8      = 19
    };
    return pixelFormat[static_cast<int>(mDesc.format)];
}

unsigned Texture::imageSize(unsigned mipLevel) const {
    //ミップマップレベルに合わせたサイズを求める
    unsigned w = mipSize(desc().width, mipLevel);
    unsigned h = mipSize(desc().height, mipLevel);
    unsigned d = mipSize(desc().depth, mipLevel);
    //DXTフォーマットか？
    if (pixel().complessedFormat) {
        //DXTのブロックサイズに変更
        w = (w + 3) / 4;
        h = (h + 3) / 4;
    }
    //イメージサイズの計算
    return w * h * d * pixel().size;
}

unsigned Texture::mipSize(unsigned size, unsigned mipLevel) {
    unsigned mipsize = (size >> mipLevel);
    return (mipsize <= 0) ? 1 : mipsize;
}

const Texture::Type& Texture::toType(TextureType type) {
    static const Type types[] = {
        { GL_TEXTURE_1D,       GL_TEXTURE_1D,                  1 }, //TEXTURE_TYPE_1D = 0
        { GL_TEXTURE_2D,       GL_TEXTURE_2D,                  1 }, //TEXTURE_TYPE_2D = 1
        { GL_TEXTURE_3D,       GL_TEXTURE_3D,                  1 }, //TEXTURE_TYPE_3D = 2
        { GL_TEXTURE_CUBE_MAP, GL_TEXTURE_CUBE_MAP_POSITIVE_X, 6 }  //TEXTURE_TYPE_CUBE = 3
    };
    return types[static_cast<int>(type)];
}

unsigned Texture::arraySize() const {
    return mType.arraySize;
}

void Texture::getTexImage(void* data, unsigned mipLevel, unsigned index) const {
    if (pixel().complessedFormat) {
        //圧縮イメージ
        glGetCompressedTexImageARB(
            target(index),
            mipLevel,
            data
        );
    } else {
        //無圧縮イメージ
        glGetTexImage(
            target(index),
            mipLevel,
            pixel().format, pixel().type, data
        );
    }
}
