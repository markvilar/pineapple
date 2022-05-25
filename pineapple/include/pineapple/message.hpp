#include <type_traits>

namespace Pineapple
{

template <typename Header, typename Body>
struct Message
{
    Header header{};
    Body body{};
};

template <typename Archive, typename Header, typename Body>
void serialize(Archive& archive, Message<Header, Body>& message)
{
    archive(message.header, message.body);
}

};
