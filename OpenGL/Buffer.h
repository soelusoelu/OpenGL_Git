#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "IBuffer.h"
#include "OpenGL.h"

class Buffer : public IBuffer {
public:
    Buffer(const BufferDesc& desc, const void* data = 0);
    virtual ~Buffer();
    //�f�B�X�N���v�^�̎擾
    virtual const BufferDesc& desc() const override;
    //�f�[�^�̐ݒ�
    virtual void setData(const void* data) override;
    //�f�[�^�̎擾
    virtual void getData(void* data) const override;
    //�o�b�t�@�̎擾
    GLuint buffer() const;

private:
    //�o�b�t�@�̃^�C�v��ϊ�
    static GLenum toTarget(BufferType type);
    //�o�b�t�@�̎g�p���@��ϊ�
    static GLenum toUsage(BufferUsage usage);

    //�R�s�[�֎~
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

private:
    //�f�B�X�N���v�^
    BufferDesc mDesc;
    //�o�b�t�@�I�u�W�F�N�g
    GLuint mBuffer;
    //�^�[�Q�b�g
    GLenum mTarget;
    //�g�p���@
    GLenum mUsage;
};

#endif // !_BUFFER_H_
