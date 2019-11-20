#ifndef _BUFFER_DESC_H_
#define _BUFFER_DESC_H_

//バッファタイプ
enum class BufferType {
    BUFFER_TYPE_VERTEX, //頂点バッファ
    BUFFER_TYPE_INDEX //インデックスバッファ
};

enum class BufferUsage {
    BUFFER_USAGE_DEFAULT,
    BUFFER_USAGE_IMMUTABLE,
    BUFFER_USAGE_DYNAMIC
};

struct BufferDesc {
    //バッファタイプ
    BufferType type;
    //バッファの使用方法
    BufferUsage usage;
    //データのバイト数
    unsigned size;
    //コンストラクタ
    BufferDesc() :
        type(BufferType::BUFFER_TYPE_VERTEX),
        usage(BufferUsage::BUFFER_USAGE_IMMUTABLE),
        size(0) {
    }
};

#endif // !_BUFFER_DESC_H_
