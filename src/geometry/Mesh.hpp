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
            class Mesh : public EnvireTypeBase
            {
            public:
                Mesh() : Mesh(std::string(), std::string())
                {}

                Mesh(const std::string& name, const std::string& filename) : Mesh(name, filename, base::Vector3d(1., 1., 1.))
                {}

                Mesh(const std::string& name, const std::string& filename, const base::Vector3d& scale)
                    : EnvireTypeBase(name), filename(filename), scale(scale)
                {}

                // TODO: store other values in configMap_ in the configMap_ variable
                Mesh(const configmaps::ConfigMap& configMap) : EnvireTypeBase(configMap)
                {
                    if (configMap_.hasKey("name") && configMap_.hasKey("filename") && configMap_.hasKey("scale") &&
                        configMap_["scale"].hasKey("x") && configMap_["scale"].hasKey("y") && configMap_["scale"].hasKey("z"))
                    {
                        name_ = configMap_["name"].toString();
                        filename = configMap_["filename"].toString();
                        scale.x() = configMap_["scale"]["x"];
                        scale.y() = configMap_["scale"]["y"];
                        scale.z() = configMap_["scale"]["z"];

                        // store all additional values in the configMap_ parameter
                        configMap_.erase("name");
                        configMap_.erase("filename");
                        configMap_.erase("scale");

                        if (configMap_.hasKey("material"))
                        {
                            material = std::make_shared<Material>(configMap_["material"]);
                            configMap_.erase("material");
                        } else
                            material = nullptr;

                    }
                    else
                    {
                        LOG_ERROR_S << "The config map has no all required keys";
                        filename = std::string();
                        scale = base::Vector3d::Zero();
                        configMap_.clear();
                    }
                }

                std::string getType() const override
                {
                    return "mesh";
                }

                configmaps::ConfigMap getFullConfigMap() const override
                {
                    configmaps::ConfigMap config;
                    config.append(configMap_);
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
            private:
                std::string filename;
                base::Vector3d scale;
                std::shared_ptr<Material> material;
            };
        }
    }
}
