#ifndef _VERTEX_DECLARATION_H_
#define _VERTEX_DECLARATION_H_

#include "IVertexDeclaration.h"
#include "VertexStreamDesc.h"
#include "OpenGL.h"
#include <vector>

class VertexDeclaration : public IVertexDeclaration {
public:
    VertexDeclaration(const VertexDeclarationDesc desc[], unsigned numDesc);
    //ディスクリプタの要素数を返す
    virtual unsigned size() const override;
    //ディスクリプタの取得
    virtual const VertexDeclarationDesc& desc(unsigned index) const override;

    //頂点バッファストリームの設定
    void setVertexStream(const VertexStreamDesc streams[], unsigned start = 0);
    //頂点バッファストリームのリセット
    void resetVertexStream();

private:
    //頂点フォーマット
    struct VertexFormat {
        GLuint type;
        GLint size;
        GLboolean normalized;
    };
    //頂点宣言要素
    struct Element {
        GLuint attrib;
        VertexFormat format;
        GLuint offset;
        unsigned stream;
    };
    //頂点バッファの設定
    void setVertexBuffer(const Element& element, const VertexStreamDesc& stream, unsigned start);
    //ディスクリプタを変換
    static Element toElement(const VertexDeclarationDesc& desc);
    //セマンティックを変換
    static GLuint toAttrib(VertexSemantic semantic);
    //頂点タイプを変換
    static const VertexFormat& toVertexFormat(VertexType type);

private:
    //ディスクリプタ配列
    using VertexDeclarationDescArray = std::vector<VertexDeclarationDesc>;
    //頂点宣言配列
    using VertexDeclarationArray = std::vector<Element>;

    //ディスクリプタ配列
    VertexDeclarationDescArray mDesc;
    //頂点宣言配列
    VertexDeclarationArray mElements;
};

#endif // !_VERTEX_DECLARATION_H_
