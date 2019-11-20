#ifndef _IVERTEX_DECLARATION_H_
#define _IVERTEX_DECLARATION_H_

#include "VertexDeclarationDesc.h"

//頂点宣言インターフェース
class IVertexDeclaration {
public:
    virtual ~IVertexDeclaration() = default;
    //ディスクリプタの要素数を返す
    virtual unsigned size() const = 0;
    //ディスクリプタの取得
    virtual const VertexDeclarationDesc& desc(unsigned int index) const = 0;
};

#endif // !_IVERTEX_DECLARATION_H_