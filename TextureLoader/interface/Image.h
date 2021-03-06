/*     Copyright 2015-2019 Egor Yusov
 *  
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF ANY PROPRIETARY RIGHTS.
 *
 *  In no event and under no legal theory, whether in tort (including negligence), 
 *  contract, or otherwise, unless required by applicable law (such as deliberate 
 *  and grossly negligent acts) or agreed to in writing, shall any Contributor be
 *  liable for any damages, including any direct, indirect, special, incidental, 
 *  or consequential damages of any character arising as a result of this License or 
 *  out of the use or inability to use the software (including but not limited to damages 
 *  for loss of goodwill, work stoppage, computer failure or malfunction, or any and 
 *  all other commercial damages or losses), even if such Contributor has been advised 
 *  of the possibility of such damages.
 */

#pragma once

#include "../../../DiligentCore/Primitives/interface/FileStream.h"
#include "../../../DiligentCore/Primitives/interface/DataBlob.h"
#include "../../../DiligentCore/Common/interface/RefCntAutoPtr.h"
#include "../../../DiligentCore/Common/interface/ObjectBase.h"

namespace Diligent
{
    /// Image file format
    enum class EImageFileFormat
    {
        /// Unknown format
        unknown = 0,

        /// The image is encoded in JPEG format
        jpeg,

        /// The image is encoded in PNG format
        png,

        /// The image is encoded in TIFF format
        tiff
    };

    /// Image loading information
    struct ImageLoadInfo
    {
        /// Image file format
        EImageFileFormat Format = EImageFileFormat::unknown;
    };

    /// Image description
    struct ImageDesc
    {
        /// Image width in pixels
        Uint32 Width = 0;

        /// Image height in pixels
        Uint32 Height = 0;

        /// Bits per pixel
        Uint32 BitsPerPixel = 0;

        /// Number of color components
        Uint32 NumComponents = 0;

        /// Image row stride in bytes
        Uint32 RowStride = 0;
    };

    /// Implementation of a 2D image
    class Image : public ObjectBase<IObject>
    {
    public:
        typedef ObjectBase<IObject> TBase;

        /// Creates a new image from the data blob

        /// \param [in] pFileData - Pointer to the data blob containing image data
        /// \param [in] LoadInfo - Image loading information
        /// \param [out] ppImage - Memory location where pointer to the created image is written.
        ///                        The image should be released via Release().
        static void CreateFromDataBlob(IDataBlob *pFileData,
                                       const ImageLoadInfo& LoadInfo,
                                       Image **ppImage);

        /// Returns image description
        const ImageDesc &GetDesc(){ return m_Desc; }

        /// Returns a pointer to the image data
        IDataBlob *GetData(){ return m_pData; }

    private:
        template<typename AllocatorType, typename ObjectType>
        friend class MakeNewRCObj;

        Image(IReferenceCounters *pRefCounters,
              IDataBlob *pFileData,
              const ImageLoadInfo& LoadInfo);

        void LoadPngFile( IDataBlob *pFileData, const ImageLoadInfo& LoadInfo );
        void LoadTiffFile( IDataBlob *pFileData,const ImageLoadInfo& LoadInfo );
        void LoadJpegFile( IDataBlob *pFileData,const ImageLoadInfo& LoadInfo );
    
        ImageDesc m_Desc;
        RefCntAutoPtr<IDataBlob> m_pData;
    };
}
