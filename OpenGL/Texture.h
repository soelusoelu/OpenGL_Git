#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "ITexture.h"
#include "OpenGL.h"

class Texture : public ITexture {
public:
    Texture(const TextureDesc& desc, const void* data);
    virtual ~Texture();
    //ディスクリプタの取得
    virtual const TextureDesc& desc() const override;
    //データの設定
    virtual void setData(const void* data) override;
    //データの取得
    virtual void getData(void* data) override;
    //イメージサイズの取得
    virtual unsigned size() const override;

    //ターゲットの取得
    GLenum target() const;
    //テクスチャオブジェクトの取得
    GLuint texture() const;

protected:
    //テクスチャタイプ型
    struct Type {
        GLenum target;
        GLenum arrayTarget;
        unsigned arraySize;
    };
    //ピクセルフォーマット型
    struct Pixel {
        GLenum internalFormat;
        GLenum format;
        GLenum type;
        GLuint size;
        bool complessedFormat;
        bool depthFormat;
        bool stencilFormat;
    };
    //初期化
    void initialize(const void* data);
    //ピクセルフォーマットの取得
    const Pixel& pixel() const;

private:
    //テクスチャのタイプを変換
    static const Type& toType(TextureType type);

    //コピー禁止
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

private:
    //ディスクリプタ
    TextureDesc mDesc;
    //テクスチャタイプ
    Type mType;
    //テクスチャオブジェクト
    GLuint mTexture;
};

#endif // !_TEXTURE_H_
