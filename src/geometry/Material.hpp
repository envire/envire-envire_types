#pragma once

#include "../EnvireTypeBase.hpp"

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
                Color() : r(0), g(0), b(0), a(1)
                {}

                Color(configmaps::ConfigMap configMap)
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
                    }
                    else
                    {
                        a = 1.0;
                    }
                }

                double r;
                double g;
                double b;
                double a;

                configmaps::ConfigMap getFullConfigMap() const
                {
                    configmaps::ConfigMap config;
                    config["r"] = r;
                    config["g"] = g;
                    config["b"] = b;
                    config["a"] = a;
                    return config;
                }
            };

            class Material : public EnvireTypeBase
            {
            public:
                Material() {}

                Material(const configmaps::ConfigMap& configMap) : EnvireTypeBase(configMap)
                {
                    if (configMap_.hasKey("name"))
                    {
                        name_ = configMap_["name"].toString();
                        configMap_.erase("name");
                    }
                    if (configMap_.hasKey("ambientColor"))
                    {
                        ambientColor = Color(configMap_["ambientColor"]);
                        configMap_.erase("ambientColor");
                    }

                    if (configMap_.hasKey("diffuseColor"))
                    {
                        diffuseColor = Color(configMap_["diffuseColor"]);
                        configMap_.erase("diffuseColor");
                    }

                    if (configMap_.hasKey("specularColor"))
                    {
                        specularColor = Color(configMap_["specularColor"]);
                        configMap_.erase("specularColor");
                    }

                    if (configMap_.hasKey("shininess"))
                    {
                        shininess = configMap_["shininess"];
                        configMap_.erase("shininess");
                    }

                    if (configMap_.hasKey("textureFilename"))
                    {
                        textureFilename = configMap_["textureFilename"].toString();
                        configMap_.erase("textureFilename");
                    }
                }

                std::string getType() const override
                {
                    return "material";
                }

                configmaps::ConfigMap getFullConfigMap() const override
                {
                    configmaps::ConfigMap config;
                    config.append(configMap_);
                    config["name"] = getName();
                    config["type"] = getType();
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
            private:
                Color ambientColor;
                Color diffuseColor;
                Color specularColor;
                double shininess;
                std::string textureFilename;
            };
        }
    }
}
