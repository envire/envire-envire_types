#pragma once

#include "../EnvireTypeBase.hpp"

#include <string>
#include <base/Eigen.hpp>
#include <base-logging/Logging.hpp>
#include <boost/serialization/access.hpp>
#include <configmaps/ConfigMap.hpp>

namespace envire
{
    namespace types
    {
        namespace joints
        {
            class Revolute : public EnvireTypeBase
            {
            public:
                Revolute() {}

                Revolute(configmaps::ConfigMap configMap_) : EnvireTypeBase(configMap_)
                {
                    if (configMap.hasKey("name") && configMap.hasKey("axis")
                        && configMap["axis"].hasKey("x") && configMap["axis"].hasKey("y") && configMap["axis"].hasKey("z")
                        && configMap.hasKey("minPosition") && configMap.hasKey("maxPosition")
                        && configMap.hasKey("maxEffort") && configMap.hasKey("maxVelocity"))
                    {
                        name_ = configMap["name"].toString();
                        axis = base::Vector3d(configMap["axis"]["x"], configMap["axis"]["y"], configMap["axis"]["z"]);
                        minPosition = configMap["minPosition"];
                        maxPosition = configMap["maxPosition"];
                        maxEffort = configMap["maxEffort"];
                        maxVelocity = configMap["maxVelocity"];

                        // we avoid the value dublication
                        // delete the keys, since we stored their values as class parameters
                        configMap.erase("name");
                        configMap.erase("axis");
                        configMap.erase("minPosition");
                        configMap.erase("maxPosition");
                        configMap.erase("maxEffort");
                        configMap.erase("maxVelocity");
                    }
                    else
                    {
                        LOG_ERROR_S << "The config map has no all required keys";
                        axis = base::Vector3d::Zero();
                        configMap.clear();
                    }
                }

                std::string getType() const override
                {
                    return "revolute";
                }

                base::Vector3d axis;
                double minPosition;
                double maxPosition;
                double maxEffort;
                double maxVelocity;

                configmaps::ConfigMap getFullConfigMap() const override
                {
                    configmaps::ConfigMap config;
                    config.append(configMap);
                    config["name"] = getName();
                    config["type"] = getType();
                    config["axis"]["x"] = axis.x();
                    config["axis"]["y"] = axis.y();
                    config["axis"]["z"] = axis.z();
                    config["minPosition"] = minPosition;
                    config["maxPosition"] = maxPosition;
                    config["maxEffort"] = maxEffort;
                    config["maxVelocity"] = maxVelocity;
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
