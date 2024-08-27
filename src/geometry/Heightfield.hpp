#pragma once

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
            struct Heightfield
            {
                Heightfield() : Heightfield(std::string()) {}
                Heightfield(std::string name) : name(name) {}
                Heightfield(configmaps::ConfigMap &configMap_) : configMap(configMap_)
                {
                    if (configMap.hasKey("name"))
                    {
                        name = configMap["name"].toString();

                        // store all additional values in the configMap parameter
                        configMap.erase("name");

                        if (configMap.hasKey("material"))
                        {
                            material = std::make_shared<Material>(configMap["material"]);
                            configMap.erase("material");
                        }
                    }
                    else
                    {
                        LOG_ERROR_S << "The config map has no all required keys";
                        configMap.clear();
                    }
                }

                std::string name;
                const std::string& getName() const
                {
                    return name;
                }
                static inline std::string const type = "heightfield";
                std::shared_ptr<Material> material;
                configmaps::ConfigMap configMap;

                configmaps::ConfigMap getFullConfigMap() {
                    configmaps::ConfigMap config;
                    config.append(configMap);
                    config["name"] = name;
                    config["type"] = type;
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
                    throw std::runtime_error("envire::types::Heightfield serialize not implemented");
                }
            };
        }
    }
}
