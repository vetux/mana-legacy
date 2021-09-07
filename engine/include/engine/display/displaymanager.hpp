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

#ifndef MANA_DISPLAYMANAGER_HPP
#define MANA_DISPLAYMANAGER_HPP

#include <set>

#include "engine/display/displaybackend.hpp"
#include "engine/display/window.hpp"
#include "engine/display/monitor.hpp"

namespace engine {
    class DisplayManager {
    public:
        DisplayManager();

        explicit DisplayManager(DisplayBackend displayApi);

        ~DisplayManager();

        Monitor *getPrimaryMonitor() const;

        std::set<Monitor *> getMonitors() const;

        Window *createWindow(GraphicsBackend graphicsBackend) const;

        Window *createWindow(GraphicsBackend graphicsBackend,
                             std::string title,
                             Vec2i size,
                             WindowAttributes attributes) const;

        Window *createWindow(GraphicsBackend graphicsBackend,
                             std::string title,
                             Vec2i size,
                             WindowAttributes attributes,
                             Monitor &monitor,
                             VideoMode mode) const;

        DisplayBackend getApi() const;

    private:
        DisplayBackend displayApi;
    };
}
#endif //MANA_DISPLAYMANAGER_HPP
