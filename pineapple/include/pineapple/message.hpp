#pragma once

#include <type_traits>

namespace pineapple
{

template <typename Header, typename Body>
struct Message
{
    using HeaderType = Header;
    using BodyType = Body;

    Header header{};
    Body body{};
};

template <typename Archive, typename Header, typename Body>
auto serialize(Archive& archive, Message<Header, Body>& message)
{
    archive(message.header, message.body);
}

template <typename Archive, typename Header, typename Body>
auto serialize(Archive& archive, const Message<Header, Body>& message)
{
    archive(message.header, message.body);
}

}; // namespace pineapple
