#include <type_traits>

namespace Pineapple
{

template <typename Header, typename Body>
struct HeadedMessage
{
    Header header{};
    Body body{};
};

template <typename Archive, typename Header, typename Body>
void serialize(Archive& archive, HeadedMessage<Header, Body>& message)
{
    archive(message.header, message.body);
}

};
