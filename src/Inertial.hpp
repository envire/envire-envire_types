#pragma once

#include <base/Eigen.hpp>
#include <configmaps/ConfigMap.hpp>
#include <envire_core/plugin/Plugin.hpp>

// TODO: add constructor with configmap

namespace envire
{
    namespace types
    {
        struct Inertial
        {
            Inertial() {}
            Inertial(configmaps::ConfigMap configMap) {
                name = configMap["name"].toString();
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

            std::string name;
            const std::string& getName() const
            {
                return name;
            }
            static inline std::string const type = "inertial";
            configmaps::ConfigMap configMap;

            double mass;
            double xx,xy,xz,yy,yz,zz;

            configmaps::ConfigMap getFullConfigMap() {
                configmaps::ConfigMap config;
                config.append(configMap);
                config["name"] = name;
                config["type"] = type;
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
