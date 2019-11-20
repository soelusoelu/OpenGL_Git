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
    //テクニック開始
    virtual void technique(const char* techniqueName) override;
    //パスを指定
    virtual void begin(int passNo = 0) override;
    //パスを終了
    virtual void end() override;
    //テクニック名を取得
    virtual const char* getTechniqueName(int techniqueNo) override;
    //テクニック数を取得
    virtual int getNumTechnique() override;
    //現在のテクニックのパス数を取得
    virtual int getNumPass() override;
    //スカラーを設定
    virtual void setScalar(const char* name, float v = 0) override;
    //ベクトルを設定
    virtual void setVector(const char* name, float x = 0, float y = 0, float z = 0, float w = 1) override;
    //行列を設定
    virtual void setMatrix(const char* name, float* matrix) override;
    //スカラーの配列を設定
    virtual void setScalarArray(const char* name, float* array, unsigned count) override;
    //ベクトルの配列を設定
    virtual void setVectorArray(const char* name, float* array, unsigned count) override;
    //行列の配列を設定
    virtual void setMatrixArray(const char* name, float* array, unsigned count) override;
    //テクスチャのパラメータを設定
    virtual void setTexture(const char* name, ITexture* texture) override;
    //シェーダー入力シグニチャ記述子を取得
    virtual InputSignatureDesc inputSignature(const char* techniqueName, int passNo = 0) override;

private:
    //CGコンテキスト
    CGcontext mContext;
    //エフェクト
    CGeffect mEffect;
    //テクニック
    CGtechnique mTechnique;
    //パス
    CGpass mPass;
};

#endif // !_EFFECT_H_
