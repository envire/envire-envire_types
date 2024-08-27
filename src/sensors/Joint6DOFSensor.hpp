#pragma once

#include "../EnvireTypeBase.hpp"

#include <string>
#include <configmaps/ConfigMap.hpp>
#include <base-logging/Logging.hpp>
#include <boost/serialization/access.hpp>


namespace envire
{
    namespace types
    {
        namespace sensors
        {
            class Joint6DOFSensor : public EnvireTypeBase
            {
            public:
                Joint6DOFSensor() {}

                Joint6DOFSensor(configmaps::ConfigMap configMap) : EnvireTypeBase(configMap)
                {
                    if (configMap_.hasKey("name")
                        && configMap_.hasKey("link")
                        && configMap_.hasKey("joint"))
                    {
                        name_ = configMap_["name"].toString();

                        // we avoid the value dublication
                        // delete the keys, since we stored their values as class parameters
                        configMap_.erase("name");
                    }
                    else
                    {
                        LOG_ERROR_S << "The config map has no all required keys";
                        configMap_.clear();
                    }
                }

                std::string getType() const override
                {
                    return "joint6dof";
                }

                configmaps::ConfigMap getFullConfigMap() const override
                {
                    configmaps::ConfigMap config;
                    config.append(configMap_);
                    config["name"] = getName();
                    return config;
                }

                /**Grants access to boost serialization */
                friend class boost::serialization::access;

                /**Serializes the members of this class*/
                template <typename Archive>
                void serialize(Archive &ar, const unsigned int version)
                {
                    throw std::runtime_error("envire::types::Joint6DOFSensor serialize not implemented");
                }
            };
        }
    }
}
