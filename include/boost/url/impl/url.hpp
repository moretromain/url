//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/url
//

#ifndef BOOST_URL_IMPL_URL_HPP
#define BOOST_URL_IMPL_URL_HPP

namespace boost {
namespace urls {

template<class Allocator>
urls::segments
url::
segments(
    Allocator const& a) noexcept
{
    return urls::segments(*this, a);
}

} // urls
} // boost

#endif