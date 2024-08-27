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
            class Capsule : public EnvireTypeBase
            {
            public:
                Capsule() : Capsule(std::string(), 0., 0.)
                {}

                Capsule(std::string name, double radius, double length) : EnvireTypeBase(name), radius(radius), length(length)
                {}

                Capsule(const configmaps::ConfigMap& configMap) : EnvireTypeBase(configMap)
                {
                    if (configMap_.hasKey("name") && configMap_.hasKey("radius") && configMap_.hasKey("length"))
                    {
                        name_ = configMap_["name"].toString();
                        radius = configMap_["radius"];
                        length = configMap_["length"];

                        // store all additional values in the configMap_ parameter
                        configMap_.erase("name");
                        configMap_.erase("radius");
                        configMap_.erase("length");

                        if (configMap_.hasKey("material"))
                        {
                            material = std::make_shared<Material>(configMap_["material"]);
                            configMap_.erase("material");
                        }
                    }
                    else
                    {
                        LOG_ERROR_S << "The config map has no all required keys";
                        radius = 0.;
                        length = 0.;
                        configMap_.clear();
                    }
                }

                std::string getType() const override
                {
                    return "capsule";
                }

                double radius;
                double length;
                std::shared_ptr<Material> material;

                configmaps::ConfigMap getFullConfigMap() const override
                {
                    configmaps::ConfigMap config;
                    config.append(configMap_);
                    config["name"] = getName();
                    config["type"] = getType();
                    config["radius"] = radius;
                    config["length"] = length;
                    if (material != nullptr)
                    {
                        config["material"] = material->getFullConfigMap();
                    }
                    return config;
                }

                /**Grants access to boost serialization */
                friend class boost::serialization::access;

                /**Serializes the members of this class*/
                template <typename Archive>
                void serialize(Archive &ar, const unsigned int version)
                {
                    throw std::runtime_error("envire::types::Capsule serialize not implemented");
                }
            };
        }
    }
}
