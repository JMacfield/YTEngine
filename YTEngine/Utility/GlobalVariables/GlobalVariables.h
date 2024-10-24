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

	/// <summary>
	/// 値のセット int32_t型
	/// </summary>
	/// <param name="groupName">グループネーム</param>
	/// <param name="key">キー</param>
	/// <param name="value">値</param>
	void SetValue(const std::string& groupName, const std::string& key, int32_t value);

	/// <summary>
	/// 値のセット float型
	/// </summary>
	/// <param name="groupName">グループネーム</param>
	/// <param name="key">キー</param>
	/// <param name="value">値</param>
	void SetValue(const std::string& groupName, const std::string& key, float value);

	/// <summary>
	/// 値のセット Vector3型
	/// </summary>
	/// <param name="groupName">グループネーム</param>
	/// <param name="key">キー</param>
	/// <param name="value">値</param>
	void SetValue(const std::string& groupName, const std::string& key, const Vector3 value);

	/// <summary>
	/// 追加する物 int32_t型
	/// </summary>
	/// <param name="groupName">グループネーム</param>
	/// <param name="key">キー</param>
	/// <param name="value">値</param>
	void AddItem(const std::string& groupName, const std::string& key, int32_t value);

	/// <summary>
	/// 追加する物 float型
	/// </summary>
	/// <param name="groupName">グループネーム</param>
	/// <param name="key">キー</param>
	/// <param name="value">値</param>
	void AddItem(const std::string& groupName, const std::string& key, float value);

	/// <summary>
	/// 追加する物 Vector3型
	/// </summary>
	/// <param name="groupName">グループネーム</param>
	/// <param name="key">キー</param>
	/// <param name="value">値</param>
	void AddItem(const std::string& groupName, const std::string& key, const Vector3 value);
	
	/// <summary>
	/// Intの値を取得
	/// </summary>
	/// <param name="groupName">グループネーム</param>
	/// <param name="key">キー</param>
	/// <returns>Int</returns>
	int32_t GetIntValue(const std::string groupName, const std::string& key);

	/// <summary>
	/// Floatの値を取得
	/// </summary>
	/// <param name="groupName">グループネーム</param>
	/// <param name="key">キー</param>
	/// <returns>Float</returns>
	float GetFloatValue(const std::string groupName, const std::string& key);

	/// <summary>
	/// Vector3の値を取得
	/// </summary>
	/// <param name="groupName">グループネーム</param>
	/// <param name="key">キー</param>
	/// <returns>Vector3</returns>
	Vector3 GetVector3Value(const std::string groupName, const std::string& key);

	/// <summary>
	/// ファイルのセーブ
	/// </summary>
	/// <param name="groupName">ファイルの名前</param>
	void SaveFile(const std::string& groupName);

	/// <summary>
	/// ファイルの読み込み
	/// </summary>
	void LoadFile();

	/// <summary>
	/// ファイルの読み込み
	/// </summary>
	/// <param name="groupName">ファイルの名前</param>
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