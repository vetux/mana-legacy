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

#ifndef MANA_MANA_HPP
#define MANA_MANA_HPP

#include "engine/io/imagefile.hpp"
#include "engine/io/serializer.hpp"
#include "engine/io/deserializer.hpp"
#include "engine/io/assetfile.hpp"
#include "engine/io/audiofile.hpp"
#include "engine/io/file.hpp"
#include "engine/io/json/jsonserializer.hpp"
#include "engine/io/json/jsondeserializer.hpp"
#include "engine/io/json/ecs/componentdeserializer.hpp"
#include "engine/io/json/ecs/componentserializer.hpp"
#include "engine/io/json/ecs/sceneserializer.hpp"
#include "engine/io/json/ecs/scenedeserializer.hpp"
#include "engine/io/json/ecs/nodeserializer.hpp"
#include "engine/io/json/ecs/nodedeserializer.hpp"
#include "engine/io/json/resource/resourcemanagerdeserializer.hpp"
#include "engine/io/json/resource/resourcedeserializer.hpp"
#include "engine/input/input.hpp"
#include "engine/input/mousekey.hpp"
#include "engine/input/inputlistener.hpp"
#include "engine/input/key.hpp"
#include "engine/input/mouse.hpp"
#include "engine/ecs/component.hpp"
#include "engine/ecs/componenttype.hpp"
#include "engine/ecs/node.hpp"
#include "engine/ecs/components.hpp"
#include "engine/ecs/system.hpp"
#include "engine/ecs/scene.hpp"
#include "engine/ecs/ecs.hpp"
#include "engine/ecs/components/boneanimatorcomponent.hpp"
#include "engine/ecs/components/cameracomponent.hpp"
#include "engine/ecs/components/transformcomponent.hpp"
#include "engine/ecs/components/lightcomponent.hpp"
#include "engine/ecs/components/particlecomponent.hpp"
#include "engine/ecs/components/physics2dcomponent.hpp"
#include "engine/ecs/components/rendercomponent.hpp"
#include "engine/ecs/components/scriptcomponent.hpp"
#include "engine/ecs/components/physics3dcomponent.hpp"
#include "engine/ecs/components/gui/textcomponent.hpp"
#include "engine/ecs/components/gui/canvascomponent.hpp"
#include "engine/ecs/components/gui/buttoncomponent.hpp"
#include "engine/ecs/systems/physics2dsystem.hpp"
#include "engine/ecs/systems/animationsystem.hpp"
#include "engine/ecs/systems/eventsystem.hpp"
#include "engine/ecs/systems/scriptingsystem.hpp"
#include "engine/ecs/systems/physics3dsystem.hpp"
#include "engine/ecs/systems/rendersystem.hpp"
#include "engine/resource/resource.hpp"
#include "engine/resource/resourcemanager.hpp"
#include "engine/resource/resourcehandle.hpp"
#include "engine/resource/script/monoscriptresource.hpp"
#include "engine/resource/render/shaderresource.hpp"
#include "engine/resource/render/meshbufferresource.hpp"
#include "engine/resource/render/texturebufferresource.hpp"
#include "engine/resource/raw/rawstringresource.hpp"
#include "engine/resource/file/textfileresource.hpp"
#include "engine/resource/file/imagefileresource.hpp"
#include "engine/resource/file/meshfileresource.hpp"
#include "engine/script/script.hpp"
#include "engine/script/mono/monocppdomain.hpp"
#include "engine/script/mono/monocppobject.hpp"
#include "engine/script/mono/monocppvalue.hpp"
#include "engine/script/mono/monoscript.hpp"
#include "engine/script/mono/monocpparguments.hpp"
#include "engine/script/mono/monocppassembly.hpp"
#include "engine/display/windowlistener.hpp"
#include "engine/display/displaybackend.hpp"
#include "engine/display/videomode.hpp"
#include "engine/display/windowattributes.hpp"
#include "engine/display/monitor.hpp"
#include "engine/display/window.hpp"
#include "engine/display/displaymanager.hpp"
#include "engine/render/renderobject.hpp"
#include "engine/render/meshbuffer.hpp"
#include "engine/render/graphicsbackend.hpp"
#include "engine/render/color.hpp"
#include "engine/render/rendertarget.hpp"
#include "engine/render/mesh.hpp"
#include "engine/render/renderer.hpp"
#include "engine/render/shaderprogram.hpp"
#include "engine/render/texturebuffer.hpp"
#include "engine/render/rendercommand.hpp"
#include "engine/render/renderdevice.hpp"
#include "engine/render/imagebuffer.hpp"
#include "engine/render/2d/renderer2d.hpp"
#include "engine/render/3d/camera.hpp"
#include "engine/render/3d/renderscene.hpp"
#include "engine/render/3d/forwardpipeline.hpp"
#include "engine/render/3d/geometrybuffer.hpp"
#include "engine/render/3d/renderpass.hpp"
#include "engine/render/3d/light.hpp"
#include "engine/render/3d/forwardcommand.hpp"
#include "engine/render/3d/renderer3d.hpp"
#include "engine/render/3d/deferredpipeline.hpp"
#include "engine/render/3d/deferredcommand.hpp"
#include "engine/render/3d/material.hpp"
#include "engine/render/3d/passes/shadowpass.hpp"
#include "engine/render/3d/passes/lightingpass.hpp"
#include "engine/render/3d/passes/outlinepass.hpp"
#include "engine/render/3d/passes/geometrypass.hpp"
#include "engine/render/opengl/hlslcrosscompiler.hpp"
#include "engine/audio/audiodevice.hpp"
#include "engine/audio/audiobuffer.hpp"
#include "engine/audio/audiobackend.hpp"
#include "engine/audio/audiolistener.hpp"
#include "engine/audio/audiosource.hpp"
#include "engine/audio/audiocontext.hpp"
#include "engine/audio/audioformat.hpp"
#include "engine/physics/rigidbodytype.hpp"
#include "engine/physics/physicsbackend.hpp"
#include "engine/physics/physics.hpp"
#include "engine/physics/2d/collider2d.hpp"
#include "engine/physics/2d/rigidbody2d.hpp"
#include "engine/physics/2d/world2d.hpp"
#include "engine/physics/3d/world3d.hpp"
#include "engine/physics/3d/collider3d.hpp"
#include "engine/physics/3d/rigidbody3d.hpp"
#include "engine/math/vector2.hpp"
#include "engine/math/transform.hpp"
#include "engine/math/vector4.hpp"
#include "engine/math/matrix.hpp"
#include "engine/math/matrixmath.hpp"
#include "engine/math/grid.hpp"
#include "engine/math/rotation.hpp"
#include "engine/math/rectangle.hpp"
#include "engine/math/vector3.hpp"
#include "engine/async/threadpool.hpp"
#include "engine/async/task.hpp"

#endif // MANA_MANA_HPP