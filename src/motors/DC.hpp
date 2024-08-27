#pragma once

#include "../EnvireTypeBase.hpp"

#include <string>
#include <base/Eigen.hpp>
#include <base-logging/Logging.hpp>
#include <configmaps/ConfigMap.hpp>


namespace envire
{
    namespace types
    {
        namespace motors
        {
            class DC : public EnvireTypeBase
            {
            public:
                DC() {}

                DC(configmaps::ConfigMap configMap) : EnvireTypeBase(configMap)
                {
                    if (configMap_.hasKey("name")
                        && configMap_.hasKey("minValue") && configMap_.hasKey("maxValue")
                        && configMap_.hasKey("maxEffort") && configMap_.hasKey("maxSpeed"))
                    {
                        name_ = configMap_["name"].toString();
                        minPosition = configMap_["minValue"];
                        maxPosition = configMap_["maxValue"];
                        maxEffort = configMap_["maxEffort"];
                        maxSpeed = configMap_["maxSpeed"];

                        // we avoid the value dublication
                        // delete the keys, since we stored their values as class parameters
                        configMap_.erase("name");
                        configMap_.erase("minValue");
                        configMap_.erase("maxValue");
                        configMap_.erase("maxEffort");
                        configMap_.erase("maxSpeed");
                    }
                    else
                    {
                        LOG_ERROR_S << "The config map has no all required keys";
                        configMap_.clear();
                    }
                }

                std::string getType() const override
                {
                    return "DC";
                }

                double minPosition;
                double maxPosition;
                double maxEffort;
                double maxSpeed;

                configmaps::ConfigMap getFullConfigMap() const override
                {
                    configmaps::ConfigMap config;
                    config.append(configMap_);
                    config["name"] = getName();
                    config["type"] = getType();
                    config["minPosition"] = minPosition;
                    config["maxPosition"] = maxPosition;
                    config["maxEffort"] = maxEffort;
                    config["maxSpeed"] = maxSpeed;
                    return config;
                }

                /**Grants access to boost serialization */
                friend class boost::serialization::access;

                /**Serializes the members of this class*/
                template <typename Archive>
                void serialize(Archive &ar, const unsigned int version)
                {
                    throw std::runtime_error("envire::types::MotorDC serialize not implemented");
                }
            };
        }
    }
}
