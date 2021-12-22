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

#ifndef MANA_SHADERSOURCE_HPP
#define MANA_SHADERSOURCE_HPP

#include "engine/render/shader/shadercompiler.hpp"

#include "engine/asset/asset.hpp"

namespace engine {
    class ShaderSource : public Asset {
    public:
        ShaderSource() = default;

        ShaderSource(std::string src,
                     std::string entryPoint,
                     ShaderCompiler::ShaderStage stage,
                     ShaderCompiler::ShaderLanguage language,
                     bool preprocessed = false);

        ~ShaderSource() override = default;

        Asset *clone() override {
            return new ShaderSource(*this);
        }

        void preprocess(const std::function<std::string(const char *)> &include = {},
                        const std::map<std::string, std::string> &macros = {},
                        ShaderCompiler::OptimizationLevel optimizationLevel = ShaderCompiler::OPTIMIZATION_NONE);

        std::vector<uint32_t>
        compile(ShaderCompiler::OptimizationLevel optimizationLevel = ShaderCompiler::OPTIMIZATION_NONE);

        ShaderSource crossCompile(ShaderCompiler::ShaderLanguage targetLanguage,
                                  ShaderCompiler::OptimizationLevel optimizationLevel = ShaderCompiler::OPTIMIZATION_NONE) const;

        const std::string &getSrc() const;

        const std::string &getEntryPoint() const;

        ShaderCompiler::ShaderStage getStage() const;

        ShaderCompiler::ShaderLanguage getLanguage() const;

        bool isPreProcessed() const;

        bool isEmpty() const { return src.empty(); }

    private:
        std::string src{};
        std::string entryPoint{};
        ShaderCompiler::ShaderStage stage{};
        ShaderCompiler::ShaderLanguage language{};
        bool preprocessed{};
    };
}

#endif //MANA_SHADERSOURCE_HPP
