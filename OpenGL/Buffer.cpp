#include "Buffer.h"

Buffer::Buffer(const BufferDesc& desc, const void* data) :
    mDesc(desc),
    mTarget(toTarget(desc.type)),
    mUsage(toUsage(desc.usage)) {
    //バッファの作成
    glGenBuffersARB(1, &mBuffer);
    glBindBufferARB(mTarget, mBuffer);
    glBufferDataARB(mTarget, mDesc.size, data, mUsage);
    glBindBufferARB(mTarget, 0);
}

Buffer::~Buffer() {
    //バッファを削除
    glDeleteBuffersARB(1, &mBuffer);
}

const BufferDesc& Buffer::desc() const {
    return mDesc;
}

void Buffer::setData(const void* data) {
    glBindBufferARB(mTarget, mBuffer);
    glBufferSubDataARB(mTarget, 0, mDesc.size, data);
    glBindBufferARB(mTarget, 0);
}

void Buffer::getData(void* data) const {
    glBindBufferARB(mTarget, mBuffer);
    glGetBufferSubDataARB(mTarget, 0, mDesc.size, data);
    glBindBufferARB(mTarget, 0);
}

GLuint Buffer::buffer() const {
    return mBuffer;
}

GLenum Buffer::toTarget(BufferType type) {
    static const GLenum targets[] = {
        GL_ARRAY_BUFFER_ARB,        //BUFFER_TYPE_VERTEX = 0
        GL_ELEMENT_ARRAY_BUFFER_ARB //BUFFER_TYPE_INDEX = 1
    };
    return targets[static_cast<int>(type)];
}

GLenum Buffer::toUsage(BufferUsage usage) {
    static const GLenum usages[] = {
        GL_STREAM_DRAW, //BUFFER_USAGE_DEFAULT = 0
        GL_STATIC_DRAW, //BUFFER_USAGE_IMMUTABLE = 1
        GL_DYNAMIC_DRAW //BUFFER_USAGE_DYNAMIC = 2
    };
    return usages[static_cast<int>(usage)];
}
