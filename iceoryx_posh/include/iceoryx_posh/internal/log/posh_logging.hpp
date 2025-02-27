// Copyright (c) 2019 by Robert Bosch GmbH. All rights reserved.
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
//
// SPDX-License-Identifier: Apache-2.0
#ifndef IOX_POSH_LOG_POSH_LOGGING_HPP
#define IOX_POSH_LOG_POSH_LOGGING_HPP

/// @todo this might be needed to be public when the logger is used in templates

#include "iceoryx_hoofs/log/logging_free_function_building_block.hpp"

namespace iox
{
struct LoggingComponentPosh
{
    static constexpr char Ctx[] = "POSH";
    static constexpr char Description[] = "Log context of the POSH component!";
};

static constexpr auto LoggerPosh = iox::log::ffbb::ComponentLogger<LoggingComponentPosh>;

static constexpr auto LogFatal = iox::log::ffbb::LogFatal<LoggingComponentPosh>;
static constexpr auto LogError = iox::log::ffbb::LogError<LoggingComponentPosh>;
static constexpr auto LogWarn = iox::log::ffbb::LogWarn<LoggingComponentPosh>;
static constexpr auto LogInfo = iox::log::ffbb::LogInfo<LoggingComponentPosh>;
static constexpr auto LogDebug = iox::log::ffbb::LogDebug<LoggingComponentPosh>;
static constexpr auto LogVerbose = iox::log::ffbb::LogVerbose<LoggingComponentPosh>;

} // namespace iox

#endif // IOX_POSH_LOG_POSH_LOGGING_HPP
