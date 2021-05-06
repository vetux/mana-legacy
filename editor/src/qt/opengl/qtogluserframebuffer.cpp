/**
 *  Mana - 3D Game Engine
 *  Copyright (C) 2021  Julian Zampiccoli
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "qtogluserframebuffer.hpp"
#include "qtogltypeconverter.hpp"
#include "qtoglcheckerror.hpp"
#include "qtoglrendertexture.hpp"

using namespace mana;
using namespace mana::opengl;

opengl::QtOGLUserFrameBuffer::QtOGLUserFrameBuffer() : FBO(0),
                                                   width(0),
                                                   height(0)
                                                   {}

opengl::QtOGLUserFrameBuffer::QtOGLUserFrameBuffer(int width, int height) : width(width),
                                                                        height(height),
                                                                        FBO(0)
                                                                        {}

opengl::QtOGLUserFrameBuffer::~QtOGLUserFrameBuffer() {
    if (deleteFramebuffer)
        glDeleteFramebuffers(1, &FBO);
}

Vec2i opengl::QtOGLUserFrameBuffer::getSize() const {
    return {width, height};
}

void opengl::QtOGLUserFrameBuffer::blitColor(const RenderTarget &source, Vec2i sourceOffset, Vec2i targetOffset,
                                           Vec2i sourceRect, Vec2i targetRect, TextureBuffer::TextureFiltering filter) {
    if (sourceRect.x < 0 || sourceRect.y < 0) {
        throw std::runtime_error("Rect cannot be negative");
    }
    if (sourceOffset.x < 0 || sourceOffset.y < 0) {
        throw std::runtime_error("Offset cannot be negative");
    }
    if (targetRect.x < 0 || targetRect.y < 0) {
        throw std::runtime_error("Rect cannot be negative");
    }
    if (targetOffset.x < 0 || targetOffset.y < 0) {
        throw std::runtime_error("Offset cannot be negative");
    }

    auto &fbS = dynamic_cast<const QtOGLFrameBuffer &>(source);

    Vec2i sourceSize = fbS.getSize();
    if (sourceSize.x < sourceRect.x + sourceOffset.x || sourceSize.y < sourceRect.y + sourceOffset.y)
        throw std::runtime_error("Blit rect out of bounds for source framebuffer");

    Vec2i targetSize = getSize();
    if (targetSize.x < targetRect.x + targetOffset.x || targetSize.y < targetRect.y + targetOffset.y)
        throw std::runtime_error("Blit rect out of bounds for target framebuffer.");

    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbS.getFBO());
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, getFBO());
    glBlitFramebuffer(sourceOffset.x,
                      sourceOffset.y,
                      sourceRect.x,
                      sourceRect.y,
                      targetOffset.x,
                      targetOffset.y,
                      targetRect.x,
                      targetRect.y,
                      GL_COLOR_BUFFER_BIT,
                      QtOGLTypeConverter::convert(filter));
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    checkQtGLError("QtOGLUserFrameBuffer::blitFramebuffer");
}

void opengl::QtOGLUserFrameBuffer::blitDepth(const RenderTarget &source, Vec2i sourceOffset, Vec2i targetOffset,
                                           Vec2i sourceRect, Vec2i targetRect, TextureBuffer::TextureFiltering filter) {
    if (sourceRect.x < 0 || sourceRect.y < 0) {
        throw std::runtime_error("Rect cannot be negative");
    }
    if (sourceOffset.x < 0 || sourceOffset.y < 0) {
        throw std::runtime_error("Offset cannot be negative");
    }
    if (targetRect.x < 0 || targetRect.y < 0) {
        throw std::runtime_error("Rect cannot be negative");
    }
    if (targetOffset.x < 0 || targetOffset.y < 0) {
        throw std::runtime_error("Offset cannot be negative");
    }

    auto &fbS = dynamic_cast<const QtOGLFrameBuffer &>(source);

    Vec2i sourceSize = fbS.getSize();
    if (sourceSize.x < sourceRect.x + sourceOffset.x || sourceSize.y < sourceRect.y + sourceOffset.y)
        throw std::runtime_error("Blit rect out of bounds for source framebuffer");

    Vec2i targetSize = getSize();
    if (targetSize.x < targetRect.x + targetOffset.x || targetSize.y < targetRect.y + targetOffset.y)
        throw std::runtime_error("Blit rect out of bounds for target framebuffer.");

    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbS.getFBO());
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, getFBO());
    glBlitFramebuffer(sourceOffset.x,
                      sourceOffset.y,
                      sourceRect.x,
                      sourceRect.y,
                      targetOffset.x,
                      targetOffset.y,
                      targetRect.x,
                      targetRect.y,
                      GL_DEPTH_BUFFER_BIT,
                      QtOGLTypeConverter::convert(filter));
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    checkQtGLError("QtOGLUserFrameBuffer::blitFramebuffer");
}

void opengl::QtOGLUserFrameBuffer::blitStencil(const RenderTarget &source, Vec2i sourceOffset, Vec2i targetOffset,
                                             Vec2i sourceRect, Vec2i targetRect, TextureBuffer::TextureFiltering filter) {
    if (sourceRect.x < 0 || sourceRect.y < 0) {
        throw std::runtime_error("Rect cannot be negative");
    }
    if (sourceOffset.x < 0 || sourceOffset.y < 0) {
        throw std::runtime_error("Offset cannot be negative");
    }
    if (targetRect.x < 0 || targetRect.y < 0) {
        throw std::runtime_error("Rect cannot be negative");
    }
    if (targetOffset.x < 0 || targetOffset.y < 0) {
        throw std::runtime_error("Offset cannot be negative");
    }

    auto &fbS = dynamic_cast<const QtOGLFrameBuffer &>(source);

    Vec2i sourceSize = fbS.getSize();
    if (sourceSize.x < sourceRect.x + sourceOffset.x || sourceSize.y < sourceRect.y + sourceOffset.y)
        throw std::runtime_error("Blit rect out of bounds for source framebuffer");

    Vec2i targetSize = getSize();
    if (targetSize.x < targetRect.x + targetOffset.x || targetSize.y < targetRect.y + targetOffset.y)
        throw std::runtime_error("Blit rect out of bounds for target framebuffer.");

    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbS.getFBO());
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, getFBO());
    glBlitFramebuffer(sourceOffset.x,
                      sourceOffset.y,
                      sourceRect.x,
                      sourceRect.y,
                      targetOffset.x,
                      targetOffset.y,
                      targetRect.x,
                      targetRect.y,
                      GL_STENCIL_BUFFER_BIT,
                      QtOGLTypeConverter::convert(filter));
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    checkQtGLError("QtOGLUserFrameBuffer::blitFramebuffer");
}

void opengl::QtOGLUserFrameBuffer::attachColor(const TextureBuffer &texture) {
    auto &tex = dynamic_cast<const QtOGLRenderTexture &>(texture);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex.handle, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    checkQtGLError("");
}

void opengl::QtOGLUserFrameBuffer::attachDepth(const TextureBuffer &texture) {
    auto &tex = dynamic_cast<const QtOGLRenderTexture &>(texture);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex.handle, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    checkQtGLError("");
}

void opengl::QtOGLUserFrameBuffer::attachStencil(const TextureBuffer &texture) {
    auto &tex = dynamic_cast<const QtOGLRenderTexture &>(texture);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, tex.handle, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    checkQtGLError("");
}

void opengl::QtOGLUserFrameBuffer::attachDepthStencil(const TextureBuffer &texture) {
    auto &tex = dynamic_cast<const QtOGLRenderTexture &>(texture);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, tex.handle, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    checkQtGLError("");
}

void opengl::QtOGLUserFrameBuffer::attachColor(TextureBuffer::CubeMapFace face, const TextureBuffer &texture) {
    auto &tex = dynamic_cast<const QtOGLRenderTexture &>(texture);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, QtOGLTypeConverter::convert(face), tex.handle, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    checkQtGLError("");
}

void opengl::QtOGLUserFrameBuffer::attachDepth(TextureBuffer::CubeMapFace face, const TextureBuffer &texture) {
    auto &tex = dynamic_cast<const QtOGLRenderTexture &>(texture);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, QtOGLTypeConverter::convert(face), tex.handle, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    checkQtGLError("");
}

void opengl::QtOGLUserFrameBuffer::attachStencil(TextureBuffer::CubeMapFace face, const TextureBuffer &texture) {
    auto &tex = dynamic_cast<const QtOGLRenderTexture &>(texture);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, QtOGLTypeConverter::convert(face), tex.handle, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    checkQtGLError("");
}

void opengl::QtOGLUserFrameBuffer::attachDepthStencil(TextureBuffer::CubeMapFace face,
                                                    const TextureBuffer &texture) {
    auto &tex = dynamic_cast<const QtOGLRenderTexture &>(texture);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, QtOGLTypeConverter::convert(face), tex.handle, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    checkQtGLError("");
}

GLuint opengl::QtOGLUserFrameBuffer::getFBO() const {
    return FBO;
}
