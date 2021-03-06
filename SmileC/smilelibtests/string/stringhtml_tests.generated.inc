// This file was auto-generated.  Do not edit!
//
// SourceHash: 36911d83b4fa7476e787bb6ee68ae9c3

START_TEST_SUITE(StringHtmlTests)
{
	EmptyStringsShouldHtmlEncodeToEmptyStrings,
	HtmlEncodeShouldEncodeTheFourDangerousCharactersToNamedEntities,
	HtmlEncodeShouldOnlyChangeTheFourDangerousCharacters,
	EmptyStringsShouldHtmlEncodeToAsciiToEmptyStrings,
	HtmlEncodeToAsciiShouldEncodeTheFourDangerousCharactersToNamedEntities,
	HtmlEncodeToAsciiShouldEncodeAllNonAsciiCharacters,
	EmptyStringsShouldHtmlDecodeToEmptyStrings,
	UnencodedStringsShouldHtmlDecodeToUnencodedStrings,
	HtmlDecodeShouldDecodeTheAsciiNamedEntities,
	HtmlDecodeShouldDecodeNamedLatin1EntitiesToUtf8,
	HtmlDecodeShouldDecodeNamedNonLatin1EntitiesToUtf8,
	HtmlDecodeShouldDecodeNumericLatin1EntitiesToUtf8,
	HtmlDecodeShouldDecodeDecimalNonLatin1EntitiesToUtf8,
	HtmlDecodeShouldDecodeUppercaseHexadecimalNonLatin1EntitiesToUtf8,
	HtmlDecodeShouldDecodeLowercaseHexadecimalNonLatin1EntitiesToUtf8,
	HtmlDecodeShouldDecodeDecimalCornerCases,
	HtmlDecodeShouldDecodeHexadecimalCornerCases,
	HtmlDecodeShouldSkipBadInput,
	EmptyStringsShouldUrlEncodeToEmptyStrings,
	UrlEncodeShouldEncodeDangerousCharactersToEscapes,
	UrlEncodeShouldIgnoreSafePunctuation,
	UrlEncodeShouldEncodeNonAsciiCharacters,
	EmptyStringsShouldUrlQueryEncodeToEmptyStrings,
	UrlQueryEncodeShouldEncodeOnlyAFewDangerousCharactersToEscapes,
	UrlQueryEncodeShouldIgnoreSafePunctuation,
	UrlQueryEncodeShouldEncodeNonAsciiCharacters,
	EmptyStringsShouldUrlDecodeToEmptyStrings,
	UrlDecodeShouldDecodeDangerousCharactersFromEscapes,
	UrlDecodeShouldDecodeUppercaseNonAsciiCharacters,
	UrlDecodeShouldDecodeLowercaseNonAsciiCharacters,
	UrlDecodeShouldSkipBadEscapes,
}
END_TEST_SUITE(StringHtmlTests)

