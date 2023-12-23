/*
 * Copyright (c) 2023 Roc Streaming authors
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

//! @file roc_rtp/identity.h
//! @brief RTP participant identity.

#ifndef ROC_RTP_IDENTITY_H_
#define ROC_RTP_IDENTITY_H_

#include "roc_core/noncopyable.h"
#include "roc_core/uuid.h"
#include "roc_packet/units.h"

namespace roc {
namespace rtp {

//! RTP participant identity.
class Identity : public core::NonCopyable<> {
public:
    //! Initialize.
    Identity();

    //! Check if was constructed successfully.
    bool is_valid() const;

    //! Get generated CNAME.
    //! Uniquely identifies participant across all RTP sessions.
    //! It is expected that collisions are not practi cally possible.
    const char* cname() const;

    //! Get generated SSRC.
    //! Uniquely identifies participant within RTP session.
    //! It is expected that collisions are possible and should be resolved.
    packet::stream_source_t ssrc() const;

    //! Regenerate SSRC.
    //! Used in case of SSRC collision.
    bool change_ssrc();

private:
    char cname_[core::UuidLen + 1];
    packet::stream_source_t ssrc_;
    bool valid_;
};

} // namespace rtp
} // namespace roc

#endif // ROC_RTP_IDENTITY_H_
