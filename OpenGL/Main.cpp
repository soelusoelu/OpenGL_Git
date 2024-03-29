#include "Renderer.h"
#include <GL/glut.h>

//頂点バッファ
IBuffer* vertexBuffer;
//インデックスバッファ
IBuffer* indexBuffer;
//テクスチャオブジェクト
ITexture* texture;
//エフェクト
IEffect* effect;
//頂点宣言
IVertexDeclaration* vertexDeclaration;
//レンダラ
IRenderer* renderer;
//レンダーターゲット
ITexture* renderTarget;
//デプスバッファ
ITexture* depthStencil;

//初期化
void init() {
    //レンダラの作成
    renderer = new Renderer();

    //エフェクトを作成
    effect = renderer->createEffect("test.cgfx");
    InputSignatureDesc descSignature = effect->inputSignature("Test");

    //頂点レイアウトの作成
    static const VertexDeclarationDesc layout[] = {
        { VertexSemantic::VERTEX_SEMANTIC_POSITION, 0, VertexType::VERTEX_TYPE_FLOAT3, sizeof(float) * 0, 0 },
        { VertexSemantic::VERTEX_SEMANTIC_TEXCOORD, 0, VertexType::VERTEX_TYPE_FLOAT2, sizeof(float) * 3, 0 }
    };
    unsigned numDesc = sizeof(layout) / sizeof(layout[0]);
    vertexDeclaration = renderer->createVertexDeclaration(layout, numDesc, descSignature);

    //テクスチャの作成
    static const unsigned char image[4][4][4] = {
        { {   0, 255,   0, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, {   0, 255,   0, 255 } },
        { { 255, 255, 255, 255 }, { 255,   0,   0, 255 }, { 255,   0, 255, 255 }, { 255, 255, 255, 255 } },
        { { 255, 255, 255, 255 }, {   0,   0, 255, 255 }, { 255, 255,   0, 255 }, { 255, 255, 255, 255 } },
        { {   0, 255,   0, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, {   0, 255,   0, 255 } }
    };
    TextureDesc textureDesc;
    textureDesc.type = TextureType::TEXTURE_TYPE_2D;
    textureDesc.format = TextureFormat::TEXTURE_FORMAT_RGBA8;
    textureDesc.width = 4;
    textureDesc.height = 4;
    texture = renderer->createTexture(textureDesc, image);

    //頂点バッファ
    static const float vertices[][5] = {
        { -0.5f, 0.5f, 0.f, 0.f, 0.f },
        { -0.5f, -0.5f, 0.f, 0.f, 1.f },
        { 0.5f, -0.5f, 0.f, 1.f, 1.f },
        { 0.5f, 0.5f, 0.f, 1.f, 0.f }
    };
    BufferDesc vertexBufferDesc;
    vertexBufferDesc.type = BufferType::BUFFER_TYPE_VERTEX;
    vertexBufferDesc.size = sizeof(vertices);
    vertexBufferDesc.usage = BufferUsage::BUFFER_USAGE_IMMUTABLE;
    vertexBuffer = renderer->createBuffer(vertexBufferDesc, vertices);

    //インデックスバッファ
    static const unsigned short indices[] = {
        0, 1, 2,
        0, 2, 3
    };
    //インデックスバッファの作成
    BufferDesc indexBufferDesc;
    indexBufferDesc.type = BufferType::BUFFER_TYPE_INDEX;
    indexBufferDesc.size = sizeof(indices);
    indexBufferDesc.usage = BufferUsage::BUFFER_USAGE_IMMUTABLE;
    indexBuffer = renderer->createBuffer(indexBufferDesc, indices);
    //レンダーターゲットの作成
    TextureDesc renderTargetDesc;
    renderTargetDesc.type = TextureType::TEXTURE_TYPE_2D;
    renderTargetDesc.format = TextureFormat::TEXTURE_FORMAT_RGBA8;
    renderTargetDesc.renderTarget = true;
    renderTargetDesc.width = 256;
    renderTargetDesc.height = 256;
    renderTargetDesc.usage = TextureUsage::TEXTURE_USAGE_DEFAULT;
    renderTarget = renderer->createTexture(renderTargetDesc);
    //デプスバッファ用のテクスチャを作成
    TextureDesc depthStencilDesc;
    depthStencilDesc.type = TextureType::TEXTURE_TYPE_2D;
    depthStencilDesc.format = TextureFormat::TEXTURE_FORMAT_D32F;
    depthStencilDesc.renderTarget = false;
    depthStencilDesc.width = 256;
    depthStencilDesc.height = 256;
    depthStencilDesc.usage = TextureUsage::TEXTURE_USAGE_DEFAULT;
    depthStencil = renderer->createTexture(depthStencilDesc);
}

//描画
void display() {
    //レンダーターゲットの設定
    renderer->setRenderTargets(&renderTarget, 1, depthStencil);
    //画面消去(背景黄色)
    renderer->clearColorBuffer(1.f, 1.f);
    //デプスバッファの消去
    renderer->clearDepthStencilBuffer();

    //ビューポートの設定(レンダーターゲットに合わせる)
    ViewportDesc viewport;
    viewport.x = 0;
    viewport.y = 0;
    viewport.width = renderTarget->desc().width;
    viewport.height = renderTarget->desc().height;
    renderer->setViewport(viewport);

    //テクスチャを設定
    effect->setTexture("baseMap", texture);
    //テクニックを開始
    effect->technique("Test");
    //パスを指定
    effect->begin();

    //頂点バッファの設定
    VertexStreamDesc stream;
    stream.buffer = vertexBuffer;
    stream.offset = 0;
    stream.stride = sizeof(float) * 5;
    renderer->setVertexBuffer(&stream);
    //頂点レイアウトの設定
    renderer->setVertexDeclaration(vertexDeclaration);
    //インデックスバッファの設定
    renderer->setIndexBuffer(indexBuffer, IndexType::INDEX_TYPE_USHORT);

    //頂点インデックスを利用して描画
    renderer->setPrimitive(PrimitiveType::PRIMITIVE_TYPE_TRIANGLE_LIST);
    renderer->drawIndexed(6);

    //エフェクトの終了
    effect->end();

    //レンダーターゲットのリセット
    renderer->resetRenderTarget();
    //ビューポートの復帰(ウィンドウに合わせる)
    viewport.x = 0;
    viewport.y = 0;
    viewport.width = 500;
    viewport.height = 500;
    renderer->setViewport(viewport);
    //画面消去
    renderer->clearColorBuffer(0.f, 0.125f, 0.3f, 1.f);
    //デプスバッファの消去
    renderer->clearDepthStencilBuffer();
    //テクスチャの設定(レンダリングしたテクスチャを設定)
    effect->setTexture("baseMap", renderTarget);
    //エフェクトの開始
    effect->technique("Test");
    effect->begin();
    //頂点バッファの設定
    stream.buffer = vertexBuffer;
    stream.offset = 0;
    stream.stride = sizeof(float) * 5;
    renderer->setVertexBuffer(&stream);
    //頂点レイアウトの設定
    renderer->setVertexDeclaration(vertexDeclaration);
    //インデックスバッファの設定
    renderer->setIndexBuffer(indexBuffer, IndexType::INDEX_TYPE_USHORT);

    //頂点インデックスを利用して描画
    renderer->setPrimitive(PrimitiveType::PRIMITIVE_TYPE_TRIANGLE_LIST);
    renderer->drawIndexed(6);
    //エフェクトの終了
    effect->end();

    //コマンドの強制実行
    renderer->flush();
    //ダブルバッファの切替
    glutSwapBuffers();
}

//メイン関数
int main(int argc, char* argv[]) {
    //ウィンドウの設定を行う
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL");
    //初期化
    init();
    //表示処理の関数を設定
    glutDisplayFunc(display);
    //メインループ処理を行う
    glutMainLoop();

    delete vertexBuffer;
    delete indexBuffer;
    delete texture;
    delete effect;
    delete vertexDeclaration;
    delete renderer;
    delete renderTarget;
    delete depthStencil;
}