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
            class Box: public EnvireTypeBase
            {
            public:
                Box() : Box(std::string(), base::Vector3d::Zero()) {}
                Box(std::string name, base::Vector3d size) : name(name), size(size) {}
                Box(configmaps::ConfigMap &configMap_) : configMap(configMap_)
                {
                    if (configMap.hasKey("name") && configMap.hasKey("size")
                        && configMap["size"].hasKey("x") && configMap["size"].hasKey("y") && configMap["size"].hasKey("z"))
                    {
                        name = configMap["name"].toString();
                        size.x() = configMap["size"]["x"];
                        size.y() = configMap["size"]["y"];
                        size.z() = configMap["size"]["z"];

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
                        size = base::Vector3d::Zero();
                        configMap.clear();
                    }
                }

                std::string name;
                static inline std::string const type = "box";
                base::Vector3d size;
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
                    config["size"]["z"] = size.z();
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
                    throw std::runtime_error("envire::types::Box serialize not implemented");
                }
            };
        }
    }
}
