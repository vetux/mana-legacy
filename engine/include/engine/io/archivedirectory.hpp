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

#ifndef MANA_ARCHIVEDIRECTORY_HPP
#define MANA_ARCHIVEDIRECTORY_HPP

#include <fstream>
#include <filesystem>

#include "engine/io/archive.hpp"

namespace mana {
    /**
     * A directory representing an archive.
     */
    class ArchiveDirectory : public Archive {
    public:
        std::string directory;

        ArchiveDirectory() = default;

        explicit ArchiveDirectory(std::string directory) : directory(std::move(directory)) {}

        ~ArchiveDirectory() override = default;

        bool exists(const std::string &name) override {
            return std::filesystem::exists(name);
        }

        std::iostream *open(const std::string &path) override {
            auto ret = new std::fstream(directory + "/" + path);
            if (!*ret) {
                delete ret;
                throw std::runtime_error("Failed to open file " + path);
            }
            return ret;
        }
    };
}

#endif //MANA_ARCHIVEDIRECTORY_HPP
