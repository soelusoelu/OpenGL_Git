#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "ITexture.h"
#include "OpenGL.h"

class Texture : public ITexture {
public:
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

    //デプス・ステンシルバッファのアタッチ
    void attachDepthStencil();
    //フレームバッファオブジェクトへのアタッチ
    void attachFramebuffer(GLuint drawBuffer, unsigned index);
    //ミップマップの作成
    void generateMipmap();

protected:
    Texture(const TextureDesc& desc);
    virtual ~Texture();
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
    //イメージサイズの計算
    unsigned imageSize(unsigned mipLevel) const;
    //ミップマップサイズを取得
    static unsigned mipSize(unsigned size, unsigned mipLevel);
    //イメージ設定用のターゲットを取得
    GLenum target(unsigned index) const;

private:
    //テクスチャのタイプを変換
    static const Type& toType(TextureType type);
    //テクスチャ配列サイズの取得
    unsigned arraySize() const;
    //イメージの取得
    void getTexImage(void* data, unsigned mipLevel, unsigned index) const;
    //イメージの設定
    virtual void texImage(const void* data, unsigned mipLevel, unsigned index) = 0;
    //イメージの更新
    virtual void texSubImage(const void* data, unsigned mipLevel, unsigned index) = 0;
    //フレームバッファオブジェクトにアタッチ
    virtual void framebufferTexture(GLuint drawBuffer, unsigned index) = 0;

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
    //デプステクスチャ
    GLuint mDepthTexture;
    //ステンシルテクスチャ
    GLuint mStencilTexture;
};

#endif // !_TEXTURE_H_
