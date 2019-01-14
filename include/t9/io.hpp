// IO helper functions for handling files -*- C++ -*-

// Copyright (C) 2019 Yves-Noel Weweler.
// All Rights Reserved.
//
// Licensed under the MIT License.
// See LICENSE file in the project root for full license information.

#ifndef CPP_T9_IO_HPP
#define CPP_T9_IO_HPP

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "format.hpp"

namespace t9::io {
/***
 * Read the content of a text file to memory.
 * @param file_path Path to the file to be read.
 * @param n_chars Maximal number of bytes to be read. If 0 is supplied, the whole file will be read.
 * @return String containing the read data.
 */
std::string
load_text_file(const std::filesystem::path &file_path,
               size_t n_chars);
}  // namespace t9::io

#endif //CPP_T9_IO_HPP
