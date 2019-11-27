#ifndef _TEXTURE2D_H_
#define _TEXTURE2D_H_

#include "Texture.h"

class Texture2D : public Texture {
public:
    Texture2D(const TextureDesc& desc, const void* data = 0);

private:
    //イメージの設定
    virtual void texImage(const void* data, unsigned mipLevel, unsigned index) override;
    //イメージ更新
    virtual void texSubImage(const void* data, unsigned mipLevel, unsigned index) override;
};

#endif // !_TEXTURE2D_H_
