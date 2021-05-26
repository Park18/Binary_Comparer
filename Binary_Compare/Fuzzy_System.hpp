#ifndef FUZZY_SYSTEM_HPP
#define FUZZY_SYSTEM_HPP

/*

	ffuzzy++ examples

	compute-hash.cpp
	Fuzzy hash computation program

	Copyright (C) 2015 Tsukasa OI <floss_ssdeep@irq.a4lg.com>


	Permission to use, copy, modify, and/or distribute this software for
	any purpose with or without fee is hereby granted, provided that the
	above copyright notice and this permission notice appear in all copies.

	THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
	WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
	MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
	ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
	WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
	ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
	OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

*/

#pragma warning(disable:4996)
#include <cstdio>
#include <limits>
#include <string>

/*
	This enables compilation without libffuzzypp.a.
	Define this in **one** of the source files to make the linker happy.
*/
#define FFUZZYPP_DECLARATIONS

// the following line will activate assertions.
//#define FFUZZYPP_DEBUG

#include "ffuzzy.hpp"
using namespace ffuzzy;
using namespace std;

typedef union
{
	digest_unorm_t u;
	digest_t d;
} unified_digest_t;
typedef union
{
	digest_long_unorm_t u;
	digest_long_t d;
} unified_digest_long_t;

// the following line will enable constant file size optimization.
#define OPTIMIZE_CONSTANT_FILE_SIZE

namespace Fuzzy_System
{
	string fuzzy_hash_compute(string file);

	digest_comparison_score_t fuzzy_hash_comppare(string hash1, string hash2);
};

#endif // !FUZZY_SYSTEM_HPP