#pragma once

#include <string>


namespace envire
{
    namespace types
    {
        class EnvireTypeBase
        {
        public:
            EnvireTypeBase() : name_{"NOT SET"} {}
            EnvireTypeBase(const std::string& name) : name_{name} {}
            virtual ~EnvireTypeBase() = default;

            virtual std::string getType() const = 0;
            const std::string& getName() const
            {
                return name_;
            }

        protected:
            std::string name_;
        };
    }
}
