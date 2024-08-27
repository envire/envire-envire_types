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
            Inertial(configmaps::ConfigMap configMap)
            {
                name_ = configMap["name"].toString();
                mass = configMap["mass"];
                xx = configMap["xx"];
                xy = configMap["xy"];
                xz = configMap["xz"];
                yy = configMap["yy"];
                yz = configMap["yz"];
                zz = configMap["zz"];

                // we avoid the value dublication
                // delete the keys, since we stored their values as class parameters
                configMap.erase("name");
                configMap.erase("mass");
                configMap.erase("xx");
                configMap.erase("xy");
                configMap.erase("xz");
                configMap.erase("yy");
                configMap.erase("yz");
                configMap.erase("zz");

                this->configMap = configMap;
            }

            std::string getType() const override
            {
                return "inertial";
            }

                        configmaps::ConfigMap configMap;

            double mass;
            double xx,xy,xz,yy,yz,zz;

            configmaps::ConfigMap getFullConfigMap() const override
            {
                configmaps::ConfigMap config;
                config.append(configMap);
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
        };
    }
}
