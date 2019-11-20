#ifndef _IEFFECT_H_
#define _IEFFECT_H_

#include "InputSignatureDesc.h"

class ITexture;

//エフェクトインターフェース
class IEffect {
public:
    virtual ~IEffect() = default;
    //テクニックを開始する
    virtual void technique(const char* techniqueName) = 0;
    //パスを指定する
    virtual void begin(int passNo = 0) = 0;
    //パスを終了する
    virtual void end() = 0;
    //テクニック名を取得
    virtual const char* getTechniqueName(int techniqueNo) = 0;
    //テクニック数を取得
    virtual int getNumTechnique() = 0;
    //現在のテクニックのパス数を取得
    virtual int getNumPass() = 0;
    //スカラーを設定
    virtual void setScalar(const char* name, float v = 0) = 0;
    //ベクトルを設定
    virtual void setVector(const char* name, float x = 0, float y = 0, float z = 0, float w = 1) = 0;
    //行列を設定
    virtual void setMatrix(const char* name, float* matrix) = 0;
    //スカラーの配列の設定
    virtual void setScalarArray(const char* name, float* array, unsigned count) = 0;
    //ベクトルの配列を設定
    virtual void setVectorArray(const char* name, float* array, unsigned count) = 0;
    //行列の配列を設定
    virtual void setMatrixArray(const char* name, float* array, unsigned count) = 0;
    //テクスチャのパラメータを設定
    virtual void setTexture(const char* name, ITexture* texture) = 0;
    //シェーダー入力シグニチャ記述子を取得
    virtual InputSignatureDesc inputSignature(const char* techniqueName, int passNo = 0) = 0;
};

#endif // !_IEFFECT_H_
