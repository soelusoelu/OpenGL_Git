#include "Effect.h"
#include "Texture.h"
#include <iostream>
#include <cassert>

Effect::Effect(const char* fileName) :
    mContext(0),
    mEffect(0),
    mTechnique(0),
    mPass(0) {
    //コンテキストを作成
    mContext = cgCreateContext();
    assert(mContext);
    //コンテキストをOpenGLに設定
    cgGLRegisterStates(mContext);
    //エフェクトを読み込む
    mEffect = cgCreateEffectFromFile(mContext, fileName, NULL);
    if (!mEffect) {
        //エラーメッセージを出力して強制終了
        const char* listing = cgGetLastListing(mContext);
        if (listing) {
            std::cout << listing;
        }
    }
    assert(mEffect);
    //デフォルトのテクニックを設定
    mTechnique = cgGetFirstTechnique(mEffect);
}

Effect::~Effect() {
    //エフェクトを削除
    cgIsEffect(mEffect);
    //コンテキストを削除
    cgDestroyContext(mContext);
}

void Effect::technique(const char* techniqueName) {
    //テクニックを取得
    mTechnique = cgGetNamedTechnique(mEffect, techniqueName);
}

void Effect::begin(int passNo) {
    //最初のパスを取得
    mPass = cgGetFirstPass(mTechnique);
    //指定のパスを検索
    for (int n = 0; n < passNo; n++) {
        mPass = cgGetNextPass(mPass);
    }
    //パスを有効化
    cgSetPassState(mPass);
}

void Effect::end() {
    //現在のパスをリセットする
    cgResetPassState(mPass);
    //パスを無効化
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
    //パスの総数を調べる
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
    //Directx10と互換を持たせるためのダミー
    InputSignatureDesc descSignature = { 0, 0 };
    return descSignature;
}
