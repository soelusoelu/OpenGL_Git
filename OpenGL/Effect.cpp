#include "Effect.h"
#include "Texture.h"
#include <iostream>
#include <cassert>

Effect::Effect(const char* fileName) :
    mContext(0),
    mEffect(0),
    mTechnique(0),
    mPass(0) {
    //�R���e�L�X�g���쐬
    mContext = cgCreateContext();
    assert(mContext);
    //�R���e�L�X�g��OpenGL�ɐݒ�
    cgGLRegisterStates(mContext);
    //�G�t�F�N�g��ǂݍ���
    mEffect = cgCreateEffectFromFile(mContext, fileName, NULL);
    if (!mEffect) {
        //�G���[���b�Z�[�W���o�͂��ċ����I��
        const char* listing = cgGetLastListing(mContext);
        if (listing) {
            std::cout << listing;
        }
    }
    assert(mEffect);
    //�f�t�H���g�̃e�N�j�b�N��ݒ�
    mTechnique = cgGetFirstTechnique(mEffect);
}

Effect::~Effect() {
    //�G�t�F�N�g���폜
    cgIsEffect(mEffect);
    //�R���e�L�X�g���폜
    cgDestroyContext(mContext);
}

void Effect::technique(const char* techniqueName) {
    //�e�N�j�b�N���擾
    mTechnique = cgGetNamedTechnique(mEffect, techniqueName);
}

void Effect::begin(int passNo) {
    //�ŏ��̃p�X���擾
    mPass = cgGetFirstPass(mTechnique);
    //�w��̃p�X������
    for (int n = 0; n < passNo; n++) {
        mPass = cgGetNextPass(mPass);
    }
    //�p�X��L����
    cgSetPassState(mPass);
}

void Effect::end() {
    //���݂̃p�X�����Z�b�g����
    cgResetPassState(mPass);
    //�p�X�𖳌���
    mPass = 0;
}

const char* Effect::getTechniqueName(int techniqueNo) {
    CGtechnique t = cgGetFirstTechnique(mEffect);
    for (int n = 0; n < techniqueNo; n++) {
        t = cgGetNextTechnique(t);
    }
    return cgGetTechniqueName(t);
}

int Effect::getNumTechnique() {
    int numTechnique = 0;
    for (CGtechnique t = cgGetFirstTechnique(mEffect); cgIsTechnique(t); t = cgGetNextTechnique(t)) {
        numTechnique++;
    }
    return numTechnique;
}

int Effect::getNumPass() {
    //�p�X�̑����𒲂ׂ�
    int numPass = 0;
    for (CGpass p = cgGetFirstPass(mTechnique); cgIsPass(p); p = cgGetNextPass(p)) {
        numPass++;
    }
    return numPass;
}

void Effect::setScalar(const char* name, float v) {
    CGparameter param = cgGetNamedEffectParameter(mEffect, name);
    cgSetParameter1f(param, v);
}

void Effect::setVector(const char* name, float x, float y, float z, float w) {
    CGparameter param = cgGetNamedEffectParameter(mEffect, name);
    float v[4] = { x, y, z, w };
    cgSetParameterValuefc(param, cgGetParameterColumns(param), v);
}

void Effect::setMatrix(const char* name, float* matrix) {
    CGparameter param = cgGetNamedEffectParameter(mEffect, name);
    cgSetMatrixParameterfr(param, matrix);
}

void Effect::setScalarArray(const char* name, float* array, unsigned count) {
    CGparameter param = cgGetNamedEffectParameter(mEffect, name);
    cgSetParameterValuefc(param, count, array);
}

void Effect::setVectorArray(const char* name, float* array, unsigned count) {
    CGparameter param = cgGetNamedEffectParameter(mEffect, name);
    cgSetParameterValuefc(param, cgGetParameterColumns(param) * count, array);
}

void Effect::setMatrixArray(const char* name, float* array, unsigned count) {
    CGparameter param = cgGetNamedEffectParameter(mEffect, name);
    cgSetParameterValuefr(param, cgGetParameterColumns(param) * cgGetParameterRows(param) * count, array);
}

void Effect::setTexture(const char* name, ITexture* texture) {
    CGparameter param = cgGetNamedEffectParameter(mEffect, name);
    cgGLSetupSampler(param, dynamic_cast<Texture*>(texture)->texture());
}

InputSignatureDesc Effect::inputSignature(const char* techniqueName, int passNo) {
    (void)techniqueName;
    (void)passNo;
    //Directx10�ƌ݊����������邽�߂̃_�~�[
    InputSignatureDesc descSignature = { 0, 0 };
    return descSignature;
}
