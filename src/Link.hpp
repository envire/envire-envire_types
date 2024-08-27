#pragma once

#include "EnvireTypeBase.hpp"

#include <base/Eigen.hpp>
#include <configmaps/ConfigMap.hpp>
#include <envire_core/plugin/Plugin.hpp>

namespace envire
{
    namespace types
    {
        class Link : public EnvireTypeBase
        {
        public:
            Link() {}

            Link(const configmaps::ConfigMap& configMap) : EnvireTypeBase(configMap)
            {
                name_ = configMap_["name"].toString();

                // we avoid the value dublication
                // delete the keys, since we stored their values as class parameters
                configMap_.erase("name");
            }

            std::string getType() const override
            {
                return "link";
            }

            configmaps::ConfigMap getFullConfigMap() const override
            {
                configmaps::ConfigMap config;
                config.append(configMap_);
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

