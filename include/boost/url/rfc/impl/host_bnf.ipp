//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/url
//

#ifndef BOOST_URL_IMPL_HOST_BNF_IPP
#define BOOST_URL_IMPL_HOST_BNF_IPP

#include <boost/url/rfc/host_bnf.hpp>
#include <boost/url/rfc/ip_literal_bnf.hpp>
#include <new>

namespace boost {
namespace urls {

bool
parse(
    char const*& it,
    char const* const end,
    error_code& ec,
    host_bnf& t)
{
    if(it == end)
    {
        t.host_type =
            host_type::name;
        t.name = {};
        t.host_part = {};
        return true;
    }
    auto const start = it;
    if(*it == '[')
    {
        // IP-literal
        ip_literal_bnf v;
        if(! parse(it, end, ec, v))
            return false;
        if(v.is_ipv6)
        {
            // IPv6address
            t.ipv6 = v.ipv6;
            t.host_type =
                host_type::ipv6;
            t.host_part = string_view(
                start, it - start);
            return true;
        }
        // IPvFuture
        t.ipvfuture = v.ipvfuture;
        t.host_type =
            host_type::ipvfuture;
        t.host_part = string_view(
            start, it - start);
        return true;
    }
    // IPv4address
    {
        if(parse(it, end, ec,
            ipv4_address_bnf{t.ipv4}))
        {
            t.host_type =
                host_type::ipv4;
            t.host_part = string_view(
                start, it - start);
            return true;
        }
        // rewind
        it = start;
        ec = {};
    }
    // reg-name
    static constexpr auto cs =
        unreserved_chars +
        subdelim_chars;
    if(! parse(it, end, ec,
        pct_encoded_bnf(
            cs, t.name)))
    {
        // bad reg-name
        return false;
    }
    t.host_type =
        host_type::name;
    t.host_part = string_view(
        start, it - start);
    return true;
}

} // urls
} // boost

#endif
