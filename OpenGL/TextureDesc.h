#ifndef _TEXTURE_DESC_H_
#define _TEXTURE_DESC_H_

//テクスチャの種類
enum class TextureType {
    TEXTURE_TYPE_1D,
    TEXTURE_TYPE_2D,
    TEXTURE_TYPE_3D,
    TEXTURE_TYPE_CUBE
};

//テクスチャフォーマット
enum class TextureFormat {
    TEXTURE_FORMAT_I8,
    TEXTURE_FORMAT_IA8,
    TEXTURE_FORMAT_RGBA8,
    TEXTURE_FORMAT_I16,
    TEXTURE_FORMAT_IA16,
    TEXTURE_FORMAT_RGBA16,
    TEXTURE_FORMAT_I16F,
    TEXTURE_FORMAT_IA16F,
    TEXTURE_FORMAT_RGBA16F,
    TEXTURE_FORMAT_I32F,
    TEXTURE_FORMAT_IA32F,
    TEXTURE_FORMAT_RGB32F,
    TEXTURE_FORMAT_RGBA32F,
    TEXTURE_FORMAT_R11G11B10F,
    TEXTURE_FORMAT_DXT1,
    TEXTURE_FORMAT_DXT3,
    TEXTURE_FORMAT_DXT5,
    TEXTURE_FORMAT_D16,
    TEXTURE_FORMAT_D32F,
    TEXTURE_FORMAT_D24S8,
};

//テクスチャの使用方法
enum class TextureUsage {
    TEXTURE_USAGE_DEFAULT,
    TEXTURE_USAGE_IMMUTABLE,
    TEXTURE_USAGE_DYNAMIC
};

//テクスチャ作成ディスクリプタ
struct TextureDesc {
    //テクスチャタイプ
    TextureType type;
    //テクスチャフォーマット
    TextureFormat format;
    //幅
    unsigned width;
    //高さ
    unsigned height;
    //深さ
    unsigned depth;
    //ミップマップレベル
    unsigned mipLevels;
    //バッファの利用方法
    TextureUsage usage;
    //レンダーターゲットに使用するか
    bool renderTarget;

    TextureDesc() :
        type(TextureType::TEXTURE_TYPE_2D),
        format(TextureFormat::TEXTURE_FORMAT_RGBA8),
        width(1),
        height(1),
        depth(1),
        mipLevels(1),
        usage(TextureUsage::TEXTURE_USAGE_DEFAULT),
        renderTarget(false) {
    }
};

#endif // !_TEXTURE_DESC_H_
