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

#ifndef MANA_RENDERER3D_HPP
#define MANA_RENDERER3D_HPP

#include <utility>
#include <map>
#include <typeindex>

#include "engine/render/renderer.hpp"
#include "engine/render/renderdevice.hpp"
#include "engine/render/shadercompiler.hpp"

#include "scene.hpp"
#include "renderpass.hpp"
#include "compositor.hpp"

namespace engine {
    class Renderer3D {
    public:
        explicit Renderer3D(RenderDevice &device);

        ~Renderer3D();

        void render(RenderTarget &target, Scene &scene);

        GeometryBuffer &getGeometryBuffer();

        Compositor &getCompositor();

        template<typename T>
        T &getRenderPass() {
            return dynamic_cast<T &>(*passes.at(typeid(T)).get());
        }

        template<typename T>
        void addRenderPass(std::unique_ptr<T> ptr) {
            auto& pass = dynamic_cast<RenderPass &>(*ptr);
            pass.prepareBuffer(geometryBuffer);

            passOrder.emplace_back(typeid(T));
            passes[typeid(T)] = std::move(ptr);
        }

        void clearRenderPasses();

    private:
        std::vector<std::type_index> passOrder;
        std::map<std::type_index, std::unique_ptr<RenderPass>> passes;

        GeometryBuffer geometryBuffer;
        Compositor compositor;
    };
}

#endif //MANA_RENDERER3D_HPP
