#ifndef _TEXTURE2D_H_
#define _TEXTURE2D_H_

#include "Texture.h"

class Texture2D : public Texture {
public:
    Texture2D(const TextureDesc& desc, const void* data = 0);

private:
    //�C���[�W�̐ݒ�
    virtual void texImage(const void* data, unsigned mipLevel, unsigned index) override;
    //�C���[�W�X�V
    virtual void texSubImage(const void* data, unsigned mipLevel, unsigned index) override;
};

#endif // !_TEXTURE2D_H_
