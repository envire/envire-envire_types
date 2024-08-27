#pragma once

#include <string>


namespace envire
{
    namespace types
    {
        class EnvireTypeBase
        {
        public:
            EnvireTypeBase() = default;
            virtual ~EnvireTypeBase() = default;

            virtual std::string getType() const = 0;
            // TODO
        };
    }
}
