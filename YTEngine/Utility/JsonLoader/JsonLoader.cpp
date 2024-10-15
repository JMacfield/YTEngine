/// レベルエディタJSONを読み込むクラス

#include "JsonLoader.h"
#include <cassert>

#include <fstream>

#include "ModelManager.h"
#include "Camera.h"
#include <numbers>

void JsonLoader::RecursiveLoad(nlohmann::json& objects) {
	//"objects"の全オブジェクトを走査
	for (nlohmann::json& object : objects) {
		assert(object.contains("type"));

		//種別を取得
		std::string type = object["type"].get<std::string>();

		//種類ごとの処理
		//MESHの場合
		if (type.compare("MESH") == 0) {
			levelData->objects.emplace_back(LevelData::ObjectData{});
			//今追加した要素の参照を得る
			LevelData::ObjectData& objectData = levelData->objects.back();
			//ここでのファイルネームはオブジェクトの名前
			if (object.contains("file_name")) {
				//ファイル名
				objectData.fileName = object["file_name"];
			}

			//トランスフォームのパラメータ読み込み
			nlohmann::json& transform = object["transform"];
			//平行移動
			objectData.translation.x = (float)transform["translation"][1];
			objectData.translation.y = (float)transform["translation"][2];
			objectData.translation.z = (float)transform["translation"][0];

			//回転角
			const float DEREES_TO_RADIUS_ = (float)std::numbers::pi / 180.0f;
			objectData.rotation.x = -(float)transform["rotation"][1] * DEREES_TO_RADIUS_;
			objectData.rotation.y = -(float)transform["rotation"][2] * DEREES_TO_RADIUS_;
			objectData.rotation.z = -(float)transform["rotation"][0] * DEREES_TO_RADIUS_;

			//スケール
			objectData.scaling.x = (float)transform["scaling"][1];
			objectData.scaling.y = (float)transform["scaling"][2];
			objectData.scaling.z = (float)transform["scaling"][0];



			//コライダーの読み込み
			nlohmann::json& collider = object["collider"];

			objectData.colliderType = object["type"];
			//中心座標
			objectData.center.x = (float)collider["center"][1];
			objectData.center.y = (float)collider["center"][2];
			objectData.center.z = -(float)collider["center"][0];
			//サイズ
			objectData.size.x = (float)collider["size"][1];
			objectData.size.y = (float)collider["size"][2];
			objectData.size.z = (float)collider["size"][0];


			if (object.contains("children")) {
				RecursiveLoad(object["children"]);
			}

		}
	}

}

void JsonLoader::Initialize(const std::string& directoryPath) {
	for (auto& objectData : levelData->objects) {
		decltype(models_)::iterator it = models_.find(objectData.fileName);

		//まだ読み込みがされていない場合読み込む
		if (it == models_.end()) {
			Model* model = nullptr;
			uint32_t modelHandle = ModelManager::GetInstance()->LoadModelFileForLevelData(directoryPath, objectData.fileName);
			model = Model::Create(modelHandle);
			models_[objectData.fileName] = model;
		}

		WorldTransform* worldTransform = new WorldTransform();

		worldTransform->Initialize();
		worldTransform->translate_ = objectData.translation;
		worldTransform->rotate_ = objectData.rotation;
		worldTransform->scale_ = objectData.scaling;



		//配列に登録
		worldTransforms_.push_back(worldTransform);
	}
}


void JsonLoader::Load(const std::string& directoryPath, const std::string& fileName) {

	//ファイルストリーム
	std::ifstream file;

	//ファイルを開く
	std::string filePath = directoryPath + "/" + fileName;
	file.open(filePath);

	if (file.fail()) {
		assert(0);
	}

	//JSON文字列から解凍したデータ
	nlohmann::json deserialized;

	//解凍
	file >> deserialized;

	//正しいレベルデータファイルかチェック
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());

	std::string name = deserialized["name"].get<std::string>();

	assert(name.compare("scene") == 0);

	//レベルデータ格納用インスlタンスを生成
	levelData = new LevelData();

	//読み込み(再帰機能付き)
	RecursiveLoad(deserialized["objects"]);

	//初期化
	Initialize(directoryPath);


}




void JsonLoader::Update() {
	//ワールドトランスフォームの更新
	for (WorldTransform* object : worldTransforms_) {
		object->Update();
	}

}

void JsonLoader::Draw(Camera& camera) {
	uint32_t count = 0;
	for (auto& objectData : levelData->objects) {
		//ファイル名から登録済みモデルを検索
		Model* model = nullptr;
		decltype(models_)::iterator it = models_.find(objectData.fileName);
		//見つかったらmodelに入れる
		if (it != models_.end()) {
			model = it->second;
		}

		model->Draw(*worldTransforms_[count], camera);

		//数を増やしていく
		count++;
	}

}



JsonLoader::~JsonLoader() {

	for (auto& pair : models_) {
		delete pair.second;
	}
	models_.clear();

	for (WorldTransform* object : worldTransforms_) {
		delete object;
	}
	worldTransforms_.clear();

	delete levelData;
}