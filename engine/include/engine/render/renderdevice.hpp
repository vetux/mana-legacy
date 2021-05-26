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

#ifndef MANA_RENDERDEVICE_HPP
#define MANA_RENDERDEVICE_HPP

#include <map>
#include <functional>

#include "engine/render/graphicsapi.hpp"
#include "engine/render/renderer.hpp"
#include "engine/render/renderobject.hpp"
#include "engine/render/geometry/mesh.hpp"

namespace mana {
    class RenderDevice {
    public:
        virtual ~RenderDevice() = default;

        virtual Renderer &getRenderer() = 0;

        virtual RenderTarget *createRenderTarget(Vec2i size, int samples) = 0;

        virtual TextureBuffer *createTextureBuffer(TextureBuffer::Attributes attributes) = 0;

        virtual MeshBuffer *createMeshBuffer(const Mesh &mesh) = 0;

        virtual MeshBuffer *createInstancedMeshBuffer(const Mesh &mesh, const std::vector<Transform> &offsets) = 0;

        virtual ShaderProgram *createShaderProgram(const std::string &vertexShader,
                                                   const std::string &fragmentShader,
                                                   const std::map<std::string, std::string> &macros,
                                                   const std::function<std::string(
                                                           const char *)> &includeCallback) = 0;
    };
}

#endif //MANA_RENDERDEVICE_HPP