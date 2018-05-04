/****************************************************************************
 *
 * Copyright 2018 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/
//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <string>

// basic_string<charT,traits,Allocator>& assign(const charT* s);

#include <string>
#include <stdexcept>
#include <cassert>
#include "libcxx_tc_common.h"

#include "test_macros.h"

template <class S>
static int
test(S s, const typename S::value_type* str, S expected)
{
    s.assign(str);
    LIBCPP_ASSERT(s.__invariants());
    TC_ASSERT_EXPR(s == expected);
    return 0;
}

int tc_libcxx_strings_string_assign_pointer(void)
{
    {
    typedef std::string S;
    TC_ASSERT_FUNC((test(S(), "", S())));
    TC_ASSERT_FUNC((test(S(), "12345", S("12345"))));
    TC_ASSERT_FUNC((test(S(), "12345678901234567890", S("12345678901234567890"))));

    TC_ASSERT_FUNC((test(S("12345"), "", S())));
    TC_ASSERT_FUNC((test(S("12345"), "12345", S("12345"))));
    TC_ASSERT_FUNC((test(S("12345"), "1234567890", S("1234567890"))));

    TC_ASSERT_FUNC((test(S("12345678901234567890"), "", S())));
    TC_ASSERT_FUNC((test(S("12345678901234567890"), "12345", S("12345"))));
    test(S("12345678901234567890"), "12345678901234567890",
         S("12345678901234567890"));
    }

    { // test assignment to self
    typedef std::string S;
    S s_short = "123/";
    S s_long  = "Lorem ipsum dolor sit amet, consectetur/";

    s_short.assign(s_short.c_str());
    TC_ASSERT_EXPR(s_short == "123/");
    s_short.assign(s_short.c_str() + 2);
    TC_ASSERT_EXPR(s_short == "3/");

    s_long.assign(s_long.c_str() + 30);
    TC_ASSERT_EXPR(s_long == "nsectetur/");
    }
    TC_SUCCESS_RESULT();
    return 0;
}
