#pragma once

#include "../EnvireTypeBase.hpp"

#include <string>
#include <boost/serialization/access.hpp>
#include <base-logging/Logging.hpp>
#include <configmaps/ConfigMap.hpp>
#include "Material.hpp"
namespace envire
{
    namespace types
    {
        namespace geometry
        {
            class Sphere: public EnvireTypeBase
            {
            public:
                Sphere() : Sphere(std::string(), 0.) {}
                Sphere(std::string name, double radius) : name(name), radius(radius) {}
                // TODO: store other values in configMap in the configMap variable
                Sphere(configmaps::ConfigMap &configMap_) : configMap(configMap_)
                {
                    if (configMap.hasKey("name") && configMap.hasKey("radius"))
                    {
                        name = configMap["name"].toString();
                        radius = configMap["radius"];

                        // store all additional values in the configMap parameter
                        configMap.erase("name");
                        configMap.erase("radius");

                        if (configMap.hasKey("material"))
                        {
                            material = std::make_shared<Material>(configMap["material"]);
                            configMap.erase("material");
                        }
                    }
                    else
                    {
                        LOG_ERROR_S << "The config map has no all required keys";
                        radius = 0.;
                        configMap.clear();
                    }
                }

                std::string name;
                static inline std::string const type = "sphere";
                double radius;
                std::shared_ptr<Material> material;
                configmaps::ConfigMap configMap;

                configmaps::ConfigMap getFullConfigMap()
                {
                    configmaps::ConfigMap config;
                    config.append(configMap);
                    config["name"] = name;
                    config["type"] = type;
                    config["radius"] = radius;
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
                    throw std::runtime_error("envire::types::Sphere serialize not implemented");
                }
            };
        }
    }
}
