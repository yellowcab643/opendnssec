/*
 * Copyright (c) 2011 SURFnet bv
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*****************************************************************************
 pb-orm-producer-tests.h

 Contains test cases to test messages from producer.proto
 We test a producer with multiple consumers that use transactions to 
 synchronize via the database using multiple threads.
 *****************************************************************************/

#ifndef _PB_ORM_PRODUCER_TESTS_H
#define _PB_ORM_PRODUCER_TESTS_H

#include <cppunit/extensions/HelperMacros.h>

#include "pb-orm.h"

class ProducerTests : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ProducerTests);
	CPPUNIT_TEST(testProducerTransactions);
	CPPUNIT_TEST_SUITE_END();

public:
	void testProducerTransactions();

	void setUp();
	void tearDown();

	OrmConn conn;
};

#endif // !_PB_ORM_PRODUCER_TESTS_H
