/*
 * Chunk data functions
 *
 * Copyright (c) 2006-2014, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBEWF_CHUNK_DATA_H )
#define _LIBEWF_CHUNK_DATA_H

#include <common.h>
#include <types.h>

#include "libewf_io_handle.h"
#include "libewf_libbfio.h"
#include "libewf_libcerror.h"
#include "libewf_libfcache.h"
#include "libewf_libfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libewf_chunk_data libewf_chunk_data_t;

struct libewf_chunk_data
{
	/* The allocated data size
	 */
	size_t allocated_data_size;

	/* The data
	 */
	uint8_t *data;

	/* The data size
	 */
	size_t data_size;

	/* The compressed data
	 */
	uint8_t *compressed_data;

	/* The compressed data offset
	 */
	size_t compressed_data_offset;

	/* The compressed data size
	 */
	size_t compressed_data_size;

	/* The padding size
	 */
	size_t padding_size;

	/* The chunk data range flags
	 */
	uint32_t range_flags;

	/* The checksum
	 */
	uint32_t checksum;

	/* The flags
	 */
	uint8_t flags;

/* TODO chunk data rewrite */
	/* The chunk IO flags
	 */
	int8_t chunk_io_flags;
};

int libewf_chunk_data_initialize(
     libewf_chunk_data_t **chunk_data,
     size_t data_size,
     libcerror_error_t **error );

int libewf_chunk_data_initialize_clear_data(
     libewf_chunk_data_t **chunk_data,
     size_t data_size,
     libcerror_error_t **error );

int libewf_chunk_data_free(
     libewf_chunk_data_t **chunk_data,
     libcerror_error_t **error );

int libewf_chunk_data_pack(
     libewf_chunk_data_t *chunk_data,
     uint32_t chunk_size,
     uint16_t compression_method,
     int8_t compression_level,
     uint8_t compression_flags,
     const uint8_t *compressed_zero_byte_empty_block,
     size_t compressed_zero_byte_empty_block_size,
     uint8_t pack_flags,
     libcerror_error_t **error );

int libewf_chunk_data_pack_buffer(
     uint8_t *data,
     size_t data_size,
     uint8_t *compressed_data,
     size_t *compressed_data_offset,
     size_t *compressed_data_size,
     uint32_t chunk_size,
     size_t chunk_data_size,
     size_t *chunk_padding_size,
     uint16_t compression_method,
     int8_t compression_level,
     uint32_t *range_flags,
     uint32_t *chunk_checksum,
     int8_t *chunk_io_flags,
     const uint8_t *compressed_zero_byte_empty_block,
     size_t compressed_zero_byte_empty_block_size,
     uint8_t pack_flags,
     libcerror_error_t **error );

int libewf_chunk_data_unpack(
     libewf_chunk_data_t *chunk_data,
     uint32_t chunk_size,
     uint16_t compression_method,
     libcerror_error_t **error );

int libewf_chunk_data_unpack_buffer(
     uint8_t *data,
     size_t *data_size,
     const uint8_t *compressed_data,
     size_t compressed_data_size,
     uint32_t chunk_size,
     uint16_t compression_method,
     uint32_t range_flags,
     uint32_t chunk_checksum,
     int8_t chunk_io_flags,
     libcerror_error_t **error );

int libewf_chunk_data_check_for_empty_block(
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libewf_chunk_data_check_for_64_bit_pattern_fill(
     const uint8_t *data,
     size_t data_size,
     uint64_t *pattern,
     libcerror_error_t **error );

ssize_t libewf_chunk_data_write(
         libewf_chunk_data_t *chunk_data,
         libbfio_pool_t *file_io_pool,
         int file_io_pool_entry,
         libcerror_error_t **error );

int libewf_chunk_data_get_write_size(
     libewf_chunk_data_t *chunk_data,
     uint32_t *write_size,
     libcerror_error_t **error );

int libewf_chunk_data_get_checksum(
     libewf_chunk_data_t *chunk_data,
     uint16_t compression_method,
     uint32_t *checksum,
     libcerror_error_t **error );

int libewf_chunk_data_read_element_data(
     libewf_io_handle_t *io_handle,
     libbfio_pool_t *file_io_pool,
     libfdata_list_element_t *element,
     libfcache_cache_t *cache,
     int file_io_pool_entry,
     off64_t chunk_data_offset,
     size64_t chunk_data_size,
     uint32_t chunk_data_flags,
     uint8_t read_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

