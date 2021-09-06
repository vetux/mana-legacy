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

#ifndef MANA_GLFWRENDERTARGETGL_HPP
#define MANA_GLFWRENDERTARGETGL_HPP

#include "../../../render/opengl/oglrendertarget.hpp"

#include "../../../render/opengl/ogltypeconverter.hpp"
#include "../../../render/opengl/oglcheckerror.hpp"

namespace engine {
    namespace glfw {
        class GLFWRenderTargetGL : public opengl::OGLRenderTarget {
        public:
            GLFWwindow *wndH;
            Vec2i size;

            explicit GLFWRenderTargetGL(GLFWwindow *wndH) : wndH(wndH) {}

            Vec2i getSize() override {
                return size;
            };

            GLuint getFBO() override {
                return 0;
            };
        };
    }
}

#endif //MANA_GLFWRENDERTARGETGL_HPP