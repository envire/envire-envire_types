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
            class Heightfield: public EnvireTypeBase
            {
            public:
                Heightfield() : Heightfield(std::string()) {}
                Heightfield(std::string name) : EnvireTypeBase(name) {}
                Heightfield(configmaps::ConfigMap &configMap_) : configMap(configMap_)
                {
                    if (configMap.hasKey("name"))
                    {
                        name_ = configMap["name"].toString();

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

                std::string getType() const override
                {
                    return "heightfield";
                }

                std::shared_ptr<Material> material;
                configmaps::ConfigMap configMap;

                configmaps::ConfigMap getFullConfigMap() const override
                {
                    configmaps::ConfigMap config;
                    config.append(configMap);
                    config["name"] = getName();
                    config["type"] = getType();
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
