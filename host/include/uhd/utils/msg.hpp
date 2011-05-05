//
// Copyright 2011 Ettus Research LLC
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef INCLUDED_UHD_UTILS_MSG_HPP
#define INCLUDED_UHD_UTILS_MSG_HPP

#include <uhd/config.hpp>
#include <ostream>
#include <string>

/*!
 * A UHD message macro with configurable type.
 * Usage: UHD_MSG(warning) << "some warning message" << std::endl;
 */
#define UHD_MSG(type) \
    uhd::msg::_msg(uhd::msg::type)


namespace uhd{ namespace msg{

    //! Possible message types
    enum type_t{
        status  = 's',
        warning = 'w',
        error   = 'e',
    };

    //! Typedef for a user-registered message handler
    typedef void (*handler_t)(type_t, const std::string &);

    /*!
     * Register the handler for uhd system messages.
     * Only one handler can be registered at once.
     * This replaces the default std::cout/cerr handler.
     * \param handler a new handler callback function
     */
    UHD_API_FUTURE void register_handler(const handler_t &handler);

    //! Internal message object (called by UHD_MSG macro)
    struct UHD_API_FUTURE _msg{
        _msg(const type_t type);
        ~_msg(void);

        std::ostream &get(void);

        template <typename T> std::ostream &operator<<(const T &x){
            return get() << x;
        }
    };

}} //namespace uhd::msg

#endif /* INCLUDED_UHD_UTILS_MSG_HPP */
