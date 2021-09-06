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

#include "engine/display/displaymanager.hpp"

#include <utility>

#include "glfw/glfwdisplay.hpp"

engine::DisplayManager::DisplayManager(engine::DisplayBackend displayApi) : displayApi(displayApi) {}

engine::DisplayManager::~DisplayManager() = default;

engine::Monitor *engine::DisplayManager::getPrimaryMonitor() const {
    switch (displayApi) {
        case GLFW:
            return glfw::getPrimaryMonitor();
        default:
            throw std::runtime_error("Unsupported display api");
    }
}

std::set<engine::Monitor *> engine::DisplayManager::getMonitors() const {
    switch (displayApi) {
        case GLFW:
            return glfw::getMonitors();
        default:
            throw std::runtime_error("Unsupported display api");
    }
}

engine::Window *engine::DisplayManager::createWindow(engine::GraphicsBackend graphicsBackend) const {
    switch (displayApi) {
        case GLFW:
            return glfw::createWindow(graphicsBackend);
        default:
            throw std::runtime_error("Unsupported display api");
    }
}

engine::Window *engine::DisplayManager::createWindow(engine::GraphicsBackend graphicsBackend, std::string title, engine::Vec2i size,
                                                     engine::WindowAttributes attributes) const {
    switch (displayApi) {
        case GLFW:
            return glfw::createWindow(graphicsBackend, std::move(title), size, attributes);
        default:
            throw std::runtime_error("Unsupported display api");
    }
}

engine::Window *engine::DisplayManager::createWindow(engine::GraphicsBackend graphicsBackend, std::string title, engine::Vec2i size,
                                                     engine::WindowAttributes attributes, engine::Monitor &monitor,
                                                     engine::VideoMode mode) const {
    switch (displayApi) {
        case GLFW:
            return glfw::createWindow(graphicsBackend, std::move(title), size, attributes, monitor, mode);
        default:
            throw std::runtime_error("Unsupported display api");
    }
}