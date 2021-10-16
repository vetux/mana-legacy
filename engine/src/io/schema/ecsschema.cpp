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

#include "engine/io/schema/ecsschema.hpp"
#include "engine/io/schema/mathschema.hpp"

namespace engine {
    CameraType &operator<<(CameraType &value, const Message &message) {
        auto str = message.getString();
        if (str == "perspective")
            value = PERSPECTIVE;
        else if (str == "orthographic")
            value = ORTHOGRAPHIC;
        else
            throw std::runtime_error("Invalid camera type " + str);
        return value;
    }

    Message &operator<<(Message &message, CameraType type) {
        switch (type) {
            case PERSPECTIVE:
                message = "perspective";
                break;
            case ORTHOGRAPHIC:
                message = "orthographic";
                break;
            default:
                throw std::runtime_error("");
        }
        return message;
    }

    LightType &operator<<(LightType &value, const Message &message) {
        auto str = message.getString();
        if (str == "directional")
            value = LIGHT_DIRECTIONAL;
        else if (str == "point")
            value = LIGHT_POINT;
        else if (str == "spot")
            value = LIGHT_SPOT;
        else
            throw std::runtime_error("Invalid light type " + str);
        return value;
    }

    Message &operator<<(Message &message, LightType type) {
        switch (type) {
            case LIGHT_DIRECTIONAL:
                message = "directional";
                break;
            case LIGHT_POINT:
                message = "point";
                break;
            case LIGHT_SPOT:
                message = "spot";
                break;
            default:
                throw std::runtime_error("");
        }
        return message;
    }

    AssetPath &operator<<(AssetPath &value, const Message &message) {
        auto map = message.getMap();
        value.bundle = message["bundle"].getString();
        value.asset = map["asset"].getString();
        return value;
    }

    Message &operator<<(Message &message, const AssetPath &path) {
        auto map = std::map<std::string, Message>();
        map["bundle"] = path.bundle;
        map["asset"] = path.asset;
        message = map;
        return message;
    }

    CameraComponent &operator<<(CameraComponent &component, const Message &message) {
        component = CameraComponent();
        component.camera.type << message["cameraType"];
        component.camera.nearClip = message["nearClip"];
        component.camera.farClip = message["farClip"];
        if (component.camera.type == PERSPECTIVE) {
            component.camera.fov = message["fov"];
            component.camera.aspectRatio = message["aspectRatio"];
        } else {
            component.camera.left = message["left"];
            component.camera.right = message["right"];
            component.camera.top = message["top"];
            component.camera.bottom = message["bottom"];
        }
        return component;
    }

    Message &operator<<(Message &message, const CameraComponent &component) {
        message = std::map<std::string, Message>();
        message["cameraType"] << component.camera.type;
        message["nearClip"] = component.camera.nearClip;
        message["farClip"] = component.camera.farClip;
        if (component.camera.type == PERSPECTIVE) {
            message["fov"] = component.camera.fov;
            message["aspectRatio"] = component.camera.aspectRatio;
        } else {
            message["left"] = component.camera.left;
            message["right"] = component.camera.right;
            message["top"] = component.camera.top;
            message["bottom"] = component.camera.bottom;
        }
        return message;
    }

    TransformComponent &operator<<(TransformComponent &component, const Message &message) {
        component = TransformComponent();
        component.transform << message["transform"];
        component.parent = message["parent"].get<std::string>();
        return component;
    }

    Message &operator<<(Message &message, const TransformComponent &component) {
        message = std::map<std::string, Message>();
        message["transform"] << component.transform;
        message["parent"] = component.parent;
        return message;
    }

    MeshRenderComponent &operator<<(MeshRenderComponent &component, const Message &message) {
        component = MeshRenderComponent();
        component.castShadows = message["castShadows"];
        component.receiveShadows = message["receiveShadows"];
        component.mesh << message["mesh"];
        component.material << message["material"];
        return component;
    }

    Message &operator<<(Message &message, const MeshRenderComponent &component) {
        message = std::map<std::string, Message>();
        message["castShadows"] = component.castShadows;
        message["receiveShadows"] = component.receiveShadows;
        message["mesh"] << component.mesh;
        message["material"] << component.material;
        return message;
    }

    SkyboxComponent &operator<<(SkyboxComponent &component, const Message &message) {
        component = SkyboxComponent();
        int i = 0;
        for (auto &node : message["paths"].getVector()) {
            component.paths.at(i++) << node;
        }
        return component;
    }

    Message &operator<<(Message &message, const SkyboxComponent &component) {
        message = std::map<std::string, Message>();
        auto vector = std::vector<Message>();
        for (const auto &path : component.paths) {
            Message m;
            m << path;
            vector.emplace_back(m);
        }
        message["paths"] = vector;
        return message;
    }

    LightComponent &operator<<(LightComponent &component, const Message &message) {
        component = LightComponent();

        component.light.type << message["lightType"];

        component.light.ambient << message["ambient"];
        component.light.diffuse << message["diffuse"];
        component.light.specular << message["specular"];

        switch (component.light.type) {
            case LIGHT_POINT:
                component.light.constant = message["constant"];
                component.light.linear = message["linear"];
                component.light.quadratic = message["quadratic"];
                break;
            case LIGHT_SPOT:
                component.light.direction << message["direction"];
                component.light.cutOff = message["cutOff"];
                component.light.outerCutOff = message["outerCutOff"];
                component.light.constant = message["constant"];
                component.light.linear = message["linear"];
                component.light.quadratic = message["quadratic"];
                break;
            case LIGHT_DIRECTIONAL:
                component.light.direction << message["direction"];
                break;
        }
        return component;
    }

    Message &operator<<(Message &message, const LightComponent &component) {
        message = std::map<std::string, Message>();
        message["lightType"] << component.light.type;
        message["ambient"] << component.light.ambient;
        message["diffuse"] << component.light.diffuse;
        message["specular"] << component.light.specular;

        switch (component.light.type) {
            case engine::LIGHT_POINT:
                message["constant"] = component.light.constant;
                message["linear"] = component.light.linear;
                message["quadratic"] = component.light.quadratic;
                break;
            case engine::LIGHT_SPOT:
                message["direction"] << component.light.direction;
                message["cutOff"] = component.light.cutOff;
                message["outerCutOff"] = component.light.outerCutOff;
                message["constant"] = component.light.constant;
                message["linear"] = component.light.linear;
                message["quadratic"] = component.light.quadratic;
                break;
            case engine::LIGHT_DIRECTIONAL:
                message["direction"] << component.light.direction;
                break;
            default:
                throw std::runtime_error("");
        }
        return message;
    }

    MonoScriptComponent &operator<<(MonoScriptComponent &component, const Message &message) {
        component = MonoScriptComponent();
        component.assembly = message["assembly"].getString();
        component.nameSpace = message["nameSpace"].getString();
        component.className = message["className"].getString();
        component.queue = message["queue"];
        return component;
    }

    Message &operator<<(Message &message, const MonoScriptComponent &component) {
        message = std::map<std::string, Message>();
        message["assembly"] = component.assembly;
        message["nameSpace"] = component.nameSpace;
        message["className"] = component.className;
        message["queue"] = component.queue;
        return message;
    }

    MonoSyncComponent &operator<<(MonoSyncComponent &component, const Message &message) {
        component = MonoSyncComponent();
        return component;
    }

    Message &operator<<(Message &message, const MonoSyncComponent &component) {
        message = std::map<std::string, Message>();
        return message;
    }

    EntityManager &operator<<(EntityManager &entityManager, const Message &message) {
        auto &componentManager = entityManager.getComponentManager();

        entityManager.clear();

        auto entities = message.getMap().at("entities").getMap();
        for (auto &entity : entities) {
            auto ent = entityManager.create();

            entityManager.setName(ent, entity.first);

            auto components = entity.second.getMap().at("components").getVector();
            for (auto &component : components) {
                auto componentType = component.at("componentType").getString();
                if (componentType == "transform") {
                    TransformComponent comp;
                    comp << component;
                    componentManager.create<TransformComponent>(ent, comp);
                } else if (componentType == "camera") {
                    CameraComponent comp;
                    comp << component;
                    componentManager.create<CameraComponent>(ent, comp);
                } else if (componentType == "light") {
                    LightComponent comp;
                    comp << component;
                    componentManager.create<LightComponent>(ent, comp);
                } else if (componentType == "script_mono") {
                    MonoScriptComponent comp;
                    comp << component;
                    componentManager.create<MonoScriptComponent>(ent, comp);
                } else if (componentType == "sync_mono") {
                    MonoSyncComponent comp;
                    comp << component;
                    componentManager.create<MonoSyncComponent>(ent, comp);
                } else if (componentType == "mesh_render") {
                    MeshRenderComponent comp;
                    comp << component;
                    auto c = componentManager.create<MeshRenderComponent>(ent, comp);
                    c << component;
                    componentManager.update<MeshRenderComponent>(ent, c);
                } else if (componentType == "skybox") {
                    SkyboxComponent comp;
                    comp << component;
                    componentManager.create<SkyboxComponent>(ent, comp);
                } else {
                    throw std::runtime_error("Invalid component type " + componentType);
                }
            }
        }

        return entityManager;
    }

    Message &operator<<(Message &message, const EntityManager &manager) {
        //TODO: Implement entity manager serialization
        throw std::runtime_error("Not Implemented");
        /*auto &componentManager = manager.getComponentManager();
        for (auto &ent : manager.getEntities()) {
            Message msg;
            if (componentManager.check<TransformComponent>(ent)) {

            }
            if (componentManager.check<CameraComponent>(ent)) {

            }
            if (componentManager.check<LightComponent>(ent)) {

            }
            if (componentManager.check<MonoScriptComponent>(ent)) {

            }
            if (componentManager.check<MonoSyncComponent>(ent)) {

            }
            if (componentManager.check<MeshRenderComponent>(ent)) {

            }
            if (componentManager.check<SkyboxComponent>(ent)) {

            }
            message.getMap().insert("", msg);
        }

        return message;*/
    }
}