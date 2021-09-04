//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/url
//

#ifndef BOOST_URL_RFC_IMPL_PORT_IPP
#define BOOST_URL_RFC_IMPL_PORT_IPP

#include <boost/url/rfc/port.hpp>
#include <boost/url/rfc/char_sets.hpp>
#include <boost/url/bnf/parse.hpp>
#include <boost/url/bnf/token.hpp>

namespace boost {
namespace urls {
namespace rfc {

char const*
parse(
    char const* const start,
    char const* const end,
    error_code& ec,
    port& t)
{
    using namespace bnf;
    string_view s;
    auto it = parse(
        start, end, ec,
        token<digit_chars>{s});
    if(ec)
        return start;
    t.s_ = s;
    t.v_.reset();
    return it;
}

} // rfc
} // urls
} // boost

#endif