#pragma once

#include "../EnvireTypeBase.hpp"

#include <string>
#include <base/Eigen.hpp>
#include <base-logging/Logging.hpp>
#include <boost/serialization/access.hpp>
#include <configmaps/ConfigMap.hpp>

// TODO: motors has maxSpeed and joint maxVelocity, find one config name
namespace envire
{
    namespace types
    {
        namespace joints
        {
            class Continuous : public EnvireTypeBase
            {
            public:
                Continuous() {}

                Continuous(const configmaps::ConfigMap& configMap) : EnvireTypeBase(configMap)
                {
                    if (configMap_.hasKey("name") && configMap_.hasKey("axis")
                        && configMap_["axis"].hasKey("x") && configMap_["axis"].hasKey("y") && configMap_["axis"].hasKey("z")
                        && configMap_.hasKey("maxEffort") && configMap_.hasKey("maxVelocity"))
                    {
                        name_ = configMap_["name"].toString();
                        axis = base::Vector3d(configMap_["axis"]["x"], configMap_["axis"]["y"], configMap_["axis"]["z"]);
                        maxEffort = configMap_["maxEffort"];
                        maxVelocity = configMap_["maxVelocity"];

                        // we avoid the value dublication
                        // delete the keys, since we stored their values as class parameters
                        configMap_.erase("name");
                        configMap_.erase("axis");
                        configMap_.erase("maxEffort");
                        configMap_.erase("maxVelocity");
                    }
                    else
                    {
                        LOG_ERROR_S << "The config map has no all required keys";
                        axis = base::Vector3d::Zero();
                        configMap_.clear();
                    }
                }

                std::string getType() const override
                {
                    return "continuous";
                }

                configmaps::ConfigMap getFullConfigMap() const override
                {
                    configmaps::ConfigMap config;
                    config.append(configMap_);
                    config["name"] = getName();
                    config["type"] = getType();
                    config["axis"]["x"] = axis.x();
                    config["axis"]["y"] = axis.y();
                    config["axis"]["z"] = axis.z();
                    config["maxEffort"] = maxEffort;
                    config["maxVelocity"] = maxVelocity;
                    return config;
                }

                const base::Vector3d& getAxis() const
                {
                    return axis;
                }

                /**Grants access to boost serialization */
                friend class boost::serialization::access;

                /**Serializes the members of this class*/
                template <typename Archive>
                void serialize(Archive &ar, const unsigned int version)
                {
                    throw std::runtime_error("envire::types::Box serialize not implemented");
                }

            private:
                base::Vector3d axis;
                double maxEffort;
                double maxVelocity;
            };
        }
    }
}
