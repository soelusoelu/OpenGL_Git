#ifndef _IBUFFER_H_
#define _IBUFFER_H_

#include "BufferDesc.h"

class IBuffer {
public:
    virtual ~IBuffer() = default;
    //ディスクリプタの取得
    virtual const BufferDesc& desc() const = 0;
    //データの設定
    virtual void setData(const void* data) = 0;
    //データの取得
    virtual void getData(void* data) const = 0;
};

#endif // !_IBUFFER_H_
