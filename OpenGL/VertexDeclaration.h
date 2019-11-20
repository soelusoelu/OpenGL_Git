#ifndef _VERTEX_DECLARATION_H_
#define _VERTEX_DECLARATION_H_

#include "IVertexDeclaration.h"
#include "VertexStreamDesc.h"
#include "OpenGL.h"
#include <vector>

class VertexDeclaration : public IVertexDeclaration {
public:
    VertexDeclaration(const VertexDeclarationDesc desc[], unsigned numDesc);
    //�f�B�X�N���v�^�̗v�f����Ԃ�
    virtual unsigned size() const override;
    //�f�B�X�N���v�^�̎擾
    virtual const VertexDeclarationDesc& desc(unsigned index) const override;

    //���_�o�b�t�@�X�g���[���̐ݒ�
    void setVertexStream(const VertexStreamDesc streams[], unsigned start = 0);
    //���_�o�b�t�@�X�g���[���̃��Z�b�g
    void resetVertexStream();

private:
    //���_�t�H�[�}�b�g
    struct VertexFormat {
        GLuint type;
        GLint size;
        GLboolean normalized;
    };
    //���_�錾�v�f
    struct Element {
        GLuint attrib;
        VertexFormat format;
        GLuint offset;
        unsigned stream;
    };
    //���_�o�b�t�@�̐ݒ�
    void setVertexBuffer(const Element& element, const VertexStreamDesc& stream, unsigned start);
    //�f�B�X�N���v�^��ϊ�
    static Element toElement(const VertexDeclarationDesc& desc);
    //�Z�}���e�B�b�N��ϊ�
    static GLuint toAttrib(VertexSemantic semantic);
    //���_�^�C�v��ϊ�
    static const VertexFormat& toVertexFormat(VertexType type);

private:
    //�f�B�X�N���v�^�z��
    using VertexDeclarationDescArray = std::vector<VertexDeclarationDesc>;
    //���_�錾�z��
    using VertexDeclarationArray = std::vector<Element>;

    //�f�B�X�N���v�^�z��
    VertexDeclarationDescArray mDesc;
    //���_�錾�z��
    VertexDeclarationArray mElements;
};

#endif // !_VERTEX_DECLARATION_H_
