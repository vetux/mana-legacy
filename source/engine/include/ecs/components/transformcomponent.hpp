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

#ifndef MANA_TRANSFORMCOMPONENT_HPP
#define MANA_TRANSFORMCOMPONENT_HPP

#include "math/transform.hpp"

#include <string>

#include "ecs/entitymanager.hpp"

namespace engine {
    struct Scene;

    struct MANA_EXPORT TransformComponent {
        static Transform walkHierarchy(const TransformComponent &component, EntityManager &entityManager);

        bool enabled = true;
        Transform transform;
        std::string parent; //The name of the parent transform entity
    };
}

#endif //MANA_TRANSFORMCOMPONENT_HPP