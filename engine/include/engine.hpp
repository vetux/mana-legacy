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

#ifndef MANA_HPP
#define MANA_HPP

#include "engine/io/protocol.hpp"
#include "engine/io/message.hpp"
#include "engine/io/archive.hpp"
#include "engine/io/protocol/jsonprotocol.hpp"
#include "engine/asset/audio.hpp"
#include "engine/asset/camera.hpp"
#include "engine/asset/vertex.hpp"
#include "engine/asset/assetbundle.hpp"
#include "engine/asset/color.hpp"
#include "engine/asset/image.hpp"
#include "engine/asset/shader.hpp"
#include "engine/asset/mesh.hpp"
#include "engine/asset/assetimporter.hpp"
#include "engine/asset/light.hpp"
#include "engine/asset/texture.hpp"
#include "engine/asset/material.hpp"
#include "engine/asset/assetpath.hpp"
#include "engine/input/input.hpp"
#include "engine/input/mousekey.hpp"
#include "engine/input/inputlistener.hpp"
#include "engine/input/key.hpp"
#include "engine/input/mouse.hpp"
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
#include "engine/render/rendertarget.hpp"
#include "engine/render/renderer.hpp"
#include "engine/render/shaderprogram.hpp"
#include "engine/render/texturebuffer.hpp"
#include "engine/render/rendercommand.hpp"
#include "engine/render/renderallocator.hpp"
#include "engine/render/renderdevice.hpp"
#include "engine/render/2d/renderer2d.hpp"
#include "engine/render/2d/text/character.hpp"
#include "engine/render/2d/text/font.hpp"
#include "engine/render/2d/text/fontrasterizer.hpp"
#include "engine/render/3d/renderscene.hpp"
#include "engine/render/3d/forwardpipeline.hpp"
#include "engine/render/3d/geometrybuffer.hpp"
#include "engine/render/3d/renderpass.hpp"
#include "engine/render/3d/forwardcommand.hpp"
#include "engine/render/3d/renderer3d.hpp"
#include "engine/render/3d/rendermaterial.hpp"
#include "engine/render/3d/deferredpipeline.hpp"
#include "engine/render/3d/deferredcommand.hpp"
#include "engine/render/3d/passes/shadowpass.hpp"
#include "engine/render/3d/passes/lightingpass.hpp"
#include "engine/render/3d/passes/outlinepass.hpp"
#include "engine/render/3d/passes/geometrypass.hpp"
#include "engine/audio/audiodevice.hpp"
#include "engine/audio/audiobuffer.hpp"
#include "engine/audio/audiobackend.hpp"
#include "engine/audio/audiolistener.hpp"
#include "engine/audio/audiosource.hpp"
#include "engine/audio/audiocontext.hpp"
#include "engine/audio/audioformat.hpp"
#include "engine/physics/physics.hpp"
#include "engine/physics/2d/collider2d.hpp"
#include "engine/physics/2d/joint2d.hpp"
#include "engine/physics/2d/rigidbody2d.hpp"
#include "engine/physics/2d/world2d.hpp"
#include "engine/physics/3d/world3d.hpp"
#include "engine/physics/3d/joint3d.hpp"
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

#endif // MANA_HPP