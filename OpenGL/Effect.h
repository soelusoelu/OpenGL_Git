#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "IEffect.h"
#include "OpenGL.h"
#include <Cg/cg.h>
#include <Cg/cgGL.h>

#pragma comment(lib, "cg.lib")
#pragma comment(lib, "cgGL.lib")

class Texture;

class Effect : public IEffect {
public:
    Effect(const char* fileName);
    virtual ~Effect();
    //�e�N�j�b�N�J�n
    virtual void technique(const char* techniqueName) override;
    //�p�X���w��
    virtual void begin(int passNo = 0) override;
    //�p�X���I��
    virtual void end() override;
    //�e�N�j�b�N�����擾
    virtual const char* getTechniqueName(int techniqueNo) override;
    //�e�N�j�b�N�����擾
    virtual int getNumTechnique() override;
    //���݂̃e�N�j�b�N�̃p�X�����擾
    virtual int getNumPass() override;
    //�X�J���[��ݒ�
    virtual void setScalar(const char* name, float v = 0) override;
    //�x�N�g����ݒ�
    virtual void setVector(const char* name, float x = 0, float y = 0, float z = 0, float w = 1) override;
    //�s���ݒ�
    virtual void setMatrix(const char* name, float* matrix) override;
    //�X�J���[�̔z���ݒ�
    virtual void setScalarArray(const char* name, float* array, unsigned count) override;
    //�x�N�g���̔z���ݒ�
    virtual void setVectorArray(const char* name, float* array, unsigned count) override;
    //�s��̔z���ݒ�
    virtual void setMatrixArray(const char* name, float* array, unsigned count) override;
    //�e�N�X�`���̃p�����[�^��ݒ�
    virtual void setTexture(const char* name, ITexture* texture) override;
    //�V�F�[�_�[���̓V�O�j�`���L�q�q���擾
    virtual InputSignatureDesc inputSignature(const char* techniqueName, int passNo = 0) override;

private:
    //CG�R���e�L�X�g
    CGcontext mContext;
    //�G�t�F�N�g
    CGeffect mEffect;
    //�e�N�j�b�N
    CGtechnique mTechnique;
    //�p�X
    CGpass mPass;
};

#endif // !_EFFECT_H_
