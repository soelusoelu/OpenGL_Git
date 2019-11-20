#ifndef _ITEXTURE_H_
#define _ITEXTURE_H_

#include "TextureDesc.h"

class ITexture {
public:
    virtual ~ITexture() = default;
    //ディスクリプタの取得
    virtual const TextureDesc& desc() const = 0;
    //データの設定
    virtual void setData(const void* data) = 0;
    //データの取得
    virtual void getData(void* data) = 0;
    //イメージサイズの取得
    virtual unsigned int size() const = 0;
};

#endif // !_ITEXTURE_H_
