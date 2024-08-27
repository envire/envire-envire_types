#pragma once

#include "EnvireTypeBase.hpp"

#include <base/Eigen.hpp>
#include <configmaps/ConfigMap.hpp>
#include <envire_core/plugin/Plugin.hpp>

namespace envire
{
    namespace types
    {
        class Link: public EnvireTypeBase
        {
        public:
            Link() {}
            Link(configmaps::ConfigMap configMap)
            {
                name_ = configMap["name"].toString();

                // we avoid the value dublication
                // delete the keys, since we stored their values as class parameters
                configMap.erase("name");

                this->configMap = configMap;
            }

            std::string getType() const override
            {
                return "link";
            }

            configmaps::ConfigMap configMap;

            configmaps::ConfigMap getFullConfigMap()
            {
                configmaps::ConfigMap config;
                config.append(configMap);
                config["name"] = getName();
                config["type"] = getType();
                return config;
            }

            /**Grants access to boost serialization */
            friend class boost::serialization::access;

            /**Serializes the members of this class*/
            template <typename Archive>
            void serialize(Archive &ar, const unsigned int version)
            {
                throw std::runtime_error("envire::types::Link::serialize not implemented");
            }
        };
    }
}

