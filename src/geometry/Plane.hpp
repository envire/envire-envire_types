#pragma once

#include "../EnvireTypeBase.hpp"

#include <string>
#include <boost/serialization/access.hpp>
#include <base/Eigen.hpp>
#include <base-logging/Logging.hpp>
#include <configmaps/ConfigMap.hpp>
#include "Material.hpp"
namespace envire
{
    namespace types
    {
        namespace geometry
        {
            class Plane: public EnvireTypeBase
            {
            public:
                Plane() : Plane(std::string(), base::Vector2d(0., 0.)) {}
                Plane(std::string name, base::Vector2d size) : name(name), size(size) {}
                // TODO: store other values in configMap in the configMap variable
                Plane(configmaps::ConfigMap &configMap_) : configMap(configMap_)
                {
                    if (configMap.hasKey("name") && configMap.hasKey("size")
                        && configMap["size"].hasKey("x") && configMap["size"].hasKey("y"))
                    {
                        name = configMap["name"].toString();
                        size.x() = configMap["size"]["x"];
                        size.y() = configMap["size"]["y"];

                        // store all additional values in the configMap parameter
                        configMap.erase("name");
                        configMap.erase("size");

                        if (configMap.hasKey("material"))
                        {
                            material = std::make_shared<Material>(configMap["material"]);
                            configMap.erase("material");
                        }
                    }
                    else
                    {
                        LOG_ERROR_S << "The config map has no all required keys";
                        size = base::Vector2d::Zero();
                        configMap.clear();
                    }
                }

                std::string name;
                static inline std::string const type = "plane";
                base::Vector2d size;
                std::shared_ptr<Material> material;
                configmaps::ConfigMap configMap;

                configmaps::ConfigMap getFullConfigMap()
                {
                    configmaps::ConfigMap config;
                    config.append(configMap);
                    config["name"] = name;
                    config["type"] = type;
                    config["size"]["x"] = size.x();
                    config["size"]["y"] = size.y();
                    if (material != nullptr)
                        config["material"] = material->getFullConfigMap();
                    return config;
                }

                /**Grants access to boost serialization */
                friend class boost::serialization::access;

                /**Serializes the members of this class*/
                template <typename Archive>
                void serialize(Archive &ar, const unsigned int version)
                {
                    throw std::runtime_error("envire::types::Plane serialize not implemented");
                }
            };
        }
    }
}
