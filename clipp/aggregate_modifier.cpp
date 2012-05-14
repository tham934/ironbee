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
 * @brief IronBee &mdash; CLIPP Aggregate Modifier Implementation
 *
 * @author Christopher Alfeld <calfeld@qualys.com>
 */

#include "aggregate_modifier.hpp"

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/random.hpp>

#include <ctime>

using boost::bind;
using namespace std;

namespace IronBee {
namespace CLIPP {

typedef boost::function<size_t()> distribution_t;

size_t constant_dist(size_t n)
{
    return n;
}

template <typename DistributionType>
class random_dist
{
public:
    explicit
    random_dist(DistributionType dist) :
        m_rng(clock()),
        m_dist(dist)
    {
        // nop
    }

    size_t operator()()
    {
        return m_dist(m_rng);
    }

protected:
    boost::random::mt19937 m_rng;
    DistributionType       m_dist;
};

template <typename DistributionType>
random_dist<DistributionType> make_random_dist(DistributionType dist)
{
    return random_dist<DistributionType>(dist);
}

struct AggregateModifier::State
{
    //! Distribution of targets.
    distribution_t distribution;

    //! Current target.
    size_t         n;
    //! Current aggregate.
    Input::input_p aggregate;
};

AggregateModifier::AggregateModifier(size_t n) :
    m_state(new State())
{
    m_state->distribution = bind(constant_dist, n);
}

bool AggregateModifier::operator()(Input::input_p& input)
{
    if (! input) {
        if (m_state->aggregate) {
            input.swap(m_state->aggregate);
        }
        return true;
    }

    if (! m_state->aggregate) {
        m_state->aggregate = input;
        m_state->n = m_state->distribution();
    }
    else {
        copy(
            input->connection.transactions.begin(),
            input->connection.transactions.end(),
            back_inserter(m_state->aggregate->connection.transactions)
        );
    }

    if (
        m_state->n != 0 &&
        m_state->aggregate->connection.transactions.size() >= m_state->n
    )
    {
        input.swap(m_state->aggregate);
        m_state->aggregate.reset();
        return true;
    }

    return false;
}

AggregateModifier AggregateModifier::uniform(
    unsigned int min,
    unsigned int max
)
{
    AggregateModifier mod;
    mod.m_state->distribution = make_random_dist(
        boost::random::uniform_int_distribution<>(min, max)
    );
    return mod;
}

AggregateModifier AggregateModifier::binomial(unsigned int t, double p)
{
    AggregateModifier mod;
    mod.m_state->distribution = make_random_dist(
        boost::random::binomial_distribution<>(t, p)
    );
    return mod;
}

} // CLIPP
} // IronBee
