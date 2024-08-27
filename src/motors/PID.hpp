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
            class PID : public EnvireTypeBase
            {
            public:
                PID() {}
                PID(configmaps::ConfigMap configMap) : EnvireTypeBase(configMap)
                {
                    if (configMap_.hasKey("name")
                        && configMap_.hasKey("p") && configMap_.hasKey("i") && configMap_.hasKey("d")
                        && configMap_.hasKey("minValue") && configMap_.hasKey("maxValue")
                        && configMap_.hasKey("maxEffort") && configMap_.hasKey("maxSpeed"))
                    {
                        name_ = configMap_["name"].toString();
                        p = configMap_["p"];
                        i = configMap_["i"];
                        d = configMap_["d"];
                        minPosition = configMap_["minValue"];
                        maxPosition = configMap_["maxValue"];
                        maxEffort = configMap_["maxEffort"];
                        maxSpeed = configMap_["maxSpeed"];

                        // we avoid the value dublication
                        // delete the keys, since we stored their values as class parameters
                        configMap_.erase("name");
                        configMap_.erase("p");
                        configMap_.erase("i");
                        configMap_.erase("d");
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
                    return "PID";
                }

                double p;
                double i;
                double d;
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
                    config["p"] = p;
                    config["i"] = i;
                    config["d"] = d;
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
                    throw std::runtime_error("envire::types::MotorPID serialize not implemented");
                }
            };
        }
    }
}
