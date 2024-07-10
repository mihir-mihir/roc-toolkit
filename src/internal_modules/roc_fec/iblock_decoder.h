/*
 * Copyright (c) 2015 Roc Streaming authors
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

//! @file roc_fec/iblock_decoder.h
//! @brief FEC block decoder interface.

#ifndef ROC_FEC_IBLOCK_DECODER_H_
#define ROC_FEC_IBLOCK_DECODER_H_

#include "roc_core/slice.h"
#include "roc_core/stddefs.h"
#include "roc_status/status_code.h"

namespace roc {
namespace fec {

//! FEC block decoder interface.
class IBlockDecoder {
public:
    virtual ~IBlockDecoder();

    //! Check if the object was successfully constructed.
    virtual status::StatusCode init_status() const = 0;

    //! Get the maximum number of encoding symbols for the scheme being used.
    virtual size_t max_block_length() const = 0;

    //! Start block.
    //! @remarks
    //!  Performs an initial setup for a block. Should be called before
    //!  any operations for the block.
    //! @returns status::StatusOK on success, or a specific error code on failure (e.g.,
    //! status::StatusNoMem if memory allocation fails).
    virtual ROC_ATTR_NODISCARD status::StatusCode
    begin_block(size_t sblen, size_t rblen, size_t payload_size) = 0;

    //! Store source or repair packet buffer for current block.
    //! @pre
    //!  This method may be called only between begin_block() and end_block().
    virtual void set_buffer(size_t index, const core::Slice<uint8_t>& buffer) = 0;

    //! Repair source packet buffer.
    //! @pre
    //!  This method may be called only between begin_block() and end_block().
    virtual core::Slice<uint8_t> repair_buffer(size_t index) = 0;

    //! Finish block.
    //! @remarks
    //!  Cleanups the resources allocated for the block. Should be called after
    //!  all operations for the block.
    virtual void end_block() = 0;
};

} // namespace fec
} // namespace roc

#endif // ROC_FEC_IBLOCK_DECODER_H_
