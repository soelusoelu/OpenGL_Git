#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "IBuffer.h"
#include "OpenGL.h"

class Buffer : public IBuffer {
public:
    Buffer(const BufferDesc& desc, const void* data = 0);
    virtual ~Buffer();
    //ディスクリプタの取得
    virtual const BufferDesc& desc() const override;
    //データの設定
    virtual void setData(const void* data) override;
    //データの取得
    virtual void getData(void* data) const override;
    //バッファの取得
    GLuint buffer() const;

private:
    //バッファのタイプを変換
    static GLenum toTarget(BufferType type);
    //バッファの使用方法を変換
    static GLenum toUsage(BufferUsage usage);

    //コピー禁止
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

private:
    //ディスクリプタ
    BufferDesc mDesc;
    //バッファオブジェクト
    GLuint mBuffer;
    //ターゲット
    GLenum mTarget;
    //使用方法
    GLenum mUsage;
};

#endif // !_BUFFER_H_
