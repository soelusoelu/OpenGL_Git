#ifndef _TEXTURE3D_H_
#define _TEXTURE3D_H_

#include "Texture.h"

class Texture3D : public Texture {
public:
    Texture3D(const TextureDesc& desc, const void* data = 0);

private:
    virtual void texImage(const void* data, unsigned mipLevel, unsigned index) override;
    virtual void texSubImage(const void* data, unsigned mipLevel, unsigned index) override;
};

#endif // !_TEXTURE3D_H_
