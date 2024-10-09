/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** OwnedMessage
*/

#ifndef OWNEDMESSAGE_HPP_
#define OWNEDMESSAGE_HPP_

#include <memory>

namespace rtype {
    namespace network {
        template <typename T>
        class NetworkConnection;
        template <typename T>
        struct OwnedMessage
        {
            std::shared_ptr<NetworkConnection<T>> remoteConnection;
            Message<T> message;

            friend std::ostream& operator<<(std::ostream& os, const OwnedMessage<T>& message) {
                os << message.message;
                return os;
            }
        };
    }
}

#endif /* !OWNEDMESSAGE_HPP_ */
