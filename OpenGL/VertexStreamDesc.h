#ifndef _VERTEX_STREAM_DESC_H_
#define _VERTEX_STREAM_DESC_H_

class IBuffer;

struct VertexStreamDesc {
    //頂点バッファ
    IBuffer* buffer;
    //オフセット
    unsigned offset;
    //ストライド
    unsigned stride;

    VertexStreamDesc() :
        buffer(0),
        offset(0),
        stride(0) {
    }
};

#endif // !_VERTEX_STREAM_DESC_H_
