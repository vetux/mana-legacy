/**
 * Convenience header which includes all engine headers.
 */

#ifndef MANA_MANA_HPP
#define MANA_MANA_HPP

#include "engine/io/imageloader.hpp"
#include "engine/io/resource.hpp"
#include "engine/io/resourcemanager.hpp"
#include "engine/io/file.hpp"
#include "engine/io/buffer.hpp"
#include "engine/io/imagewriter.hpp"
#include "engine/io/meshloader.hpp"
#include "engine/io/fileresource.hpp"
#include "engine/io/imagebuffer.hpp"
#include "engine/input/input.hpp"
#include "engine/input/mousekey.hpp"
#include "engine/input/inputlistener.hpp"
#include "engine/input/key.hpp"
#include "engine/input/mouse.hpp"
#include "engine/ecs/component.hpp"
#include "engine/ecs/node.hpp"
#include "engine/ecs/system.hpp"
#include "engine/ecs/data/shader.hpp"
#include "engine/ecs/data/material.hpp"
#include "engine/ecs/components/transform.hpp"
#include "engine/ecs/components/camera.hpp"
#include "engine/ecs/components/rigidbody.hpp"
#include "engine/ecs/components/collider.hpp"
#include "engine/ecs/components/light.hpp"
#include "engine/ecs/components/particleemitter.hpp"
#include "engine/ecs/components/script.hpp"
#include "engine/ecs/components/meshrenderer.hpp"
#include "engine/ecs/components/boneanimator.hpp"
#include "engine/ecs/components/gui/text.hpp"
#include "engine/ecs/components/gui/canvas.hpp"
#include "engine/ecs/components/gui/button.hpp"
#include "engine/ecs/systems/animationsystem.hpp"
#include "engine/ecs/systems/eventsystem.hpp"
#include "engine/ecs/systems/scriptingsystem.hpp"
#include "engine/ecs/systems/physicssystem.hpp"
#include "engine/ecs/systems/rendersystem.hpp"
#include "engine/sound/audiobuffer.hpp"
#include "engine/sound/audioplayer.hpp"
#include "engine/render/rendertransform.hpp"
#include "engine/render/renderapi.hpp"
#include "engine/render/vertex.hpp"
#include "engine/render/graphicsapi.hpp"
#include "engine/render/renderscene.hpp"
#include "engine/render/color.hpp"
#include "engine/render/meshobject.hpp"
#include "engine/render/primitive.hpp"
#include "engine/render/renderunit.hpp"
#include "engine/render/windowlistener.hpp"
#include "engine/render/rendercamera.hpp"
#include "engine/render/displayapi.hpp"
#include "engine/render/framebufferobject.hpp"
#include "engine/render/glfwdisplayapi.hpp"
#include "engine/render/rendermesh.hpp"
#include "engine/render/shaderprogram.hpp"
#include "engine/render/textureattributes.hpp"
#include "engine/render/textureobject.hpp"
#include "engine/render/videomode.hpp"
#include "engine/render/windowattributes.hpp"
#include "engine/render/renderlight.hpp"
#include "engine/render/monitor.hpp"
#include "engine/render/window.hpp"
#include "engine/physics/physicsengine.hpp"
#include "engine/math/vector2.hpp"
#include "engine/math/vector4.hpp"
#include "engine/math/matrix.hpp"
#include "engine/math/matrixmath.hpp"
#include "engine/math/grid.hpp"
#include "engine/math/rotation.hpp"
#include "engine/math/rectangle.hpp"
#include "engine/math/vector3.hpp"
#include "engine/lang/python/pythoninterpreter.hpp"
#include "engine/lang/mono/monointerpreter.hpp"

#endif //MANA_MANA_HPP
