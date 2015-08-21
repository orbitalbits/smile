// This file was auto-generated.  Do not edit!

START_TEST_SUITE(StringParseTests)
{
	EmptyStringsShouldFailToBeParsedAsBooleans,
	ThingsThatArentBooleanShouldFailToBeParsed,
	KnownBooleanTruthValuesShouldParseAsTrue,
	WhitespaceShouldNotAffectBooleanTruthValueParsing,
	KnownBooleanFalsehoodValuesShouldParseAsFalse,
	WhitespaceShouldNotAffectBooleanFalsehoodValueParsing,
	EmptyStringsShouldFailToBeParsedAsIntegers,
	ThingsThatArentIntegersShouldFailToBeParsed,
	ShouldParsePositiveDecimalIntegers,
	ShouldParsePositiveHexIntegers,
	ShouldParseNegativeDecimalIntegers,
	ShouldParseNegativeHexIntegers,
	EmptyStringsShouldFailToBeParsedAsReals,
	ThingsThatArentRealsShouldFailToBeParsed,
	ThingsThatAreSimilarToRealsButNotRealsShouldFailToBeParsed,
	ShouldParsePositiveDecimalRealsThatLookLikeIntegers,
	ShouldParseNegativeDecimalRealsThatLookLikeIntegers,
	ShouldParsePositiveDecimalRealsThatAreOfTheFormIntegerDot,
	ShouldParseNegativeDecimalRealsThatAreOfTheFormIntegerDot,
	ShouldParsePositiveDecimalRealsThatAreOfTheFormIntegerDotDigits,
	ShouldParseNegativeDecimalRealsThatAreOfTheFormIntegerDotDigits,
	ShouldParsePositiveDecimalRealsThatAreOfTheFormDotDigits,
	ShouldParseNegativeDecimalRealsThatAreOfTheFormDotDigits,
	ShouldParsePositiveExponents,
	ShouldParseNegativeExponents,
	CertainProblematicNumbersParseExactly,
	VeryProblematicNumbersParseWithinOneOrTwoUlps,
}
END_TEST_SUITE(StringParseTests)
