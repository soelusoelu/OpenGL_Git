#include "Renderer.h"
#include "Buffer.h"
#include "Texture.h"
#include "VertexDeclaration.h"
#include "Effect.h"
#include <cassert>

Renderer::Renderer() :
    mVertexDeclaration(nullptr),
    mIndexBuffer(nullptr),
    mIndexFormat(toIndexFormat(IndexType::INDEX_TYPE_USHORT)),
    mIndexOffset(0),
    mPrimitiveMode(toPrimitiveMode(PrimitiveType::PRIMITIVE_TYPE_TRIANGLE_LIST)) {
    initialize();
}

Renderer::~Renderer() {
    clearState();
}

void Renderer::initialize() {
    //面カリングの処理
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    //デプスバッファを1.0でクリアする
    glClearDepth(1.0);
    //デプステストの設定
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //アルファテストの設定
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0);
    //ブレンドステートの設定
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //パースペクティブ補正を行う
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    //レンダーターゲットをリセット
    resetRenderTarget();
}

void Renderer::setViewport(const ViewportDesc& desc) {
    glViewport(desc.x, desc.y, desc.width, desc.height);
    mViewport = desc;
}

const ViewportDesc& Renderer::getViewport() const {
    return mViewport;
}

void Renderer::clearColorBuffer(float r, float g, float b, float a) {
    //消去カラーの設定
    glClearColor(r, g, b, a);
    //カラーバッファの消去
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::clearDepthStencilBuffer(bool depth, bool stencil) {
    GLbitfield mask = 0;
    if (depth) {
        mask |= GL_DEPTH_BUFFER_BIT;
    }
    if (stencil) {
        mask |= GL_STENCIL_BUFFER_BIT;
    }
    glClear(mask);
}

IBuffer* Renderer::createBuffer(const BufferDesc& desc, const void* data) {
    return new Buffer(desc, data);
}

ITexture* Renderer::createTexture(const TextureDesc& desc, const void* data) {
    return new Texture(desc, data);
}

IVertexDeclaration* Renderer::createVertexDeclaration(const VertexDeclarationDesc desc[], unsigned numDesc, const InputSignatureDesc& inputSignature) {
    (void)inputSignature; //OpenGLでは使用しない
    return new VertexDeclaration(desc, numDesc);
}

IEffect* Renderer::createEffect(const char* fileName) {
    return new Effect(fileName);
}

void Renderer::setVertexDeclaration(IVertexDeclaration* layout) {
    mVertexDeclaration = reinterpret_cast<VertexDeclaration*>(layout);
}

void Renderer::setVertexBuffer(const VertexStreamDesc streams[], unsigned numStream, unsigned offset) {
    for (unsigned i = 0; i < numStream; ++i) {
        mVertexStreams[i + offset] = streams[i];
    }
}

void Renderer::setIndexBuffer(IBuffer* buffer, IndexType type, unsigned offset) {
    mIndexBuffer = reinterpret_cast<Buffer*>(buffer);
    mIndexFormat = toIndexFormat(type);
    mIndexOffset = offset;
}

void Renderer::setPrimitive(PrimitiveType primitive) {
    mPrimitiveMode = toPrimitiveMode(primitive);
}

void Renderer::draw(unsigned numVertex, unsigned start) {
    //頂点バッファを設定
    mVertexDeclaration->setVertexStream(mVertexStreams, start);
    //頂点バッファの描画
    glDrawArrays(mPrimitiveMode, 0, numVertex);
    //頂点バッファをリセット
    mVertexDeclaration->resetVertexStream();
}

void Renderer::drawIndexed(unsigned numIndices, unsigned startIndex, unsigned startVertex) {
    //頂点バッファを設定
    mVertexDeclaration->setVertexStream(mVertexStreams, startVertex);
    //インデックスバッファをバインド
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, mIndexBuffer->buffer());
    //インデックスバッファの描画
    GLubyte* base = nullptr;
    glDrawElements(
        mPrimitiveMode,
        numIndices,
        mIndexFormat.type,
        &base[(mIndexOffset + startIndex) * mIndexFormat.size]
    );
    //インデックスバッファをリセット
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
    //頂点バッファをリセット
    mVertexDeclaration->resetVertexStream();
}

void Renderer::setRenderTargets(ITexture* targets[], unsigned numTargets, ITexture* depthStencil, unsigned index) {
}

void Renderer::resetRenderTarget() {
}

void Renderer::generateMipmap(ITexture* texture) {
}

void Renderer::flush() {
    glFlush();
}

void Renderer::clearState() {
    initialize();
}

const Renderer::IndexFormat& Renderer::toIndexFormat(IndexType format) {
    static const Renderer::IndexFormat indexFormat[] = {
        { GL_UNSIGNED_SHORT, sizeof(GLushort) }, //INDEX_TYPE_USHORT = 0
        { GL_UNSIGNED_INT, sizeof(GLuint) } //INDEX_TYPE_UINT = 1
    };
    return indexFormat[static_cast<int>(format)];
}

GLenum Renderer::toPrimitiveMode(PrimitiveType primitive) {
    static const GLenum primitiveModes[] = {
        GL_POINTS, //PRIMITIVE_TYPE_POINTLIST = 0
        GL_LINES, //PRIMITIVE_TYPE_LINELIST = 1
        GL_LINE_STRIP, //PRIMITIVE_TYPE_LINESTRIP = 2
        GL_TRIANGLES, //PRIMITIVE_TYPE_TRIANGLE_LIST = 3
        GL_TRIANGLE_STRIP //PRIMITIVE_TYPE_TRIANGLE_STRIP = 4
    };
    return primitiveModes[static_cast<int>(primitive)];
}
