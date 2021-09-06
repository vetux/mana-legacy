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

#ifndef MANA_SKYBOXCOMPONENT_HPP
#define MANA_SKYBOXCOMPONENT_HPP

#include <string>

#include "runtime/ecs/component.hpp"

#include "engine/asset/assetpath.hpp"

namespace engine::runtime {
    struct SkyboxComponent : public Component {
        SkyboxComponent() : Component(SKYBOX) {}

        Component *clone() override {
            return new SkyboxComponent(*this);
        }

        const std::type_info &getTypeInfo() override {
            return typeid(SkyboxComponent);
        }

        //Paths to skybox images, using paths here means immutable skybox images
        //Mutable images would be desirable for animated skybox
        std::array<AssetPath, 6> paths;
    };
}
#endif //MANA_SKYBOXCOMPONENT_HPP
