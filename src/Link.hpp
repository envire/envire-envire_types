#pragma once

#include <base/Eigen.hpp>
#include <configmaps/ConfigMap.hpp>
#include <envire_core/plugin/Plugin.hpp>

namespace envire
{
    namespace types
    {
        struct Link
        {
            Link() {}
            Link(configmaps::ConfigMap configMap)
            {
                name = configMap["name"].toString();

                // we avoid the value dublication
                // delete the keys, since we stored their values as class parameters
                configMap.erase("name");

                this->configMap = configMap;
            }

            std::string name;
            static inline std::string const type = "link";
            configmaps::ConfigMap configMap;

            configmaps::ConfigMap getFullConfigMap()
            {
                configmaps::ConfigMap config;
                config.append(configMap);
                config["name"] = name;
                config["type"] = type;
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

