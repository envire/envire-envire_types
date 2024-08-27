#pragma once

#include "../EnvireTypeBase.hpp"

#include <string>
#include <boost/serialization/access.hpp>
#include <base/Eigen.hpp>
#include <base-logging/Logging.hpp>
#include <configmaps/ConfigMap.hpp>
#include "Material.hpp"
namespace envire
{
    namespace types
    {
        namespace geometry
        {
            class Mesh: public EnvireTypeBase
            {
            public:
                Mesh() : Mesh(std::string(), std::string()) {}
                Mesh(std::string name, std::string filename) : Mesh(name, filename, base::Vector3d(1., 1., 1.)) {}
                Mesh(std::string name, std::string filename, base::Vector3d scale) : EnvireTypeBase(name), filename(filename), scale(scale) {}
                // TODO: store other values in configMap in the configMap variable
                Mesh(configmaps::ConfigMap &configMap_) : configMap(configMap_)
                {
                    if (configMap.hasKey("name") && configMap.hasKey("filename") && configMap.hasKey("scale") &&
                        configMap["scale"].hasKey("x") && configMap["scale"].hasKey("y") && configMap["scale"].hasKey("z"))
                    {
                        name_ = configMap["name"].toString();
                        filename = configMap["filename"].toString();
                        scale.x() = configMap["scale"]["x"];
                        scale.y() = configMap["scale"]["y"];
                        scale.z() = configMap["scale"]["z"];

                        // store all additional values in the configMap parameter
                        configMap.erase("name");
                        configMap.erase("filename");
                        configMap.erase("scale");

                        if (configMap.hasKey("material"))
                        {
                            material = std::make_shared<Material>(configMap["material"]);
                            configMap.erase("material");
                        } else
                            material = nullptr;

                    }
                    else
                    {
                        LOG_ERROR_S << "The config map has no all required keys";
                        filename = std::string();
                        scale = base::Vector3d::Zero();
                        configMap.clear();
                    }
                }

                std::string getType() const override
                {
                    return "mesh";
                }

                std::string filename;
                base::Vector3d scale;
                std::shared_ptr<Material> material;
                configmaps::ConfigMap configMap;

                configmaps::ConfigMap getFullConfigMap() const override
                {
                    configmaps::ConfigMap config;
                    config.append(configMap);
                    config["name"] = getName();
                    config["type"] = getType();
                    config["filename"] = filename;
                    config["scale"]["x"] = scale.x();
                    config["scale"]["y"] = scale.y();
                    config["scale"]["z"] = scale.z();
                    if (material != nullptr)
                        config["material"] = material->getFullConfigMap();
                    return config;
                }

                /**Grants access to boost serialization */
                friend class boost::serialization::access;

                /**Serializes the members of this class*/
                template <typename Archive>
                void serialize(Archive &ar, const unsigned int version)
                {
                    throw std::runtime_error("envire::types::Mesh serialize not implemented");
                }
            };
        }
    }
}
