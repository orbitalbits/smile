//---------------------------------------------------------------------------------------
//  Smile Programming Language Interpreter (Unit Tests)
//  Copyright 2004-2015 Sean Werkema
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//---------------------------------------------------------------------------------------

#include "stdafx.h"
#include <setjmp.h>

#ifdef _WIN32
	#include <conio.h>
	#include "ansicolor-w32.h"
#else
	#include <termios.h>
#endif

#include "testlib.h"

/// <summary>
/// This jump-buffer is used to abort failed tests by unwinding the stack to the point
/// before the test ran.
/// </summary>
static jmp_buf TestJmpBuf;

/// <summary>
/// This exists to temporarily hold the test-failure message across the long-jump that
/// unwinds the stack.
/// </summary>
static const char *TestFailureMessage = NULL;

/// <summary>
/// Assert that the given string is a valid string and matches the given text and length.
/// This will fail the current unit test if this string does not match.
/// </summary>
/// <param name="str">The string to validate.</param>
/// <param name="expectedString">The expected contents of that string.</param>
/// <param name="expectedLength">The expected length of that string.</param>
/// <param name="message">A message to display to the user to explain why the test failed.</param>
void AssertStringInternal(String str, const char *expectedString, Int expectedLength, const char *message)
{
	char buffer[1024];

	if (str == NULL) {
		sprintf(buffer, "%s: actual string is a NULL pointer", message);
		FailTestInternal(buffer);
	}

	if (String_Length(str) != expectedLength) {
		sprintf(buffer, "%s: actual string length is %d", message, String_Length(str));
		FailTestInternal(buffer);
	}

	if (String_GetBytes(str)[expectedLength] != '\0') {
		sprintf(buffer, "%s: actual string is missing '\0' after end", message);
		FailTestInternal(buffer);
	}

	if (expectedLength > 0) {
		if (MemCmp(String_GetBytes(str), expectedString, expectedLength)) {
			sprintf(buffer, "%s: actual string bytes do not match", message);
			FailTestInternal(buffer);
		}
	}
	else {
		if (str != String_Empty) {
			sprintf(buffer, "%s: actual string is not the String_Empty singleton", message);
			FailTestInternal(buffer);
		}
	}
}

/// <summary>
/// Print out an "OK" message to show the test succeeded.
/// </summary>
/// <param name="totalTicks">The total number of ticks this test executed in.</param>
static void PrintTestSuccess(UInt64 totalTicks)
{
	double usec;
	double timing;
	int precision;
	const char *units;

	// Compute the nicest way to print out the timing metrics.
	usec = (double)Smile_TicksToMicroseconds(totalTicks);
	if (usec >= 1000000.0) {
		precision = usec > 100000000.0 ? 0 : usec > 10000000.0 ? 1 : 2;
		timing = usec / 1000000.0;
		units = "s";
	}
	else if (usec >= 1000.0) {
		precision = usec > 100000.0 ? 0 : usec > 10000.0 ? 1 : 2;
		timing = usec / 1000.0;
		units = "ms";
	}
	else {
		precision = 0;
		timing = usec;
		units = "us";
	}

	// Print the message.
	printf("\x1B[0;1;32mOK\x1B[0m \x1B[36m(%.*f %s)\x1B[0m\n", precision, timing, units);

	// Flush it to the output, which ensures that it gets seen even if the next test fails.
	fflush(stdout);
}

/// <summary>
/// Print a big red failure message for this test.
/// </summary>
/// <param name="message">The message describing what failed in this test.</param>
/// <param name="file">The file in which the failure occurred.</param>
/// <param name="line">The line on which the failure occurred in that file.</param>
static void PrintTestFailure(const char *message, const char *file, int line)
{
	printf(
		"\x1B[0;1;37;41m FAILED \x1B[0m\n"
		"    \x1B[1;31m________________________________________________________________\x1B[0;1;31m\n"
		"\n"
		"    \x1B[31mFailed assertion was:\n"
		"      \x1B[33m%s\x1B[0m\n"
		"\n"
		"\x1B[0;1;31m    at %s%s: %d\n"
		"    \x1B[1;31m________________________________________________________________\x1B[0m\n"
		"\n",
		message,
		strlen(file) > 60 ? "..." : "",
		strlen(file) > 60 ? file + strlen(file) - 60 : file,
		line
	);

	// Flush it to the output, which ensures that it gets seen even if the next test also fails.
	fflush(stdout);
}

/// <summary>
/// Run the given test.
/// </summary>
/// <param name="str">The string to validate.</param>
/// <param name="expectedString">The expected contents of that string.</param>
/// <param name="expectedLength">The expected length of that string.</param>
/// <param name="message">A message to display to the user to explain why the test failed.</param>
int RunTestInternal(const char *name, const char *file, int line, TestFuncInternal testFuncInternal)
{
	UInt64 startTicks, endTicks;

	// First, print the name of the test we're about to run.
	if (strlen(name) > 58) {
		printf("  %.15s...%.40s: ", name, name + strlen(name) - 40);
	}
	else {
		printf("  %s: ", name);
	}

	// Flush it to the output, which ensures that it gets seen even if this test fails.
	fflush(stdout);

	// Set a marker so we can get back to this if-statement if the test fails.
	if (setjmp(TestJmpBuf)) {

		// Test failed, so print the message, and return that it failed.
		PrintTestFailure(TestFailureMessage, file, line);
		return 0;
	}

	// Run the test, with timing metrics.
	startTicks = Smile_GetTicks();
	testFuncInternal();
	endTicks = Smile_GetTicks();

	// Test succeeded, so print "OK", and return that it succeeded.
	PrintTestSuccess(endTicks - startTicks);
	return 1;
}

/// <summary>
/// Cause the current test to fail, aborting all successive execution.
/// </summary>
/// <param name="message">The message to display to the user explaining why this test failed.</param>
/// <returns>Never returns.</returns>
int FailTestInternal(const char *message)
{
	char *safeMessage;

	// Save the message so the test runner can find it (and save it in case it gets stomped on).
	safeMessage = GC_MALLOC_ATOMIC(strlen(message) + 1);
	if (safeMessage == NULL)
		Smile_Abort_OutOfMemory();
	strcpy(safeMessage, message);
	TestFailureMessage = safeMessage;

	// Long-jump back to abort the test.  We pass '1', which is what will be returned by the
	// original setjmp() call.
	longjmp(TestJmpBuf, 1);

	return 0;	// Never reached.
}

/// <summary>
/// Run all the tests in the given test suite, and return a new collection of results for it.
/// </summary>
/// <param name="name">The name of the test suite.</param>
/// <param name="funcs">An array of the functions in the test suite to be run.</param>
/// <param name="numFuncs">The number of functions to run.</param>
/// <returns>A new collection of results that describes the overall state of this test suite.</returns>
TestSuiteResults *RunTestSuiteInternal(const char *name, TestFunc *funcs, int numFuncs)
{
	int numSuccesses, numFailures, succeeded, i;
	TestSuiteResults *results;

	printf("\x1B[0;1;37m Test suite %s: \x1B[0m\n", name);
	fflush(stdout);

	numSuccesses = 0, numFailures = 0;
	for (i = 0; i < numFuncs; i++, funcs++) {
		succeeded = (*funcs)();
		if (succeeded) numSuccesses++;
		else numFailures++;
	}

	printf("\n");

	results = GC_MALLOC_STRUCT(TestSuiteResults);
	if (results == NULL) Smile_Abort_OutOfMemory();
	results->numFailures = numFailures;
	results->numSuccesses = numSuccesses;
	return results;
}

/// <summary>
/// Print a summary message for the given set of test-suite results.
/// </summary>
/// <param name="results">The results to print.</param>
void DisplayTestSuiteResults(TestSuiteResults *results)
{
	printf("\x1B[0;1;37m Test suite results:  \x1B[32m%d\x1B[37m tests succeeded,%s %d\x1B[37m tests failed. \x1B[0m\n\n",
		results->numSuccesses, results->numFailures > 0 ? " \x1B[1;33;41m" : "\x1B[1;32m", results->numFailures);
	fflush(stdout);
}

/// <summary>
/// Wait for any keystroke from the user.  Surprisingly complex and non-portable.
/// </summary>
void WaitForAnyKey(void)
{
	#ifdef _WIN32
		getch();
	#else
		struct termios oldInfo, info;

		// Get the current terminal behavior.
		tcgetattr(0, &oldInfo);

		// Disable canonical mode.
		tcgetattr(0, &info);
		info.c_lflag &= ~ICANON;
		info.c_cc[VMIN] = 1;
		info.c_cc[VTIME] = 0;
		tcsetattr(0, TCSANOW, &info);

		// Read one key.
		getchar();

		// Restore the terminal behavior to default.
		tcsetattr(0, TCSANOW, &oldInfo);
	#endif
}
