/*****************************************************************************
 * Licensed to Qualys, Inc. (QUALYS) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * QUALYS licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ****************************************************************************/

/**
 * @file
 * @brief IronBee++ --- Test Fixture
 *
 * @author Christopher Alfeld <calfeld@qualys.com>
 **/

#ifndef __IBPP__TEST_FIXTURE__
#define __IBPP__TEST_FIXTURE__

#include <ironbeepp/engine.hpp>
#include <ironbeepp/server.hpp>
#include <ironbeepp/connection.hpp>
#include <ironbeepp/transaction.hpp>

namespace IronBee {

/**
 * Simple IronBee++ Test Fixture
 **/
class TestFixture
{
public:
    TestFixture();
    ~TestFixture();

protected:
    IronBee::Server      m_server;
    IronBee::Engine      m_engine;
    IronBee::Connection  m_connection;
    IronBee::Transaction m_transaction;

private:
    IronBee::ServerValue m_server_value;
};

} // IronBee

#endif
