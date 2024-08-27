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
            class Plane : public EnvireTypeBase
            {
            public:
                Plane() : Plane(std::string(), base::Vector2d(0., 0.))
                {}

                Plane(std::string name, base::Vector2d size) : EnvireTypeBase(name), size(size)
                {}

                // TODO: store other values in configMap_ in the configMap_ variable
                Plane(const configmaps::ConfigMap& configMap) : EnvireTypeBase(configMap)
                {
                    if (configMap_.hasKey("name") && configMap_.hasKey("size")
                        && configMap_["size"].hasKey("x") && configMap_["size"].hasKey("y"))
                    {
                        name_ = configMap_["name"].toString();
                        size.x() = configMap_["size"]["x"];
                        size.y() = configMap_["size"]["y"];

                        // store all additional values in the configMap_ parameter
                        configMap_.erase("name");
                        configMap_.erase("size");

                        if (configMap_.hasKey("material"))
                        {
                            material = std::make_shared<Material>(configMap_["material"]);
                            configMap_.erase("material");
                        }
                    }
                    else
                    {
                        LOG_ERROR_S << "The config map has no all required keys";
                        size = base::Vector2d::Zero();
                        configMap_.clear();
                    }
                }

                std::string getType() const override
                {
                    return "plane";
                }

                base::Vector2d size;
                std::shared_ptr<Material> material;

                configmaps::ConfigMap getFullConfigMap() const override
                {
                    configmaps::ConfigMap config;
                    config.append(configMap_);
                    config["name"] = getName();
                    config["type"] = getType();
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
