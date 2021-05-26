#include "Fuzzy_System.hpp"

string Fuzzy_System::fuzzy_hash_compute(string file)
{
	// digest_generator is reset by default.
	digest_generator gen;
	// Use "unnormalized" form not to remove
	// sequences with 4 or more identical characters.
	// You can use "digest_t" and you will get digests without such sequences.
	digest_unorm_t d;
	// Generated digest is always natural.
	// You don't have to give too large sizes.
	char digestbuf[digest_unorm_t::max_natural_chars];
	// File buffer
	static const size_t BUFFER_SIZE = 4096;
	unsigned char filebuf[BUFFER_SIZE];

	// The buffer which contains the format string.
	// Converting to "unsigned" is completely safe for
	// ssdeep-compatible configuration
	// (I mean, unless you haven't modified many parameters).
	static_assert(digest_unorm_t::max_natural_width <= std::numeric_limits<unsigned>::max(),
		"digest_unorm_t::max_natural_width must be small enough.");
	char digestformatbuf[digest_unorm_t::max_natural_width_digits + 9];
	sprintf(digestformatbuf, "%%-%us  %%s\n",
		static_cast<unsigned>(digest_unorm_t::max_natural_width));
#if 0
	fprintf(stderr, "FORMAT STRING: %s\n", digestformatbuf);
#endif


	string filename = file;
	FILE* fp = fopen(filename.c_str(), "rb");

	// error when failed to open file
	if (!fp)
	{
		perror(filename.c_str());
		return nullptr;
	}

#ifdef OPTIMIZE_CONSTANT_FILE_SIZE
	/*
		Retrieve file size (but the file is not seekable, do nothing).
		Note that using off_t is not safe for 32-bit platform.
		Use something much more robust to retrieve file sizes.
	*/
	bool seekable = false;
	off_t filesize;
	if (fseek(fp, 0, SEEK_END) == 0)
	{
		/*
			If seekable, set file size constant for
			digest generator optimization. The generator will work without it
			but using it makes the program significantly faster.
		*/
		seekable = true;
		filesize = ftell(fp);
		if (fseek(fp, 0, SEEK_SET) != 0)
		{
			fprintf(stderr, "%s: could not seek to the beginning.\n", filename);
			fclose(fp);
			return NULL;
		}
		/*
			set_file_size_constant fails if:
			*	set_file_size_constant is called multiple times (not happens here)
			*	given file size is too large to optimize
		*/
		if (!gen.set_file_size_constant(filesize))
		{
			fprintf(stderr, "%s: cannot optimize performance for this file.\n", filename);
			fclose(fp);
			return NULL;
		}
	}
	else
	{
#if 0
		fprintf(stderr, "%s: seek operation is not available.\n", filename);
#endif
	}
#endif

	// update generator by given file stream and buffer
	if (!gen.update_by_stream<BUFFER_SIZE>(fp, filebuf))
	{
		fprintf(stderr, "%s: failed to update fuzzy hashes.\n", filename);
		fclose(fp);
		return NULL;
	}
	fclose(fp);

	/*
		copy_digest will fail if:
		*	The file was too big to process
		*	The file size did not match with file size constant
			(set by set_file_size_constant)
	*/
	if (!gen.copy_digest(d))
	{
		if (gen.is_total_size_clamped())
			fprintf(stderr, "%s: too big to process.\n", filename);
#ifdef OPTIMIZE_CONSTANT_FILE_SIZE
		else if (seekable && (digest_filesize_t(filesize) != gen.total_size()))
			fprintf(stderr, "%s: file size changed while reading (or arithmetic overflow?)\n", filename);
#endif
		else
			fprintf(stderr, "%s: failed to copy digest with unknown error.\n", filename);
		return NULL;
	}

	/*
		If size of the digest buffer is equal or greater than max_natural_chars,
		copying the string digest with pretty_unsafe function is completely safe.

		However, this function still may fail due to failure of sprintf.
	*/
	if (!d.pretty_unsafe(digestbuf))
	{
		fprintf(stderr, "%s: failed to stringize the digest.\n", filename);
		return NULL;
	}
	//printf(digestformatbuf, digestbuf, filename);
	string hash(digestbuf);

	// reset the generator if we haven't reached the end
	//if (i + 1 != argc)
	//	gen.reset();	

	return hash;
}

digest_comparison_score_t Fuzzy_System::fuzzy_hash_comppare(string hash1, string hash2)
{
#if 1
	unified_digest_t h1, h2;
#else
	unified_digest_long_t h1, h2;
#endif
	char digestbuf[decltype(h1.u)::max_natural_chars];

	// Parse digests
	if (!decltype(h1.u)::parse(h1.u, hash1.c_str()))
	{
		fprintf(stderr, "error: failed to parse HASH1.\n");
		return 1;
	}
	if (!decltype(h2.u)::parse(h2.u, hash2.c_str()))
	{
		fprintf(stderr, "error: failed to parse HASH2.\n");
		return 1;
	}

	/*
		Restringize digests (just for demo)
		Notice that we're using h1.d instead of h1.u?
		This is not a good example but works perfectly.
	*/
	if (!h1.d.pretty_unsafe(digestbuf))
	{
		fprintf(stderr, "abort: failed to re-stringize HASH1.\n");
		return 1;
	}
	//printf("HASH1 : %s\n", digestbuf);
	if (!h2.d.pretty_unsafe(digestbuf))
	{
		fprintf(stderr, "abort: failed to re-stringize HASH2.\n");
		return 1;
	}
	//printf("HASH2 : %s\n", digestbuf);

	// Normalize digests and restringize them
	decltype(h1.d)::normalize(h1.d, h1.u);
	decltype(h2.d)::normalize(h2.d, h2.u);
	if (!h1.d.pretty_unsafe(digestbuf))
	{
		fprintf(stderr, "abort: failed to re-stringize HASH1.\n");
		return 1;
	}
	//printf("NORM1 : %s\n", digestbuf);
	if (!h2.d.pretty_unsafe(digestbuf))
	{
		fprintf(stderr, "abort: failed to re-stringize HASH2.\n");
		return 1;
	}
	//printf("NORM2 : %s\n", digestbuf);

	/*
		Compare them
		"Unnormalized" form has compare function but slow because of additional normalization)

		Note:
		Use `compare` or `compare<comparison_version::latest>` for latest
		version and `compare<comparison_version::v2_9>` for version 2.9 emulation.
	*/
	digest_comparison_score_t score =
		decltype(h1.d)::compare<comparison_version::v2_9>(h1.d, h2.d);
	//printf("SCORE: %u\n", unsigned(score)); // safe to cast to unsigned (value is in [0,100])

	return unsigned(score);
}
