#ifndef _IRENDERER_H_
#define _IRENDERER_H_

#include "IBuffer.h"
#include "IEffect.h"
#include "ITexture.h"
#include "IVertexDeclaration.h"
#include "VertexStreamDesc.h"
#include "ViewportDesc.h"

//プリミティブタイプ
enum class PrimitiveType {
    PRIMITIVE_TYPE_POINT_LIST,
    PRIMITIVE_TYPE_LINE_LIST,
    PRIMITIVE_TYPE_LINE_STRIP,
    PRIMITIVE_TYPE_TRIANGLE_LIST,
    PRIMITIVE_TYPE_TRIANGLE_STRIP
};

//インデックスバッファタイプ
enum class IndexType {
    INDEX_TYPE_USHORT,
    INDEX_TYPE_UINT
};

//レンダラインターフェース
class IRenderer {
public:
    virtual ~IRenderer() = default;
    //初期化
    virtual void initialize() = 0;
    //ビューポートの設定
    virtual void setViewport(const ViewportDesc& desc) = 0;
    //ビューポートの取得
    virtual const ViewportDesc& getViewport() const = 0;
    //画面消去
    virtual void clearColorBuffer(float r = 0.f, float g = 0.f, float b = 0.f, float a = 1.f) = 0;
    //デプス・ステンシルバッファの消去
    virtual void clearDepthStencilBuffer(bool depth = true, bool stencil = false) = 0;
    //バッファの作成
    virtual IBuffer* createBuffer(const BufferDesc& desc, const void* data = 0) = 0;
    //テクスチャの作成
    virtual ITexture* createTexture(const TextureDesc& desc, const void* data = 0) = 0;
    //頂点宣言の作成
    virtual IVertexDeclaration* createVertexDeclaration(const VertexDeclarationDesc desc[], unsigned numDesc, const InputSignatureDesc& inputSignature) = 0;
    //エフェクトの作成
    virtual IEffect* createEffect(const char* fileName) = 0;
    //頂点フォーマットの設定
    virtual void setVertexDeclaration(IVertexDeclaration* layout) = 0;
    //頂点バッファの設定
    virtual void setVertexBuffer(const VertexStreamDesc streams[], unsigned numStream = 1, unsigned offset = 0) = 0;
    //インデックスバッファの設定
    virtual void setIndexBuffer(IBuffer* buffer, IndexType type, unsigned offset = 0) = 0;
    //描画プリミティブの設定
    virtual void setPrimitive(PrimitiveType primitive) = 0;
    //頂点バッファを描画
    virtual void draw(unsigned numVertex, unsigned start = 0) = 0;
    //インデックスバッファを描画する
    virtual void drawIndexed(unsigned numIndices, unsigned startIndex = 0, unsigned startVertex = 0) = 0;
    //レンダーターゲットの設定
    virtual void setRenderTargets(ITexture* targets[], unsigned numTargets, ITexture* depthStencil, unsigned index = 0) = 0;
    //レンダーターゲットをリセット
    virtual void resetRenderTarget() = 0;
    //ミップマップの作成
    virtual void generateMipmap(ITexture* texture) = 0;
    //レンダラーをフラッシュ
    virtual void flush() = 0;
    //状態をクリア
    virtual void clearState() = 0;
};

#endif // !_IRENDERER_H_