/// ImGuiで調整したものを保存するクラス

#pragma once

#include <iostream>
#include <variant>
#include <string>
#include <Vector3.h>
#include <map>
#include <fstream>

#include <json.hpp>

//項目
struct Item 
{
	std::variant<int32_t,float, Vector3 >value;
};

//グループ
struct Group 
{
	std::map<std::string, Item>items;
};

//調整項目クラス
class GlobalVariables
{
private:
	
	GlobalVariables() = default;

	~GlobalVariables() = default;

public:

	static GlobalVariables* GetInstance();

	GlobalVariables(const GlobalVariables& obj) = delete;

	GlobalVariables& operator=(const GlobalVariables& obj) = delete;

public:

	/// <summary>
	/// グループの作成
	/// </summary>
	/// <param name="groupName">グループの名前</param>
	void CreateGroup(const std::string& groupName);

	// 値のセット
	void SetValue(const std::string& groupName, const std::string& key, int32_t value);

	void SetValue(const std::string& groupName, const std::string& key, float value);

	void SetValue(const std::string& groupName, const std::string& key, const Vector3 value);

	// 値の追加
	void AddItem(const std::string& groupName, const std::string& key, int32_t value);

	void AddItem(const std::string& groupName, const std::string& key, float value);

	void AddItem(const std::string& groupName, const std::string& key, const Vector3 value);
	
	// 値を取得
	int32_t GetIntValue(const std::string groupName, const std::string& key);

	float GetFloatValue(const std::string groupName, const std::string& key);

	Vector3 GetVector3Value(const std::string groupName, const std::string& key);

	// ファイルのセーブ・ロード
	void SaveFile(const std::string& groupName);

	void LoadFile();

	void LoadFile(const std::string& groupName);
	
	/// <summary>
	/// 更新
	/// </summary>
	void Update();

private:

	std::map<std::string, Group>datas_;

	using json = nlohmann::json;

	const std::string DIRECTORY_PATH_ = "Resources/JsonFile/";
};