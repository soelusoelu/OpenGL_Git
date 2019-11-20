#include "VertexDeclaration.h"
#include "VertexStreamDesc.h"
#include "Buffer.h"

VertexDeclaration::VertexDeclaration(const VertexDeclarationDesc desc[], unsigned numDesc) :
    mDesc(&desc[0], &desc[numDesc]),
    mElements(numDesc) {
    for (unsigned i = 0; i < numDesc; i++) {
        mElements[i] = toElement(mDesc[i]);
    }
}

unsigned VertexDeclaration::size() const {
    return static_cast<unsigned>(mDesc.size());
}

const VertexDeclarationDesc& VertexDeclaration::desc(unsigned index) const {
    return mDesc[index];
}

void VertexDeclaration::setVertexStream(const VertexStreamDesc streams[], unsigned start) {
    //頂点ストリームのリセット
    resetVertexStream();
    //頂点バッファを設定
    for (auto&& e : mElements) {
        setVertexBuffer(e, streams[e.stream], start);
    }
}

void VertexDeclaration::resetVertexStream() {
    //頂点配列を無効にする
    for (GLuint attr = 0; attr < VERTEX_DECLARATION_MAX; ++attr) {
        glDisableVertexAttribArray(attr);
    }
}

void VertexDeclaration::setVertexBuffer(const Element& element, const VertexStreamDesc& stream, unsigned start) {
    //頂点バッファをバインド
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, reinterpret_cast<Buffer*>(stream.buffer)->buffer());
    //頂点データを有効化
    glEnableVertexAttribArrayARB(element.attrib);
    //頂点バッファを設定
    GLubyte* base = 0;
    glVertexAttribPointerARB(
        element.attrib,
        element.format.size,
        element.format.type,
        element.format.normalized,
        stream.stride,
        &base[start * stream.stride + stream.offset + element.offset]
    );
    //頂点バッファのバインドを解除
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
}

VertexDeclaration::Element VertexDeclaration::toElement(const VertexDeclarationDesc& desc) {
    Element element;
    element.attrib = toAttrib(desc.semantic) + desc.index;
    element.format = toVertexFormat(desc.type);
    element.offset = desc.offset;
    element.stream = desc.stream;
    return element;
}

GLuint VertexDeclaration::toAttrib(VertexSemantic semantic) {
    static const unsigned attribs[] = {
        0, //VERTEX_SEMANTIC_POSITION = 0
        1, //VERTEX_SEMANTIC_BLENDWEIGHT = 1
        2, //VERTEX_SEMANTIC_NORMAL = 2
        3, //VERTEX_SEMANTIC_COLOR = 3
        3, //VERTEX_SEMANTIC_DIFFUSE = 4
        4, //VERTEX_SEMANTIC_SPECULAR = 5
        5, //VERTEX_SEMANTIC_TESSFACTOR = 6
        5, //VERTEX_SEMANTIC_FOGCOORD = 7
        6, //VERTEX_SEMANTIC_PSIZE = 8
        7, //VERTEX_SEMANTIC_BLENDINDICES = 9
        8, //VERTEX_SEMANTIC_TEXCOORD = 10
        14,//VERTEX_SEMANTIC_TANGENT = 11
        15 //VERTEX_SEMANTIC_BINORMAL = 12
    };
    return attribs[static_cast<int>(semantic)];
}

const VertexDeclaration::VertexFormat& VertexDeclaration::toVertexFormat(VertexType type) {
    static const VertexFormat vertexFormats[] = {
        { GL_FLOAT,          1, GL_FALSE }, //VERTEX_TYPE_FLOAT1 = 0
        { GL_FLOAT,          2, GL_FALSE }, //VERTEX_TYPE_FLOAT2 = 1
        { GL_FLOAT,          3, GL_FALSE }, //VERTEX_TYPE_FLOAT3 = 2
        { GL_FLOAT,          4, GL_FALSE }, //VERTEX_TYPE_FLOAT4 = 3
        { GL_BYTE,           4, GL_FALSE }, //VERTEX_TYPE_BYTE4 = 4
        { GL_BYTE,           4, GL_TRUE },  //VERTEX_TYPE_BYTE4N = 5
        { GL_UNSIGNED_BYTE,  4, GL_FALSE }, //VERTEX_TYPE_UBYTE4 = 6
        { GL_UNSIGNED_BYTE,  4, GL_TRUE },  //VERTEX_TYPE_UBYTE4N = 7
        { GL_SHORT,          2, GL_FALSE }, //VERTEX_TYPE_SHORT2 = 8
        { GL_SHORT,          2, GL_TRUE },  //VERTEX_TYPE_SHORT2N = 9
        { GL_UNSIGNED_SHORT, 2, GL_FALSE }, //VERTEX_TYPE_USHORT2 = 10
        { GL_UNSIGNED_SHORT, 2, GL_TRUE },  //VERTEX_TYPE_USHORT2N = 11
        { GL_SHORT,          4, GL_FALSE }, //VERTEX_TYPE_SHORT4 = 12
        { GL_SHORT,          4, GL_TRUE },  //VERTEX_TYPE_SHORT4N = 13
        { GL_UNSIGNED_SHORT, 4, GL_FALSE }, //VERTEX_TYPE_USHORT4 = 14
        { GL_UNSIGNED_SHORT, 4, GL_TRUE },  //VERTEX_TYPE_USHORT4N = 15
        { GL_INT,            1, GL_FALSE }, //VERTEX_TYPE_INT1 = 16
        { GL_INT,            2, GL_FALSE }, //VERTEX_TYPE_INT2 = 17
        { GL_INT,            3, GL_FALSE }, //VERTEX_TYPE_INT3 = 18
        { GL_INT,            4, GL_FALSE }, //VERTEX_TYPE_INT4 = 19
        { GL_UNSIGNED_INT,   1, GL_FALSE }, //VERTEX_TYPE_UINT1 = 20
        { GL_UNSIGNED_INT,   2, GL_FALSE }, //VERTEX_TYPE_UINT2 = 21
        { GL_UNSIGNED_INT,   3, GL_FALSE }, //VERTEX_TYPE_UINT3 = 22
        { GL_UNSIGNED_INT,   4, GL_FALSE }, //VERTEX_TYPE_UINT4 = 23
    };
    return vertexFormats[static_cast<int>(type)];
}
