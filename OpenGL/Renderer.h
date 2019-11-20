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
    //������
    virtual void initialize() override;
    //�r���[�|�[�g�̐ݒ�
    virtual void setViewport(const ViewportDesc& desc) override;
    //�r���[�|�[�g�̎擾
    virtual const ViewportDesc& getViewport() const override;
    //��ʏ���
    virtual void clearColorBuffer(float r = 0.f, float g = 0.f, float b = 0.f, float a = 1.f) override;
    //�f�v�X�E�X�e���V���o�b�t�@�̏���
    virtual void clearDepthStencilBuffer(bool depth = true, bool stencil = false) override;
    //�o�b�t�@�̍쐬
    virtual IBuffer* createBuffer(const BufferDesc& desc, const void* data = 0) override;
    //�e�N�X�`���̍쐬
    virtual ITexture* createTexture(const TextureDesc& desc, const void* data = 0) override;
    //���_�錾�̍쐬
    virtual IVertexDeclaration* createVertexDeclaration(const VertexDeclarationDesc desc[], unsigned numDesc, const InputSignatureDesc& inputSignature) override;
    //�G�t�F�N�g�̍쐬
    virtual IEffect* createEffect(const char* fileName) override;
    //���_�錾�̐ݒ�
    virtual void setVertexDeclaration(IVertexDeclaration* layout) override;
    //���_�o�b�t�@�̐ݒ�
    virtual void setVertexBuffer(const VertexStreamDesc streams[], unsigned numStream = 1, unsigned offset = 0) override;
    //�C���f�b�N�X�o�b�t�@�̐ݒ�
    virtual void setIndexBuffer(IBuffer* buffer, IndexType type, unsigned offset = 0) override;
    //�`��v���~�e�B�u�̐ݒ�
    virtual void setPrimitive(PrimitiveType primitive) override;
    //���_�o�b�t�@��`��
    virtual void draw(unsigned numVertex, unsigned start = 0) override;
    //�C���f�b�N�X�o�b�t�@��`��
    virtual void drawIndexed(unsigned numIndices, unsigned startIndex = 0, unsigned startVertex = 0) override;
    //�����_�[�^�[�Q�b�g��ݒ�
    virtual void setRenderTargets(ITexture* targets[], unsigned numTargets, ITexture* depthStencil, unsigned index = 0) override;
    //�����_�[�^�[�Q�b�g�����Z�b�g
    virtual void resetRenderTarget() override;
    //�~�b�v�}�b�v�̍쐬
    virtual void generateMipmap(ITexture* texture) override;
    //�����_�����t���b�V��
    virtual void flush() override;
    //��Ԃ��N���A
    virtual void clearState() override;

private:
    //�C���f�b�N�X�o�b�t�@�t�H�[�}�b�g
    struct IndexFormat {
        GLenum type;
        GLuint size;
    };
    //�C���f�b�N�X�^�C�v�̕ϊ�
    static const IndexFormat& toIndexFormat(IndexType format);
    //�v���~�e�B�u�^�C�v��ϊ�
    static GLenum toPrimitiveMode(PrimitiveType primitive);

private:
    //�����_�����O�^�[�Q�b�g�̍ő吔
    static const unsigned RENDER_TARGET_MAX = 8;
    //���_�o�b�t�@�X�g���[���̍ő吔
    static const unsigned VERTEX_STREAM_MAX = 16;
    //�r���[�|�[�g
    ViewportDesc mViewport;
    //���_�o�b�t�@�X�g���[��
    VertexStreamDesc mVertexStreams[VERTEX_STREAM_MAX];
    //���_�錾
    VertexDeclaration* mVertexDeclaration;
    //�C���f�b�N�X�o�b�t�@
    Buffer* mIndexBuffer;
    //�C���f�b�N�X�o�b�t�@�t�H�[�}�b�g
    IndexFormat mIndexFormat;
    //�C���f�b�N�X�o�b�t�@�I�t�Z�b�g
    unsigned mIndexOffset;
    //�v���~�e�B�u���[�h
    GLenum mPrimitiveMode;
    //�t���[���o�b�t�@�I�u�W�F�N�g
    GLuint mFramebufferObject;
};

#endif // !_RENDERER_H_
