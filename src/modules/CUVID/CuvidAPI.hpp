/*
    QMPlay2 is a video and audio player.
    Copyright (C) 2010-2020  Błażej Szczygieł

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <cuda/CUDAQMPlayTypes.hpp>
#include <cuda/CUVIDQMPlayTypes.hpp>

#include <memory>

namespace cu {

using  cuInitType = CUresult CUDAAPI (*)(unsigned int flags);
extern cuInitType init;

using  cuDeviceGetType = CUresult CUDAAPI (*)(CUdevice *device, int ordinal);
extern cuDeviceGetType deviceGet;

using  cuCtxCreateType = CUresult CUDAAPI (*)(CUcontext *pctx, unsigned int flags, CUdevice dev);
extern cuCtxCreateType ctxCreate;

using  cuCtxPushCurrentType = CUresult CUDAAPI (*)(CUcontext ctx);
extern cuCtxPushCurrentType ctxPushCurrent;

using  cuCtxPopCurrentType = CUresult CUDAAPI (*)(CUcontext *pctx);
extern cuCtxPopCurrentType ctxPopCurrent;

using  cuMemcpyDtoHType = CUresult CUDAAPI (*)(void *dstHost, CUdeviceptr srcDevice, size_t byteCount);
extern cuMemcpyDtoHType memcpyDtoH;

using  cuMemcpy2DType = CUresult CUDAAPI (*)(const CUDA_MEMCPY2D *pCopy);
extern cuMemcpy2DType memcpy2D;

using  cuGraphicsGLRegisterImageType = CUresult CUDAAPI (*)(CUgraphicsResource *pCudaResource, quint32 image, qint32 target, unsigned int flags);
extern cuGraphicsGLRegisterImageType graphicsGLRegisterImage;

using  cuGraphicsMapResourcesType = CUresult CUDAAPI (*)(unsigned int count, CUgraphicsResource *resources, CUstream hStream);
extern cuGraphicsMapResourcesType graphicsMapResources;

using  cuGraphicsSubResourceGetMappedArrayType = CUresult CUDAAPI (*)(CUarray *pArray, CUgraphicsResource resource, unsigned int arrayIndex, unsigned int mipLevel);
extern cuGraphicsSubResourceGetMappedArrayType graphicsSubResourceGetMappedArray;

using  cuGraphicsUnmapResourcesType = CUresult CUDAAPI (*)(unsigned int count, CUgraphicsResource *resources, CUstream hStream);
extern cuGraphicsUnmapResourcesType graphicsUnmapResources;

using  cuGraphicsUnregisterResourceType = CUresult CUDAAPI (*)(CUgraphicsResource resource);
extern cuGraphicsUnregisterResourceType graphicsUnregisterResource;

using  cuCtxDestroyType = CUresult CUDAAPI (*)(CUcontext ctx);
extern cuCtxDestroyType ctxDestroy;

bool load();

std::shared_ptr<CUcontext> createContext();

class ContextGuard
{
    Q_DISABLE_COPY(ContextGuard)

public:
    ContextGuard(const std::shared_ptr<CUcontext> &ctx);
    ContextGuard(CUcontext ctx);
    ~ContextGuard();

    void unlock();

private:
    bool m_locked = true;
};

}

namespace cuvid {

using  cuvidCreateVideoParserType = CUresult CUDAAPI (*)(CUvideoparser *pObj, CUVIDPARSERPARAMS *pParams);
extern cuvidCreateVideoParserType createVideoParser;

using  cuvidDestroyVideoParserType = CUresult CUDAAPI (*)(CUvideoparser obj);
extern cuvidDestroyVideoParserType destroyVideoParser;

using  cuvidDecodePictureType = CUresult CUDAAPI (*)(CUvideodecoder hDecoder, CUVIDPICPARAMS *pPicParams);
extern cuvidDecodePictureType decodePicture;

using  cuvidCreateDecoderType = CUresult CUDAAPI (*)(CUvideodecoder *phDecoder, CUVIDDECODECREATEINFO *pdci);
extern cuvidCreateDecoderType createDecoder;

using  cuvidDestroyDecoderType = CUresult CUDAAPI (*)(CUvideodecoder hDecoder);
extern cuvidDestroyDecoderType destroyDecoder;

using  cuvidMapVideoFrameType = CUresult CUDAAPI (*)(CUvideodecoder hDecoder, int nPicIdx, quintptr *pDevPtr, unsigned int *pPitch, CUVIDPROCPARAMS *pVPP);
extern cuvidMapVideoFrameType mapVideoFrame;

using  cuvidUnmapVideoFrameType = CUresult CUDAAPI (*)(CUvideodecoder hDecoder, quintptr DevPtr);
extern cuvidUnmapVideoFrameType unmapVideoFrame;

using  cuvidParseVideoDataType = CUresult CUDAAPI (*)(CUvideoparser obj, CUVIDSOURCEDATAPACKET *pPacket);
extern cuvidParseVideoDataType parseVideoData;

bool load();

}