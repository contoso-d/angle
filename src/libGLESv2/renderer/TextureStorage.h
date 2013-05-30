//
// Copyright (c) 2002-2012 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// TextureStorage.h: Defines the abstract rx::TextureStorageInterface class and its concrete derived
// classes TextureStorageInterface2D and TextureStorageInterfaceCube, which act as the interface to the
// GPU-side texture.

#ifndef LIBGLESV2_RENDERER_TEXTURESTORAGE_H_
#define LIBGLESV2_RENDERER_TEXTURESTORAGE_H_

#include "common/debug.h"

namespace rx
{
class Renderer;
class SwapChain;
class RenderTarget;
class Blit;

class TextureStorage
{
  public:
    TextureStorage() {};
    virtual ~TextureStorage() {};

    virtual int getLodOffset() const = 0;
    virtual bool isRenderTarget() const = 0;
    virtual bool isManaged() const = 0;
    virtual int levelCount() = 0;

    virtual RenderTarget *getRenderTarget(int level) = 0;
    virtual RenderTarget *getRenderTarget(GLenum faceTarget, int level) = 0;
    virtual RenderTarget *getRenderTargetLayer(int mipLevel, int layer) = 0;
    virtual void generateMipmap(int level) = 0;
    virtual void generateMipmap(int face, int level) = 0;

  private:
    DISALLOW_COPY_AND_ASSIGN(TextureStorage);

};

class TextureStorageInterface
{
  public:
    TextureStorageInterface();
    virtual ~TextureStorageInterface();

    TextureStorage *getStorageInstance() { return mInstance; }

    unsigned int getTextureSerial() const;
    virtual unsigned int getRenderTargetSerial(GLenum target) const = 0;

    virtual int getLodOffset() const;
    virtual bool isRenderTarget() const;
    virtual bool isManaged() const;
    virtual int levelCount();

  protected:
    TextureStorage *mInstance;

  private:
    DISALLOW_COPY_AND_ASSIGN(TextureStorageInterface);

    const unsigned int mTextureSerial;
    static unsigned int issueTextureSerial();

    static unsigned int mCurrentTextureSerial;
};

class TextureStorageInterface2D : public TextureStorageInterface
{
  public:
    TextureStorageInterface2D(Renderer *renderer, SwapChain *swapchain);
    TextureStorageInterface2D(Renderer *renderer, int levels, GLenum internalformat, GLenum usage, bool forceRenderable, GLsizei width, GLsizei height);
    virtual ~TextureStorageInterface2D();

    void generateMipmap(int level);
    RenderTarget *getRenderTarget() const;

    virtual unsigned int getRenderTargetSerial(GLenum target) const;

  private:
    DISALLOW_COPY_AND_ASSIGN(TextureStorageInterface2D);

    const unsigned int mRenderTargetSerial;
};

class TextureStorageInterfaceCube : public TextureStorageInterface
{
  public:
    TextureStorageInterfaceCube(Renderer *renderer, int levels, GLenum internalformat, GLenum usage, bool forceRenderable, int size);
    virtual ~TextureStorageInterfaceCube();

    void generateMipmap(int face, int level);
    RenderTarget *getRenderTarget(GLenum faceTarget) const;

    virtual unsigned int getRenderTargetSerial(GLenum target) const;

  private:
    DISALLOW_COPY_AND_ASSIGN(TextureStorageInterfaceCube);

    const unsigned int mFirstRenderTargetSerial;
};

class TextureStorageInterface3D : public TextureStorageInterface
{
  public:
    TextureStorageInterface3D(Renderer *renderer, int levels, GLenum internalformat, GLenum usage,
                              GLsizei width, GLsizei height, GLsizei depth);
    virtual ~TextureStorageInterface3D();

    void generateMipmap(int level);

    virtual unsigned int getRenderTargetSerial(GLenum target) const;

  private:
    DISALLOW_COPY_AND_ASSIGN(TextureStorageInterface3D);
};

class TextureStorageInterface2DArray : public TextureStorageInterface
{
  public:
    TextureStorageInterface2DArray(Renderer *renderer, int levels, GLenum internalformat, GLenum usage,
                              GLsizei width, GLsizei height, GLsizei depth);
    virtual ~TextureStorageInterface2DArray();

    void generateMipmap(int level);

    virtual unsigned int getRenderTargetSerial(GLenum target) const;

  private:
    DISALLOW_COPY_AND_ASSIGN(TextureStorageInterface2DArray);
};

}

#endif // LIBGLESV2_RENDERER_TEXTURESTORAGE_H_