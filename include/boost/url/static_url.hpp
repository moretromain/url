//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/url
//

#ifndef BOOST_URL_STATIC_URL_HPP
#define BOOST_URL_STATIC_URL_HPP

#include <boost/url/detail/config.hpp>
#include <boost/url/url.hpp>
#include <boost/static_assert.hpp>
#include <cstddef>

namespace boost {
namespace urls {

// VFALCO This is here to reduce the
// number of template instantiations,
// and keep definitions in the library
#ifndef BOOST_URL_DOCS
class BOOST_SYMBOL_VISIBLE
    static_url_base : public url
{
protected:
    BOOST_URL_DECL
    virtual
    ~static_url_base();

    BOOST_URL_DECL static_url_base(
        char* buf, std::size_t cap) noexcept;
    BOOST_URL_DECL void copy(url const& u);
    BOOST_URL_DECL void copy(url_view const& u);
    BOOST_URL_DECL url_view convert() const noexcept;

    BOOST_URL_DECL char* alloc_impl(
        std::size_t n) override;
    BOOST_URL_DECL void free_impl(char*) override;
    BOOST_URL_DECL std::size_t growth_impl(
        std::size_t cap, std::size_t
            new_size) override;
public:
    BOOST_URL_DECL
    operator url_view() const noexcept;
};
#endif

//------------------------------------------------

/** A URL with fixed-capacity storage

    This container acts like @ref url,
    except that dynamic allocations are
    never performed. Instead, the capacity
    for the data comes from inline storage.

    @tparam Capacity The maximum capacity
    in bytes. A URL requires bytes equal
    to at least the number of characters
    plus one, plus an additional number
    of bytes proportional to the count of
    path segments plus the count of query
    params. Due to alignment requirements,
    the usable capacity may be slightly
    less than this number.

    @see
        @ref url,
        @ref url_view.
*/
template<std::size_t Capacity>
class static_url
#ifdef BOOST_URL_DOCS
    : public url
#else
    : public static_url_base
#endif
{
    char buf_[(Capacity + 1) &
        ~(sizeof(max_align_t)-1)];

public:
    /** Destructor
    */
    ~static_url()
    {
    }

    /** Constructor
    */
    static_url() noexcept
        : static_url_base(
            buf_, Capacity)
    {
    }

    /** Constructor

        This constructs a copy of `u`.

        @par Exception Safety
        Strong guarantee.

        @throw std::bad_alloc `u.encoded_url().size() > Capacity`
    */
    static_url(url const& u)
        : static_url()
    {
        copy(u);
    }

    /** Constructor

        This constructs a copy of `u`.

        @par Exception Safety
        Strong guarantee.

        @throw std::bad_alloc `u.encoded_url().size() > Capacity`
    */
    static_url(url_view const& u)
        : static_url()
    {
        copy(u);
    }

    /** Constructor

        This constructs a copy of `u`.

        @par Exception Safety
        Strong guarantee.

        @throw std::bad_alloc `u.encoded_url().size() > Capacity`
    */
    static_url(static_url const& u)
        : static_url()
    {
        copy(u);
    }

    /** Assignment
    */
    static_url&
    operator=(url const& u)
    {
        copy(u);
        return *this;
    }

    /** Assignment
    */
    static_url&
    operator=(url_view const& u)
    {
        copy(u);
        return *this;
    }

    /** Assignment
    */
    static_url&
    operator=(static_url const& u)
    {
        copy(u);
        return *this;
    }
};

} // urls
} // boost

#endif
