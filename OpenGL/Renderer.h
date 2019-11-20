#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "IRenderer.h"
#include "OpenGL.h"

class Buffer;
class VertexDeclaration;

class Renderer : public IRenderer {
public:
    Renderer();
    virtual ~Renderer();
    //初期化
    virtual void initialize() override;
    //ビューポートの設定
    virtual void setViewport(const ViewportDesc& desc) override;
    //ビューポートの取得
    virtual const ViewportDesc& getViewport() const override;
    //画面消去
    virtual void clearColorBuffer(float r = 0.f, float g = 0.f, float b = 0.f, float a = 1.f) override;
    //デプス・ステンシルバッファの消去
    virtual void clearDepthStencilBuffer(bool depth = true, bool stencil = false) override;
    //バッファの作成
    virtual IBuffer* createBuffer(const BufferDesc& desc, const void* data = 0) override;
    //テクスチャの作成
    virtual ITexture* createTexture(const TextureDesc& desc, const void* data = 0) override;
    //頂点宣言の作成
    virtual IVertexDeclaration* createVertexDeclaration(const VertexDeclarationDesc desc[], unsigned numDesc, const InputSignatureDesc& inputSignature) override;
    //エフェクトの作成
    virtual IEffect* createEffect(const char* fileName) override;
    //頂点宣言の設定
    virtual void setVertexDeclaration(IVertexDeclaration* layout) override;
    //頂点バッファの設定
    virtual void setVertexBuffer(const VertexStreamDesc streams[], unsigned numStream = 1, unsigned offset = 0) override;
    //インデックスバッファの設定
    virtual void setIndexBuffer(IBuffer* buffer, IndexType type, unsigned offset = 0) override;
    //描画プリミティブの設定
    virtual void setPrimitive(PrimitiveType primitive) override;
    //頂点バッファを描画
    virtual void draw(unsigned numVertex, unsigned start = 0) override;
    //インデックスバッファを描画
    virtual void drawIndexed(unsigned numIndices, unsigned startIndex = 0, unsigned startVertex = 0) override;
    //レンダーターゲットを設定
    virtual void setRenderTargets(ITexture* targets[], unsigned numTargets, ITexture* depthStencil, unsigned index = 0) override;
    //レンダーターゲットをリセット
    virtual void resetRenderTarget() override;
    //ミップマップの作成
    virtual void generateMipmap(ITexture* texture) override;
    //レンダラをフラッシュ
    virtual void flush() override;
    //状態をクリア
    virtual void clearState() override;

private:
    //インデックスバッファフォーマット
    struct IndexFormat {
        GLenum type;
        GLuint size;
    };
    //インデックスタイプの変換
    static const IndexFormat& toIndexFormat(IndexType format);
    //プリミティブタイプを変換
    static GLenum toPrimitiveMode(PrimitiveType primitive);

private:
    //レンダリングターゲットの最大数
    static const unsigned RENDER_TARGET_MAX = 8;
    //頂点バッファストリームの最大数
    static const unsigned VERTEX_STREAM_MAX = 16;
    //ビューポート
    ViewportDesc mViewport;
    //頂点バッファストリーム
    VertexStreamDesc mVertexStreams[VERTEX_STREAM_MAX];
    //頂点宣言
    VertexDeclaration* mVertexDeclaration;
    //インデックスバッファ
    Buffer* mIndexBuffer;
    //インデックスバッファフォーマット
    IndexFormat mIndexFormat;
    //インデックスバッファオフセット
    unsigned mIndexOffset;
    //プリミティブモード
    GLenum mPrimitiveMode;
    //フレームバッファオブジェクト
    GLuint mFramebufferObject;
};

#endif // !_RENDERER_H_
