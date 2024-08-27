#pragma once

#include <string>
#include <boost/serialization/access.hpp>
#include <base/Eigen.hpp>
#include <base-logging/Logging.hpp>
#include <configmaps/ConfigMap.hpp>

namespace envire
{
    namespace types
    {
        namespace geometry
        {
            struct Color
            {
                Color() : r(0), g(0), b(0), a(1) {}
                Color(configmaps::ConfigMap &configMap)
                {
                    if (configMap.hasKey("r") && configMap.hasKey("g") && configMap.hasKey("b"))
                    {
                        r = configMap["r"];
                        g = configMap["g"];
                        b = configMap["b"];

                    }

                    if (configMap.hasKey("a"))
                    {
                        a = configMap["a"];
                    } else {
                        a = 1.0;
                    }
                }

                double r;
                double g;
                double b;
                double a;

                configmaps::ConfigMap getFullConfigMap()
                {
                    configmaps::ConfigMap config;
                    config["r"] = r;
                    config["g"] = g;
                    config["b"] = b;
                    config["a"] = a;
                    return config;
                }
            };

            struct Material
            {
                Material() {}
                Material(configmaps::ConfigMap &configMap_) : configMap(configMap_)
                {
                    if (configMap.hasKey("name"))
                    {
                        name = configMap["name"].toString();
                        configMap.erase("name");
                    }
                    if (configMap.hasKey("ambientColor"))
                    {
                        ambientColor = Color(configMap["ambientColor"]);
                        configMap.erase("ambientColor");
                    }

                    if (configMap.hasKey("diffuseColor"))
                    {
                        diffuseColor = Color(configMap["diffuseColor"]);
                        configMap.erase("diffuseColor");
                    }

                    if (configMap.hasKey("specularColor"))
                    {
                        specularColor = Color(configMap["specularColor"]);
                        configMap.erase("specularColor");
                    }

                    if (configMap.hasKey("shininess"))
                    {
                        shininess = configMap["shininess"];
                        configMap.erase("shininess");
                    }

                    if (configMap.hasKey("textureFilename"))
                    {
                        textureFilename = configMap["textureFilename"].toString();
                        configMap.erase("textureFilename");
                    }
                }

                std::string name;
                static inline std::string const type = "material";
                Color ambientColor;
                Color diffuseColor;
                Color specularColor;
                double shininess;
                std::string textureFilename;
                configmaps::ConfigMap configMap;

                configmaps::ConfigMap getFullConfigMap()
                {
                    configmaps::ConfigMap config;
                    config.append(configMap);
                    config["name"] = name;
                    config["type"] = type;
                    config["ambientColor"] = ambientColor.getFullConfigMap();
                    config["diffuseColor"] = diffuseColor.getFullConfigMap();
                    config["specularColor"] = specularColor.getFullConfigMap();
                    config["shininess"] = shininess;
                    config["textureFilename"] = textureFilename;
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
