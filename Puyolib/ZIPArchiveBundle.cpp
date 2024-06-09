// Copyright (c) 2024, LossRain
// SPDX-License-Identifier: GPLv3

#include "ZIPArchiveBundle.h"

#include <filesystem>
#include <unistd.h>
#include <utility>

// FIXME: This is not a great solution, use std::filesystem instead
#ifdef _WIN32
#define FF_SEPARATOR '\\'
#else
#define FF_SEPARATOR '/'
#endif

namespace ppvs {

ZipArchive::~ZipArchive()
{
	mz_zip_reader_close(zip_reader);
	mz_stream_os_close(file_stream);
}

// Attempts to extract the whole contents of archive into extract_location.
// FIXME: Implement bytestream-based import of all assets on all clients and replace this potential nightmare with handling bytestream
GameAssetSettings* extract_archive(const std::string& archive_fn, const std::string& extract_location, GameAssetSettings* gas)
{
	// The name of the subfolder we will extract to
	std::string bundle_name = std::filesystem::path(archive_fn.c_str()).stem();
	// The path to which we will extract this bundle
	std::filesystem::path extract_folder = std::filesystem::path(extract_location.c_str()) / bundle_name;

	// Test if folder already exists, do not duplicate work
	if (std::filesystem::exists(extract_folder) and not access(extract_folder.c_str(), R_OK)) {
		if (not std::filesystem::is_empty(extract_folder)) {
			gas->baseAssetDir = extract_folder.string() + FF_SEPARATOR;
			gas->is_valid = true;
			return gas;
		}
	}

	// Test write access to extraction folder
	if (access(extract_location.c_str(), W_OK)) {
		// We can NOT write to the folder, attempt creating
		if (not std::filesystem::create_directory(extract_location)) {
			gas->is_valid = false;
			gas->reason = 1;
			return gas;
		}
	}

	// Create folder
	if (not std::filesystem::exists(extract_folder)) {
		if (not std::filesystem::create_directory(extract_folder)) {
			// Folder creation failed
			gas->is_valid = false;
			gas->reason = 2;
			return gas;
		}
	}

	std::unique_ptr<ZipArchive> archive = std::make_unique<ZipArchive>();

	// Open archive file
	if (mz_stream_os_open(archive->file_stream, archive_fn.c_str(), MZ_OPEN_MODE_READ) != MZ_OK) {
		gas->is_valid = false;
		gas->reason = 3;
		return gas;
	}
	// Open minizip reader
	if (mz_zip_reader_open(archive->zip_reader, archive->file_stream) != MZ_OK) {
		gas->is_valid = false;
		gas->reason = 4;
		return gas;
	}
	// Extract
	if (mz_zip_reader_save_all(archive->zip_reader, extract_folder.c_str()) != MZ_OK) {
		gas->is_valid = false;
		gas->reason = 5;
		return gas;
	}

	// Set bundle valid
	gas->baseAssetDir = extract_folder.string() + FF_SEPARATOR;
	gas->is_valid = true;
	return gas;
}

ZIPArchiveBundle::ZIPArchiveBundle(Frontend* fe, const std::string& archive_fn, const std::string& extract_location, GameAssetSettings* template_settings)
	: FolderAssetBundle(fe, extract_archive(archive_fn, extract_location, template_settings))
{
}

// Debug function for determining the final folder location
std::string ZIPArchiveBundle::get_folder()
{
	return m_settings->baseAssetDir;
}
// ppvs
}