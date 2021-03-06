/* Payload Tests
 *
 * Copyright (C) 2013 SansGrid
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */
/// \file
#include "payload_tests.h"

/// Test a peck payload
int testPeckPayload(PayloadTestStruct *test_struct) {
	// Call Peck tests with all options
	int exit_code;
	PayloadTestNode peck;

	// Set defaults
	peck.read_dir = SG_TEST_COMM_WRITE_SPI;
	peck.expected_exit_code = 0;
	// Assign nodes
	test_struct->peck = &peck;

	// Test device unrecognized
	peck.next_packet = SG_DEVSTATUS_SINGING;
	test_struct->peck_mode = SG_PECK_MATE;
	exit_code = testEyeballPayload(test_struct);
	if (exit_code)
		return exit_code;

	// Test device recognized
	peck.next_packet = SG_DEVSTATUS_SQUAWKING;
	test_struct->peck_mode = SG_PECK_RECOGNIZED;
	exit_code = testEyeballPayload(test_struct);

	return exit_code;
}


/// Test a peck payload
START_TEST (testPeck) {
#if TESTS_DEBUG_LEVEL > 0
	printf("\n\nTesting Peck\n");
#endif
	PayloadTestStruct test_struct;
	testStructInit(&test_struct);
	testPeckPayload(&test_struct);
#if TESTS_DEBUG_LEVEL > 0
	printf("Successfully Pecked\n");
#endif
}
END_TEST;


/// Payload unit tests
Suite *payloadTestPeck(void) {
	Suite *s = suite_create("Peck Payload Tests");
	TCase *tc_core = tcase_create("Core");
	tcase_add_test(tc_core, testPeck);

	suite_add_tcase(s, tc_core);

	return s;
}

// vim: ft=c ts=4 noet sw=4:


