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

#include "engine/imgui/imguicompat.hpp"

#include <limits>

#include "engine/display/window.hpp"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "display/glfw/opengl/glfwwindowgl.hpp"

static uint imGuiRefCounter = 0;

static void joinImGui() {
    if (imGuiRefCounter == std::numeric_limits<uint>::max()) {
        throw std::runtime_error("Counter overflow");
    }
    if (imGuiRefCounter++ == 0)
        ImGui::CreateContext();
}

static void leaveImGui() {
    if (imGuiRefCounter == 0)
        throw std::runtime_error("Counter underflow");
    if (--imGuiRefCounter == 0)
        ImGui::DestroyContext();
}

namespace engine {
    namespace ImGuiCompat {
        void Init(Window &window) {
            joinImGui();
            switch (window.getDisplayBackend()) {
                case GLFW:
                    ImGui_ImplGlfw_InitForOpenGL(dynamic_cast<glfw::GLFWWindowGL &>(window).wndH, true);
                    break;
            }
            switch (window.getGraphicsBackend()) {
                case OPENGL_4_6:
                    ImGui_ImplOpenGL3_Init("#version 460");
                    break;
                case DIRECTX_11:
                case VULKAN:
                    throw std::runtime_error("Not supported");
            }
        }

        void Shutdown(Window &window) {
            switch (window.getGraphicsBackend()) {
                case OPENGL_4_6:
                    ImGui_ImplOpenGL3_Shutdown();
                    break;
                case DIRECTX_11:
                case VULKAN:
                    throw std::runtime_error("Not supported");
            }
            switch (window.getDisplayBackend()) {
                case GLFW:
                    ImGui_ImplGlfw_Shutdown();
                    break;
            }
            leaveImGui();
        }

        void NewFrame(Window &window) {
            switch (window.getGraphicsBackend()) {
                case OPENGL_4_6:
                    ImGui_ImplOpenGL3_NewFrame();
                    break;
                case DIRECTX_11:
                case VULKAN:
                    throw std::runtime_error("Not supported");
            }
            switch (window.getDisplayBackend()) {
                case GLFW:
                    ImGui_ImplGlfw_NewFrame();
                    break;
            }
        }

        void DrawData(Window &window) {
            switch (window.getGraphicsBackend()) {
                case OPENGL_4_6:
                    glViewport(0, 0, window.getFramebufferSize().x, window.getFramebufferSize().y);
                    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
                    break;
                case DIRECTX_11:
                case VULKAN:
                    throw std::runtime_error("Not supported");
            }
        }
    }
}