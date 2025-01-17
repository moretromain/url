//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/url
//

// Test that header file is self-contained.
#include <boost/url/rfc/charsets.hpp>

#include "test_bnf.hpp"
#include "test_suite.hpp"

namespace boost {
namespace urls {

class char_sets_test
{
public:
    void
    testLuts()
    {
        test_char_set(
            pchars,
            // unreserved
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789"
            "-._~"
            // sub-delims
            "!$&'()*+,;="
            // ":" / "@"
            ":@");
    }

    void
    run()
    {
        testLuts();
    }
};

TEST_SUITE(
    char_sets_test,
    "boost.url.char_sets");

} // urls
} // boost
