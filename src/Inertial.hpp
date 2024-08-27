#pragma once

#include "EnvireTypeBase.hpp"

#include <base/Eigen.hpp>
#include <configmaps/ConfigMap.hpp>
#include <envire_core/plugin/Plugin.hpp>


namespace envire
{
    namespace types
    {
        class Inertial: public EnvireTypeBase
        {
        public:
            Inertial() {}

            Inertial(const configmaps::ConfigMap& configMap) : EnvireTypeBase(configMap)
            {
                name_ = configMap_["name"].toString();
                mass = configMap_["mass"];
                xx = configMap_["xx"];
                xy = configMap_["xy"];
                xz = configMap_["xz"];
                yy = configMap_["yy"];
                yz = configMap_["yz"];
                zz = configMap_["zz"];

                // we avoid the value dublication
                // delete the keys, since we stored their values as class parameters
                configMap_.erase("name");
                configMap_.erase("mass");
                configMap_.erase("xx");
                configMap_.erase("xy");
                configMap_.erase("xz");
                configMap_.erase("yy");
                configMap_.erase("yz");
                configMap_.erase("zz");
            }

            std::string getType() const override
            {
                return "inertial";
            }

            configmaps::ConfigMap getFullConfigMap() const override
            {
                configmaps::ConfigMap config;
                config.append(configMap_);
                config["name"] = getName();
                config["type"] = getType();
                config["mass"] = mass;
                config["xx"] = xx;
                config["xy"] = xy;
                config["xz"] = xz;
                config["yy"] = yy;
                config["yz"] = yz;
                config["zz"] = zz;

                return config;
            }

            /**Grants access to boost serialization */
            friend class boost::serialization::access;

            /**Serializes the members of this class*/
            template <typename Archive>
            void serialize(Archive &ar, const unsigned int version)
            {
                throw std::runtime_error("envire::types::Inertial::serialize not implemented");
            }

        private:
            double mass;
            double xx;
            double xy;
            double xz;
            double yy;
            double yz;
            double zz;
        };
    }
}
