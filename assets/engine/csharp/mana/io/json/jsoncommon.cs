using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace Mana.IO
{
    static class JsonCommon
    {
        public static ComponentType convertComponentType(string type)
        {
            if (type == "transform")
                return ComponentType.TRANSFORM;
            else if (type == "camera")
                return ComponentType.CAMERA;
            else if (type == "light")
                return ComponentType.LIGHT;
            else if (type == "mesh_render")
                return ComponentType.MESH_RENDER;
            else
                return ComponentType.NONE;
        }

        public static string convertComponentType(ComponentType type)
        {
            switch (type)
            {
                case ComponentType.TRANSFORM:
                    return "transform";
                case ComponentType.CAMERA:
                    return "camera";
                case ComponentType.LIGHT:
                    return "light";
                case ComponentType.MESH_RENDER:
                    return "mesh_render";
                default:
                    return "none";
            }
        }

        public static Camera.CameraType convertCameraType(string type)
        {
            if (type == "perspective")
                return Camera.CameraType.PERSPECTIVE;
            else if (type == "orthographic")
                return Camera.CameraType.ORTHOGRAPHIC;
            else
                throw new System.Exception();
        }

        public static string convertCameraType(Camera.CameraType type)
        {
            switch (type)
            {
                case Camera.CameraType.PERSPECTIVE:
                    return "perspective";
                case Camera.CameraType.ORTHOGRAPHIC:
                    return "orthographic";
                default:
                    throw new System.Exception();
            }
        }

        public static Light.LightType convertLightType(string type)
        {
            if (type == "directional")
                return Light.LightType.DIRECTIONAL;
            else if (type == "point")
                return Light.LightType.POINT;
            else if (type == "spot")
                return Light.LightType.SPOT;
            else
                throw new System.Exception();
        }

        public static string convertLightType(Light.LightType type)
        {
            switch (type)
            {
                case Light.LightType.DIRECTIONAL:
                    return "directional";
                case Light.LightType.POINT:
                    return "point";
                case Light.LightType.SPOT:
                    return "spot";
                default:
                    throw new System.Exception();
            }
        }

        public static Vector3 convertVector(JToken vec)
        {
            Vector3 ret = new Vector3();

            if (vec["x"] != null)
                ret.x = vec.Value<float>("x");
            else if (vec["r"] != null)
                ret.x = vec.Value<float>("r");

            if (vec["y"] != null)
                ret.y = vec.Value<float>("y");
            else if (vec["g"] != null)
                ret.y = vec.Value<float>("g");

            if (vec["z"] != null)
                ret.z = vec.Value<float>("z");
            else if (vec["b"] != null)
                ret.z = vec.Value<float>("b");

            return ret;
        }

        public static JObject convertVector(Vector3 vec)
        {
            JObject ret = new JObject();
            ret.Add("x", vec.x);
            ret.Add("y", vec.y);
            ret.Add("z", vec.z);
            return ret;
        }

        public static Transform convertTransform(JToken component)
        {
            if (component == null)
                throw new System.Exception();
            Transform ret = new Transform();
            ret.position = convertVector(component["transform"].Value<JToken>("position"));
            ret.rotation = convertVector(component["transform"].Value<JToken>("rotation"));
            ret.scale = convertVector(component["transform"].Value<JToken>("scale"));
            ret.parentName = component.Value<string>("parent");
            return ret;
        }

        public static JObject convertTransform(Transform component)
        {
            JObject t = new JObject();
            t.Add("position", convertVector(component.position));
            t.Add("rotation", convertVector(component.rotation));
            t.Add("scale", convertVector(component.scale));

            JObject ret = new JObject();
            ret.Add("transform", t);
            ret.Add("parent", component.parentName);

            return ret;
        }

        public static Camera convertCamera(JToken component)
        {
            Camera ret = new Camera();
            ret.cameraType = convertCameraType(component.Value<string>("cameraType"));
            ret.nearClip = component.Value<float>("nearClip");
            ret.farClip = component.Value<float>("farClip");

            if (ret.cameraType == Camera.CameraType.PERSPECTIVE)
            {
                ret.fov = component.Value<float>("fov");
                ret.aspectRatio = component.Value<float>("aspectRatio");
            }
            else if (ret.cameraType == Camera.CameraType.ORTHOGRAPHIC)
            {
                ret.left = component.Value<float>("left");
                ret.top = component.Value<float>("top");
                ret.right = component.Value<float>("right");
                ret.bottom = component.Value<float>("bottom");
            }

            return ret;
        }

        public static JObject convertCamera(Camera camera)
        {
            JObject ret = new JObject();
            ret.Add("cameraType", convertCameraType(camera.cameraType));
            ret.Add("nearClip", camera.nearClip);
            ret.Add("farClip", camera.farClip);
            ret.Add("fov", camera.fov);
            ret.Add("aspectRatio", camera.aspectRatio);
            ret.Add("left", camera.left);
            ret.Add("top", camera.top);
            ret.Add("right", camera.right);
            ret.Add("bottom", camera.bottom);
            return ret;
        }

        public static Light convertLight(JToken component)
        {
            Light ret = new Light();
            ret.lightType = convertLightType(component.Value<string>("lightType"));
            ret.ambient = convertVector(component.Value<JToken>("ambient"));
            ret.diffuse = convertVector(component.Value<JToken>("diffuse"));
            ret.specular = convertVector(component.Value<JToken>("specular"));

            switch (ret.lightType)
            {
                case Light.LightType.POINT:
                    ret.constant = component.Value<float>("constant");
                    ret.linear = component.Value<float>("linear");
                    ret.quadratic = component.Value<float>("quadratic");
                    break;
                case Light.LightType.SPOT:
                    ret.direction = convertVector(component.Value<JToken>("direction"));
                    ret.cutOff = component.Value<float>("cutOff");
                    ret.outerCutOff = component.Value<float>("outerCutOff");
                    ret.constant = component.Value<float>("constant");
                    ret.linear = component.Value<float>("linear");
                    ret.quadratic = component.Value<float>("quadratic");
                    break;
                case Light.LightType.DIRECTIONAL:
                    ret.direction = convertVector(component.Value<JToken>("direction"));
                    break;
            }

            return ret;
        }

        public static JObject convertLight(Light light)
        {
            JObject ret = new JObject();
            ret.Add("lightType", convertLightType(light.lightType));
            ret.Add("ambient", convertVector(light.ambient));
            ret.Add("diffuse", convertVector(light.diffuse));
            ret.Add("specular", convertVector(light.specular));
            ret.Add("direction", convertVector(light.direction));
            ret.Add("cutOff", light.cutOff);
            ret.Add("outerCutOff", light.outerCutOff);
            ret.Add("constant", light.constant);
            ret.Add("linear", light.linear);
            ret.Add("quadratic", light.quadratic);
            return ret;
        }

        public static AssetPath convertAssetPath(JToken path)
        {
            AssetPath ret = new AssetPath();
            ret.bundle = path.Value<string>("bundle");
            ret.asset = path.Value<string>("asset");
            return ret;
        }

        public static JObject convertAssetPath(AssetPath path)
        {
            JObject ret = new JObject();
            ret.Add("bundle", path.bundle);
            ret.Add("asset", path.asset);
            return ret;
        }

        public static MeshRenderer convertMeshRenderer(JToken component)
        {
            MeshRenderer ret = new MeshRenderer();
            ret.castShadows = component.Value<bool>("castShadows");
            ret.receiveShadows = component.Value<bool>("receiveShadows");
            ret.mesh = convertAssetPath(component.Value<JToken>("mesh"));
            ret.material = convertAssetPath(component.Value<JToken>("material"));
            return ret;
        }

        public static JObject convertMeshRenderer(MeshRenderer component)
        {
            JObject ret = new JObject();
            ret.Add("castShadows", component.castShadows);
            ret.Add("receiveShadows", component.receiveShadows);
            ret.Add("mesh", convertAssetPath(component.mesh));
            ret.Add("material", convertAssetPath(component.material));
            return ret;
        }

        public static Component convertComponent(JToken component)
        {
            var type = convertComponentType(component.Value<string>("componentType"));
            Component ret;
            switch (type)
            {
                case ComponentType.TRANSFORM:
                    ret = convertTransform(component);
                    break;
                case ComponentType.CAMERA:
                    ret = convertCamera(component);
                    break;
                case ComponentType.LIGHT:
                    ret = convertLight(component);
                    break;
                case ComponentType.MESH_RENDER:
                    ret = convertMeshRenderer(component);
                    break;
                default:
                    ret = new Component();
                    break;
            }
            ret.enabled = component.Value<bool>("enabled");
            ret.type = type;
            return ret;
        }

        public static JObject convertComponent(Component component)
        {
            JObject ret;
            switch (component.type)
            {
                case ComponentType.TRANSFORM:
                    ret = convertTransform(component as Transform);
                    break;
                case ComponentType.CAMERA:
                    ret = convertCamera(component as Camera);
                    break;
                case ComponentType.LIGHT:
                    ret = convertLight(component as Light);
                    break;
                case ComponentType.MESH_RENDER:
                    ret = convertMeshRenderer(component as MeshRenderer);
                    break;
                default:
                    ret = new JObject();
                    break;
            }
            ret.Add("enabled", component.enabled);
            ret.Add("componentType", convertComponentType(component.type));
            return ret;
        }

        public static Node convertNode(JToken node)
        {
            Node ret = new Node();
            ret.enabled = node.Value<bool>("enabled");
            JArray components = node.Value<JArray>("components");
            foreach (var component in components)
            {
                var comp = convertComponent(component);
                if (comp.type != ComponentType.NONE)
                    ret.components.Add(comp);
            }
            return ret;
        }

        public static JObject convertNode(Node node)
        {
            JObject ret = new JObject();
            ret.Add("enabled", node.enabled);
            JArray components = new JArray();
            foreach (var component in node.components)
            {
                if (component.type == ComponentType.NONE)
                    continue;
                var comp = convertComponent(component);
                components.Add(comp);
            }
            ret.Add("components", components);
            return ret;
        }

        public static Scene convertScene(JToken scene)
        {
            Scene ret = new Scene();
            ret.name = scene.Value<string>("name");
            JObject nodes = scene.Value<JObject>("nodes");
            foreach (var node in nodes)
            {
                ret.nodes.Add(node.Key, convertNode(node.Value as JObject));
            }
            return ret;
        }

        public static JObject convertScene(Scene scene)
        {
            JObject ret = new JObject();
            ret.Add("name", scene.name);
            JObject nodes = new JObject();
            foreach (var node in scene.nodes)
            {
                nodes.Add(node.Key, convertNode(node.Value));
            }
            ret.Add("nodes", nodes);
            return ret;
        }
    }
}