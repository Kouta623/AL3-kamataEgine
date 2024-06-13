#include "MapchipField.h"
#include <assert.h>
#include <fstream>
#include <map>
#include <sstream>

namespace {

std::map<std::string, MapChipType> mapchipTabale = {

    {"0", MapChipType::kBlank},
    {"1", MapChipType::kBlock},
};
}

void MapchipField::ResetMapChipData() {

	mapChipData_.data.clear();
	mapChipData_.data.resize(kNumBlockVirtical);
	for (std::vector<MapChipType>& mapChipDataLine : mapChipData_.data) {

		mapChipDataLine.resize(kNumBlockHorizontal);
	}
}

void MapchipField::LoadMapChipCsv(const std::string& filePath) {

	// マップチップデータをリセット
	ResetMapChipData();

	// ファイルを開く
	std::ifstream file;
	file.open(filePath);
	assert(file.is_open());

	// マップチップcsv
	std::stringstream mapChipCsv;
	// ファイルの内容を文字列ストリームにコピー
	mapChipCsv << file.rdbuf();
	// ファイルを閉じる
	file.close();

	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {

		std::string line;
		getline(mapChipCsv, line);

		// 1行分の文字列をストリーミングに変換して解析しやすくする
		std::istringstream line_stream(line);

		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {

			std::string word;
			getline(line_stream, word, ',');

			if (mapchipTabale.contains(word)) {

				mapChipData_.data[i][j] = mapchipTabale[word];
			}
		}
	}
}

MapChipType MapchipField::GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex) {

	if (xIndex < 0 || kNumBlockHorizontal - 1 < xIndex) {
		return MapChipType::kBlank;
	}

	if (yIndex < 0 || kNumBlockVirtical - 1 < yIndex) {
		return MapChipType::kBlank;
	}

	return mapChipData_.data[yIndex][xIndex];
}

Vector3 MapchipField::GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex) { return Vector3(kBlockWidth * xIndex, kBlockHeight * (kNumBlockVirtical - 1 - yIndex), 0); }

int MapchipField::GetNumBlockVirtical() { return kNumBlockVirtical; }

int MapchipField::GetNumBlockHorizontal() { return kNumBlockHorizontal; }

IndexSet MapchipField::GetMapchipIndexsetByPosition(const Vector3& position) {

	uint32_t xindex = static_cast<uint32_t>((position.x + kBlockWidth / 2) / kBlockWidth);
	uint32_t yindex = static_cast<uint32_t>((position.y + kBlockHeight / 2) / kBlockHeight);
	int32_t maxIndexY = kNumBlockVirtical - 1;
	yindex = maxIndexY - yindex;

	IndexSet indexSet;
	indexSet.xIndex = xindex;
	indexSet.yIndex = yindex;

	return indexSet;
}

Rect MapchipField::GetRectByIndex(uint32_t xIndex, uint32_t yIndex) {
	Vector3 center = GetMapChipPositionByIndex(xIndex, yIndex);
	Rect rect;
	rect.left = center.x - kBlockWidth / 2.0f;
	rect.right = center.x - kBlockWidth / 2.0f;
	rect.bottom = center.x - kBlockWidth / 2.0f;
	rect.top = center.x - kBlockWidth / 2.0f;

	return rect;
}
