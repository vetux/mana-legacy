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

#ifndef MANA_RIGIDBODYCOMPONENT2D_HPP
#define MANA_RIGIDBODYCOMPONENT2D_HPP

#include "runtime/ecs/component.hpp"

#include "engine/physics/2d/rigidbody2d.hpp"

namespace engine::runtime {
    struct RigidBodyComponent2D : public Component {
        RigidBodyComponent2D() : Component(RIGIDBODY_2D) {}

        Component *clone() override {
            return new RigidBodyComponent2D(*this);
        }

        const std::type_info &getTypeInfo() override {
            return typeid(RigidBodyComponent2D);
        }

        RigidBody2D::RigidBodyType type;
    };
}

#endif //MANA_RIGIDBODYCOMPONENT2D_HPP
