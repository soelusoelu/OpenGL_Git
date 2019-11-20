#ifndef _IVERTEX_DECLARATION_H_
#define _IVERTEX_DECLARATION_H_

#include "VertexDeclarationDesc.h"

class IVertexDeclaration {
public:
    virtual ~IVertexDeclaration() = default;
    //�f�B�X�N���v�^�̗v�f����Ԃ�
    virtual unsigned size() const = 0;
    //�f�B�X�N���v�^�̎擾
    virtual const VertexDeclarationDesc& desc(unsigned index) const = 0;
};

#endif // !_IVERTEX_DECLARATION_H_
