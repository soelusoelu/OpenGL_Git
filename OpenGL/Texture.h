#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "ITexture.h"
#include "OpenGL.h"

class Texture : public ITexture {
public:
    //�f�B�X�N���v�^�̎擾
    virtual const TextureDesc& desc() const override;
    //�f�[�^�̐ݒ�
    virtual void setData(const void* data) override;
    //�f�[�^�̎擾
    virtual void getData(void* data) override;
    //�C���[�W�T�C�Y�̎擾
    virtual unsigned size() const override;

    //�^�[�Q�b�g�̎擾
    GLenum target() const;
    //�e�N�X�`���I�u�W�F�N�g�̎擾
    GLuint texture() const;

    //�f�v�X�E�X�e���V���o�b�t�@�̃A�^�b�`
    void attachDepthStencil();
    //�t���[���o�b�t�@�I�u�W�F�N�g�ւ̃A�^�b�`
    void attachFramebuffer(GLuint drawBuffer, unsigned index);
    //�~�b�v�}�b�v�̍쐬
    void generateMipmap();

protected:
    Texture(const TextureDesc& desc);
    virtual ~Texture();
    //�e�N�X�`���^�C�v�^
    struct Type {
        GLenum target;
        GLenum arrayTarget;
        unsigned arraySize;
    };
    //�s�N�Z���t�H�[�}�b�g�^
    struct Pixel {
        GLenum internalFormat;
        GLenum format;
        GLenum type;
        GLuint size;
        bool complessedFormat;
        bool depthFormat;
        bool stencilFormat;
    };
    //������
    void initialize(const void* data);
    //�s�N�Z���t�H�[�}�b�g�̎擾
    const Pixel& pixel() const;
    //�C���[�W�T�C�Y�̌v�Z
    unsigned imageSize(unsigned mipLevel) const;
    //�~�b�v�}�b�v�T�C�Y���擾
    static unsigned mipSize(unsigned size, unsigned mipLevel);
    //�C���[�W�ݒ�p�̃^�[�Q�b�g���擾
    GLenum target(unsigned index) const;

private:
    //�e�N�X�`���̃^�C�v��ϊ�
    static const Type& toType(TextureType type);
    //�e�N�X�`���z��T�C�Y�̎擾
    unsigned arraySize() const;
    //�C���[�W�̎擾
    void getTexImage(void* data, unsigned mipLevel, unsigned index) const;
    //�C���[�W�̐ݒ�
    virtual void texImage(const void* data, unsigned mipLevel, unsigned index) = 0;
    //�C���[�W�̍X�V
    virtual void texSubImage(const void* data, unsigned mipLevel, unsigned index) = 0;
    //�t���[���o�b�t�@�I�u�W�F�N�g�ɃA�^�b�`
    virtual void framebufferTexture(GLuint drawBuffer, unsigned index) = 0;

    //�R�s�[�֎~
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

private:
    //�f�B�X�N���v�^
    TextureDesc mDesc;
    //�e�N�X�`���^�C�v
    Type mType;
    //�e�N�X�`���I�u�W�F�N�g
    GLuint mTexture;
    //�f�v�X�e�N�X�`��
    GLuint mDepthTexture;
    //�X�e���V���e�N�X�`��
    GLuint mStencilTexture;
};

#endif // !_TEXTURE_H_
