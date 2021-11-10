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

#ifndef MANA_GLFWWINDOWGL_HPP
#define MANA_GLFWWINDOWGL_HPP

#include <set>

#include "../../../extern/glad.h"

#include "engine/display/window.hpp"
#include "engine/display/windowattributes.hpp"

#include "../../../render/opengl/oglrenderdevice.hpp"
#include "../../../render/opengl/oglrendertarget.hpp"

#include "../glfwmonitor.hpp"
#include "glfwrendertargetgl.hpp"

#include "../../../input/glfw/glfwinput.hpp"

namespace engine {
    namespace glfw {
        class GLFWWindowGL : public Window {
        public:
            GLFWWindowGL(const std::string &title, Vec2i size, WindowAttributes attributes);

            GLFWWindowGL(const std::string &title,
                         Vec2i size,
                         WindowAttributes attributes,
                         GLFWMonitor &monitor,
                         VideoMode videoMode);

            ~GLFWWindowGL() override;

            RenderDevice &getRenderDevice() override;

            RenderTarget &getRenderTarget() override;

            Input &getInput() override;

            void makeCurrent() override;

            void swapBuffers() override;

            void update() override;

            bool shouldClose() override;

            void registerListener(WindowListener &listener) override;

            void unregisterListener(WindowListener &listener) override;

            void maximize() override;

            void minimize() override;

            void restore() override;

            void show() override;

            void hide() override;

            void focus() override;

            void requestAttention() override;

            void setTitle(std::string title) override;

            void setIcon(Image<ColorRGBA> &buffer) override;

            void setWindowPosition(Vec2i position) override;

            Vec2i getWindowPosition() override;

            void setWindowSize(Vec2i size) override;

            Vec2i getWindowSize() override;

            void setWindowSizeLimit(Vec2i sizeMin, Vec2i sizeMax) override;

            void setWindowAspectRatio(Vec2i ratio) override;

            Vec2i getFramebufferSize() override;

            Vec4i getFrameSize() override;

            Vec2f getWindowContentScale() override;

            float getWindowOpacity() override;

            void setWindowOpacity(float opacity) override;

            std::unique_ptr<Monitor> getMonitor() override;

            void setMonitor(Monitor &monitor, Recti rect, int refreshRate) override;

            void setWindowed() override;

            void setWindowDecorated(bool decorated) override;

            void setWindowResizable(bool resizable) override;

            void setWindowAlwaysOnTop(bool alwaysOnTop) override;

            void setWindowAutoMinimize(bool autoMinimize) override;

            void setWindowFocusOnShow(bool focusOnShow) override;

            void setSwapInterval(int interval) override;

            void glfwWindowCloseCallback();

            void glfwWindowMoveCallback(Vec2i pos);

            void glfwWindowSizeCallback(int width, int height);

            void glfwWindowRefreshCallback();

            void glfwWindowFocusCallback(bool focused);

            void glfwWindowMinimizeCallback();

            void glfwWindowMaximizeCallback();

            void glfwWindowContentScaleCallback(Vec2f scale);

            void glfwFrameBufferSizeCallback(Vec2i size);

            GLFWwindow *wndH;
        private:
            std::unique_ptr<GLFWInput> input;

            std::unique_ptr<opengl::OGLRenderDevice> renderDevice;
            std::unique_ptr<GLFWRenderTargetGL> renderTarget;

            std::set<WindowListener *> listeners;
        };
    }
}

#endif //MANA_GLFWWINDOWGL_HPP
