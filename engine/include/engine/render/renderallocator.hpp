/**
 *  Mana - 3D Engine
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

#ifndef MANA_RENDERALLOCATOR_HPP
#define MANA_RENDERALLOCATOR_HPP

#include "engine/render/geometry/mesh.hpp"
#include "engine/render/framebuffer.hpp"
#include "engine/render/textureattributes.hpp"
#include "engine/render/rendermesh.hpp"
#include "engine/render/shaderprogram.hpp"
#include "engine/math/transform.hpp"

namespace mana {
    class RenderAllocator {
    public:
        virtual FrameBuffer *allocateFrameBuffer(int width,
                                                 int height,
                                                 TextureAttributes colorBufferProperties = {}) = 0;

        virtual RenderTexture *allocateTexture(int width,
                                               int height,
                                               TextureAttributes properties = {}) = 0;

        virtual RenderTexture *allocateCubeMapTexture(int width,
                                                      int height,
                                                      TextureAttributes properties = {}) = 0;

        virtual RenderMesh *allocateMesh(const Mesh &mesh) = 0;

        virtual RenderMesh *allocateInstancedMesh(const Mesh &mesh,
                                                           const std::vector<Transform> &offsets = {}) = 0;

        virtual ShaderProgram *allocateShaderProgram(std::string vertexShader, std::string fragmentShader) = 0;
    };
}

#endif //MANA_RENDERALLOCATOR_HPP
