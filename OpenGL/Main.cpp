#include "Renderer.h"
#include <GL/glut.h>

//���_�o�b�t�@
IBuffer* vertexBuffer;
//�C���f�b�N�X�o�b�t�@
IBuffer* indexBuffer;
//�e�N�X�`���I�u�W�F�N�g
ITexture* texture;
//�G�t�F�N�g
IEffect* effect;
//���_�錾
IVertexDeclaration* vertexDeclaration;
//�����_��
IRenderer* renderer;
//�����_�[�^�[�Q�b�g
ITexture* renderTarget;
//�f�v�X�o�b�t�@
ITexture* depthStencil;

//������
void init() {
    //�����_���̍쐬
    renderer = new Renderer();

    //�G�t�F�N�g���쐬
    effect = renderer->createEffect("test.cgfx");
    InputSignatureDesc descSignature = effect->inputSignature("Test");

    //���_���C�A�E�g�̍쐬
    static const VertexDeclarationDesc layout[] = {
        { VertexSemantic::VERTEX_SEMANTIC_POSITION, 0, VertexType::VERTEX_TYPE_FLOAT3, sizeof(float) * 0, 0 },
        { VertexSemantic::VERTEX_SEMANTIC_TEXCOORD, 0, VertexType::VERTEX_TYPE_FLOAT2, sizeof(float) * 3, 0 }
    };
    unsigned numDesc = sizeof(layout) / sizeof(layout[0]);
    vertexDeclaration = renderer->createVertexDeclaration(layout, numDesc, descSignature);

    //�e�N�X�`���̍쐬
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

    //���_�o�b�t�@
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

    //�C���f�b�N�X�o�b�t�@
    static const unsigned short indices[] = {
        0, 1, 2,
        0, 2, 3
    };
    //�C���f�b�N�X�o�b�t�@�̍쐬
    BufferDesc indexBufferDesc;
    indexBufferDesc.type = BufferType::BUFFER_TYPE_INDEX;
    indexBufferDesc.size = sizeof(indices);
    indexBufferDesc.usage = BufferUsage::BUFFER_USAGE_IMMUTABLE;
    indexBuffer = renderer->createBuffer(indexBufferDesc, indices);
    //�����_�[�^�[�Q�b�g�̍쐬
    TextureDesc renderTargetDesc;
    renderTargetDesc.type = TextureType::TEXTURE_TYPE_2D;
    renderTargetDesc.format = TextureFormat::TEXTURE_FORMAT_RGBA8;
    renderTargetDesc.renderTarget = true;
    renderTargetDesc.width = 256;
    renderTargetDesc.height = 256;
    renderTargetDesc.usage = TextureUsage::TEXTURE_USAGE_DEFAULT;
    renderTarget = renderer->createTexture(renderTargetDesc);
    //�f�v�X�o�b�t�@�p�̃e�N�X�`�����쐬
    TextureDesc depthStencilDesc;
    depthStencilDesc.type = TextureType::TEXTURE_TYPE_2D;
    depthStencilDesc.format = TextureFormat::TEXTURE_FORMAT_D32F;
    depthStencilDesc.renderTarget = false;
    depthStencilDesc.width = 256;
    depthStencilDesc.height = 256;
    depthStencilDesc.usage = TextureUsage::TEXTURE_USAGE_DEFAULT;
    depthStencil = renderer->createTexture(depthStencilDesc);
}

//�`��
void display() {
    //�����_�[�^�[�Q�b�g�̐ݒ�
    renderer->setRenderTargets(&renderTarget, 1, depthStencil);
    //��ʏ���(�w�i���F)
    renderer->clearColorBuffer(1.f, 1.f);
    //�f�v�X�o�b�t�@�̏���
    renderer->clearDepthStencilBuffer();

    //�r���[�|�[�g�̐ݒ�(�����_�[�^�[�Q�b�g�ɍ��킹��)
    ViewportDesc viewport;
    viewport.x = 0;
    viewport.y = 0;
    viewport.width = renderTarget->desc().width;
    viewport.height = renderTarget->desc().height;
    renderer->setViewport(viewport);

    //�e�N�X�`����ݒ�
    effect->setTexture("baseMap", texture);
    //�e�N�j�b�N���J�n
    effect->technique("Test");
    //�p�X���w��
    effect->begin();

    //���_�o�b�t�@�̐ݒ�
    VertexStreamDesc stream;
    stream.buffer = vertexBuffer;
    stream.offset = 0;
    stream.stride = sizeof(float) * 5;
    renderer->setVertexBuffer(&stream);
    //���_���C�A�E�g�̐ݒ�
    renderer->setVertexDeclaration(vertexDeclaration);
    //�C���f�b�N�X�o�b�t�@�̐ݒ�
    renderer->setIndexBuffer(indexBuffer, IndexType::INDEX_TYPE_USHORT);

    //���_�C���f�b�N�X�𗘗p���ĕ`��
    renderer->setPrimitive(PrimitiveType::PRIMITIVE_TYPE_TRIANGLE_LIST);
    renderer->drawIndexed(6);

    //�G�t�F�N�g�̏I��
    effect->end();

    //�����_�[�^�[�Q�b�g�̃��Z�b�g
    renderer->resetRenderTarget();
    //�r���[�|�[�g�̕��A(�E�B���h�E�ɍ��킹��)
    viewport.x = 0;
    viewport.y = 0;
    viewport.width = 500;
    viewport.height = 500;
    renderer->setViewport(viewport);
    //��ʏ���
    renderer->clearColorBuffer(0.f, 0.125f, 0.3f, 1.f);
    //�f�v�X�o�b�t�@�̏���
    renderer->clearDepthStencilBuffer();
    //�e�N�X�`���̐ݒ�(�����_�����O�����e�N�X�`����ݒ�)
    effect->setTexture("baseMap", renderTarget);
    //�G�t�F�N�g�̊J�n
    effect->technique("Test");
    effect->begin();
    //���_�o�b�t�@�̐ݒ�
    stream.buffer = vertexBuffer;
    stream.offset = 0;
    stream.stride = sizeof(float) * 5;
    renderer->setVertexBuffer(&stream);
    //���_���C�A�E�g�̐ݒ�
    renderer->setVertexDeclaration(vertexDeclaration);
    //�C���f�b�N�X�o�b�t�@�̐ݒ�
    renderer->setIndexBuffer(indexBuffer, IndexType::INDEX_TYPE_USHORT);

    //���_�C���f�b�N�X�𗘗p���ĕ`��
    renderer->setPrimitive(PrimitiveType::PRIMITIVE_TYPE_TRIANGLE_LIST);
    renderer->drawIndexed(6);
    //�G�t�F�N�g�̏I��
    effect->end();

    //�R�}���h�̋������s
    renderer->flush();
    //�_�u���o�b�t�@�̐ؑ�
    glutSwapBuffers();
}

//���C���֐�
int main(int argc, char* argv[]) {
    //�E�B���h�E�̐ݒ���s��
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL");
    //������
    init();
    //�\�������̊֐���ݒ�
    glutDisplayFunc(display);
    //���C�����[�v�������s��
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