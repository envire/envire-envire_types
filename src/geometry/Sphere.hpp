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
            class Sphere : public EnvireTypeBase
            {
            public:
                Sphere() : Sphere(std::string(), 0.)
                {}

                Sphere(std::string name, double radius) : EnvireTypeBase(name), radius(radius)
                {}

                // TODO: store other values in configMap_ in the configMap_ variable
                Sphere(const configmaps::ConfigMap& configMap) : EnvireTypeBase(configMap)
                {
                    if (configMap_.hasKey("name") && configMap_.hasKey("radius"))
                    {
                        name_ = configMap_["name"].toString();
                        radius = configMap_["radius"];

                        // store all additional values in the configMap_ parameter
                        configMap_.erase("name");
                        configMap_.erase("radius");

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
                        configMap_.clear();
                    }
                }

                std::string getType() const override
                {
                    return "sphere";
                }

                double radius;
                std::shared_ptr<Material> material;

                configmaps::ConfigMap getFullConfigMap() const override
                {
                    configmaps::ConfigMap config;
                    config.append(configMap_);
                    config["name"] = getName();
                    config["type"] = getType();
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
