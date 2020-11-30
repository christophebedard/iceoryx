// Copyright (c) 2020 by Apex.AI Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "iceoryx_posh/popo/guard_condition.hpp"
#include "iceoryx_posh/popo/modern_api/typed_subscriber.hpp"
#include "iceoryx_posh/popo/wait_set.hpp"
#include "iceoryx_posh/runtime/posh_runtime.hpp"
#include "topic_data.hpp"

#include <chrono>
#include <csignal>
#include <iostream>

bool killswitch = false;

static void sigHandler(int f_sig [[gnu::unused]])
{
    killswitch = true;
}

void receive()
{
    iox::popo::TypedSubscriber<CounterTopic> subscriber({"CounterTopic", iox::capro::AnyInstanceString, "Counter"});

    subscriber.subscribe();
    uint64_t maxNumSamples = 2;
    while (!killswitch)
    {
#if 0        
//todo: requires the queue resize feature to be merged
        subscriber.unsubscribe();                             // unsubscribe and resubscribe
        std::this_thread::sleep_for(std::chrono::seconds(1)); // we will probably miss some data while unsubscribed
        // we can (re)subscribe with differing maximum number of samples
        maxNumSamples = maxNumSamples % 4 + 1; // cycles between last 1 to 4 samples
        subscriber.subscribe(maxNumSamples);
        std::cout << "Subscribe with max number of samples " << maxNumSamples << std::endl;
#endif
        std::this_thread::sleep_for(std::chrono::seconds(1));

        bool hasData = true;
        do
        {
            subscriber.take()
                .and_then([](iox::popo::Sample<const CounterTopic>& sample) {
                    std::cout << "Received: " << *sample.get() << std::endl;
                })
                .if_empty([&] { hasData = false; })
                .or_else([](iox::popo::ChunkReceiveError) { std::cout << "Error while receiving." << std::endl; });
        } while (hasData);
        std::cout << "Waiting for data ... " << std::endl;
    }
    subscriber.unsubscribe();
}

int main()
{
    signal(SIGINT, sigHandler);
    iox::runtime::PoshRuntime::getInstance("/iox-subscriber2");

    std::thread receiver(receive);
    receiver.join();

    return (EXIT_SUCCESS);
}