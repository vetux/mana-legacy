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

#ifndef MANA_SHADERCOMPILER_HPP
#define MANA_SHADERCOMPILER_HPP

#include <map>
#include <string>
#include <functional>

namespace engine {
    namespace ShaderCompiler {
        enum ShaderStage {
            VERTEX,
            FRAGMENT
        };

        enum ShaderLanguage {
            GLSL,
            HLSL
        };

        std::string compileGlslToHlsl(const std::string &source,
                                      ShaderStage stage,
                                      const std::function<std::string(const char *)> &includeCallback = {},
                                      const std::map<std::string, std::string> &macros = {});

        std::string compileHlslToGlsl(const std::string &source,
                                      const std::string &entryPoint,
                                      ShaderStage stage,
                                      const std::function<std::string(const char *)> &includeCallback = {},
                                      const std::map<std::string, std::string> &macros = {});

        std::vector<uint32_t> compileGlslToSPIRV(const std::string &source,
                                                 ShaderStage stage,
                                                 const std::function<std::string(const char *)> &include = {},
                                                 const std::map<std::string, std::string> &macros = {});

        std::vector<uint32_t> compileHlslToSPIRV(const std::string &source,
                                                 const std::string &entryPoint,
                                                 ShaderStage stage,
                                                 const std::function<std::string(const char *)> &include = {},
                                                 const std::map<std::string, std::string> &macros = {});
    }
}

#endif //MANA_SHADERCOMPILER_HPP