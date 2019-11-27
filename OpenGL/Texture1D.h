#ifndef _TEXTURE1D_H_
#define _TEXTURE1D_H_

#include "Texture.h"

class Texture1D : public Texture {
public:
    Texture1D(const TextureDesc& desc, const void* data = 0);

private:
    //イメージの設定
    virtual void texImage(const void* data, unsigned mipLevel, unsigned index) override;
    //イメージの更新
    virtual void texSubImage(const void* data, unsigned mipLevel, unsigned index) override;
};

#endif // !_TEXTURE1D_H_
