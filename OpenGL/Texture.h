#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "ITexture.h"
#include "OpenGL.h"

class Texture : public ITexture {
public:
    Texture(const TextureDesc& desc, const void* data);
    virtual ~Texture();
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

protected:
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

private:
    //�e�N�X�`���̃^�C�v��ϊ�
    static const Type& toType(TextureType type);

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
};

#endif // !_TEXTURE_H_
