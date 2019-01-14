// IO helper functions for handling files -*- C++ -*-

// Copyright (C) 2019 Yves-Noel Weweler.
// All Rights Reserved.
//
// Licensed under the MIT License.
// See LICENSE file in the project root for full license information.

#include "t9/io.hpp"

namespace t9::io {
std::string
load_text_file(const std::filesystem::path &file_path,
               size_t n_chars) {
  std::ifstream file;
  std::string data;
  size_t file_size;

  // Check if the file actually exists.
  if (!std::filesystem::exists(file_path)) {
    std::string error_msg = format("Failed to find \"%s\": No such file or directory", file_path.c_str());
    throw std::runtime_error(error_msg);
  }

  // Request throwing of exceptions in case an error occurs.
  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  // Open the file for reading.
  file.open(file_path, std::ios::in);

  if (file.fail()) {
    std::string error_msg = format("Failed to open \"%s\"", file_path.c_str());
    throw std::system_error(errno, std::system_category(), error_msg);
  }

  // Query the file size in bytes.
  file_size = std::filesystem::file_size(file_path);
  if (n_chars > 0) {
    // If given, load only up to n_chars bytes.
    file_size = std::min(n_chars, file_size);
  }

  // Prepare buffer and load contents from disk.
  data.resize(file_size);
  file.seekg(0, std::ios::beg);
  file.read(data.data(), data.size());

  file.close();

  return data;
}
}  // namespace t9::io
