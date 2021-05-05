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

#include "engine/io/json/jsonresourcefile.hpp"

#include "engine/resource/render/meshbufferresource.hpp"
#include "engine/resource/file/meshfileresource.hpp"
#include "engine/resource/meshresource.hpp"
#include "engine/resource/file/textfileresource.hpp"
#include "engine/resource/file/imagefileresource.hpp"
#include "engine/resource/render/texturebufferresource.hpp"
#include "engine/resource/script/monoscriptresource.hpp"

#include "extern/json.hpp"

namespace mana {
    TextureBuffer::TextureType parseTextureType(const std::string &str) {
        if (str == "texture2d")
            return TextureBuffer::TEXTURE_2D;
        else if (str == "cubemap")
            return TextureBuffer::TEXTURE_CUBE_MAP;
        else
            throw std::runtime_error("Invalid texture type " + str);
    }

    TextureBuffer::ColorFormat parseColorFormat(const std::string &str) {
        if (str == "rgba")
            return TextureBuffer::RGBA;
        else if (str == "rgb")
            return TextureBuffer::RGB;
        else
            throw std::runtime_error("Invalid color format " + str);
    }

    TextureBuffer::TextureWrapping parseTextureWrapping(const std::string &str) {
        if (str == "repeat")
            return TextureBuffer::REPEAT;
        else if (str == "mirrored_repeat")
            return TextureBuffer::MIRRORED_REPEAT;
        else if (str == "clamp_to_edge")
            return TextureBuffer::CLAMP_TO_EDGE;
        else if (str == "clamp_to_border")
            return TextureBuffer::CLAMP_TO_BORDER;
        else
            throw std::runtime_error("Invalid texture wrapping " + str);
    }

    TextureBuffer::TextureFiltering parseTextureFiltering(const std::string &str) {
        if (str == "nearest")
            return TextureBuffer::NEAREST;
        else if (str == "linear")
            return TextureBuffer::LINEAR;
        else
            throw std::runtime_error("Invalid texture filtering " + str);
    }

    TextureBuffer::MipMapFiltering parseMipMapFiltering(const std::string &str) {
        if (str == "nearest_mipmap_nearest")
            return TextureBuffer::NEAREST_MIPMAP_NEAREST;
        else if (str == "linear_mipmap_nearest")
            return TextureBuffer::LINEAR_MIPMAP_NEAREST;
        else if (str == "nearest_mipmap_linear")
            return TextureBuffer::NEAREST_MIPMAP_LINEAR;
        else if (str == "linear_mipmap_linear")
            return TextureBuffer::LINEAR_MIPMAP_LINEAR;
        else
            throw std::runtime_error("Invalid mipmap filtering " + str);
    }

    Transform parseTransform(const nlohmann::json &component) {
        Transform ret;

        ret.position.x = component["position"]["x"];
        ret.position.y = component["position"]["y"];
        ret.position.z = component["position"]["z"];

        ret.rotation.x = component["rotation"]["x"];
        ret.rotation.y = component["rotation"]["y"];
        ret.rotation.z = component["rotation"]["z"];

        ret.scale.x = component["scale"]["x"];
        ret.scale.y = component["scale"]["y"];
        ret.scale.z = component["scale"]["z"];

        return ret;
    }

    MeshFileResource *parseMeshFile(const nlohmann::json &j) {
        return new MeshFileResource(AssetFile(j["assetFilePath"]), j["assetName"]);
    }

    TextFileResource *parseTextFile(const nlohmann::json &j) {
        return new TextFileResource(j["filePath"]);
    }

    ImageFileResource *parseImageFile(const nlohmann::json &j) {
        return new ImageFileResource(j["filePath"]);
    }

    ShaderResource *parseShader(const nlohmann::json &j, const Resources &res, RenderAllocator &alloc) {
        return new ShaderResource(alloc,
                                  res.getResource<TextResource>(j["vertexShaderResourceName"]),
                                  res.getResource<TextResource>(j["fragmentShaderResourceName"]));
    }

    MeshBufferResource *parseMeshBuffer(const nlohmann::json &j, const Resources &res, RenderAllocator &alloc) {
        if (j["instanced"]) {
            std::vector<Transform> offsets;
            for (auto &t : j["instanceOffsets"]) {
                offsets.emplace_back(parseTransform(t));
            }
            return new MeshBufferResource(alloc, res.getResource<MeshResource>(j["meshResourceName"]), offsets);
        } else {
            return new MeshBufferResource(alloc, res.getResource<MeshResource>(j["meshResourceName"]));
        }
    }

    TextureBufferResource *parseTexture(const nlohmann::json &j, const Resources &res, RenderAllocator &alloc) {
        TextureBuffer::Attributes attr;
        attr.textureType = parseTextureType(j["textureType"]);
        attr.format = parseColorFormat(j["format"]);
        attr.wrapping = parseTextureWrapping(j["wrapping"]);
        attr.filterMin = parseTextureFiltering(j["filterMin"]);
        attr.filterMag = parseTextureFiltering(j["filterMag"]);
        attr.generateMipmap = j["generateMipmap"];
        attr.mipmapFilter = parseMipMapFiltering(j["mipmapFilter"]);
        return new TextureBufferResource(alloc, res.getResource<ImageResource>(j["imageResourceName"]), attr);
    }

    MonoScriptResource *parseMonoScript(const nlohmann::json &j, MonoCppDomain &monoRuntime) {
        return new MonoScriptResource(monoRuntime, j["assemblyFileName"], j["nameSpace"], j["className"]);
    }

    Resources *parseResources(const std::string &jsonStr, RenderAllocator &allocator, MonoCppDomain &monoRuntime) {
        auto *ret = new Resources();
        auto json = nlohmann::json::parse(jsonStr);
        for (auto &r : json["resources"]) {
            std::string type = r["type"];
            Resource *resource = nullptr;
            if (type == "meshfile")
                resource = parseMeshFile(r);
            else if (type == "textfile")
                resource = parseTextFile(r);
            else if (type == "imagefile")
                resource = parseImageFile(r);
            else if (type == "shader")
                resource = parseShader(r, *ret, allocator);
            else if (type == "meshbuffer")
                resource = parseMeshBuffer(r, *ret, allocator);
            else if (type == "texture")
                resource = parseTexture(r, *ret, allocator);
            else if (type == "monoscript")
                resource = parseMonoScript(r, monoRuntime);
            else
                throw std::runtime_error("Invalid resource type " + type);
            ret->addResource(r["name"], resource);
        }
        return ret;
    }

    JsonResourceFile::JsonResourceFile(const std::string &filePath)
            : fileContents(File::readAllText(filePath)) {
        this->filePath = filePath;
    }

    void JsonResourceFile::open() {
        fileContents = File::readAllText(filePath);
    }

    void JsonResourceFile::close() {
        fileContents.clear();
    }

    Resources *JsonResourceFile::getResources(RenderAllocator &allocator, MonoCppDomain &monoRuntime) {
        return parseResources(fileContents, allocator, monoRuntime);
    }
}