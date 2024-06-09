// Copyright (c) 2024, LossRain
// SPDX-License-Identifier: GPLv3

#include "../ThirdParty/minizip-ng/minizip-ng/mz.h"
#include "../ThirdParty/minizip-ng/minizip-ng/mz_strm.h"
#include "../ThirdParty/minizip-ng/minizip-ng/mz_strm_os.h"
#include "../ThirdParty/minizip-ng/minizip-ng/mz_zip.h"
#include "../ThirdParty/minizip-ng/minizip-ng/mz_zip_rw.h"
#include "AssetBundle.h"

namespace ppvs {

class ZipArchive {
public:
	~ZipArchive();
	void* zip_reader = mz_zip_reader_create();
	void* file_stream = mz_stream_os_create();
};

GameAssetSettings* extract_archive(const std::string& archive_fn, const std::string& extract_location, GameAssetSettings* pSettings);

class ZIPArchiveBundle : public FolderAssetBundle {
public:
	ZIPArchiveBundle(Frontend* fe, const std::string& archive_fn, const std::string& extract_location, GameAssetSettings* template_settings);
	std::string get_folder();
};

}