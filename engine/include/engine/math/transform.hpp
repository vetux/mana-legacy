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

#ifndef MANA_TRANSFORM_HPP
#define MANA_TRANSFORM_HPP

#include "engine/math/vector3.hpp"
#include "engine/math/quaternion.hpp"
#include "engine/math/matrixmath.hpp"

namespace engine {
    struct Transform {
        Vec3f position;
        Quaternion rotation;
        Vec3f scale = Vec3f(1);

        Transform() = default;

        Transform(Vec3f position, Vec3f rotation, Vec3f scale) : position(position),
                                                                 rotation(rotation),
                                                                 scale(scale) {}

        Transform(Vec3f position, Quaternion rotation, Vec3f scale) : position(position),
                                                                      rotation(rotation),
                                                                      scale(scale) {}

        Transform &operator+=(const Transform &other) {
            position += other.position;
            rotation = other.rotation * rotation;
            scale += other.scale;
            return *this;
        }

        Vec3f rotate(Vec3f vec) const {
            Vec4f ret = MatrixMath::inverse(rotation.matrix()) * Vec4f(vec.x, vec.y, vec.z, 1);
            return Vec3f(ret.x, ret.y, ret.z);
        }

        Mat4f model() const {
            Mat4f model = MatrixMath::translate(position);
            model = model * MatrixMath::scale(scale);
            model = model * rotation.matrix();
            return model;
        }
    };
}

#endif //MANA_TRANSFORM_HPP
