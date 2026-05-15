#include "GameObject.h"


// コンストラクタ
GameObject::GameObject() 
	: image()
	, z_layer()
{

}

// 初期化
void GameObject::Initialize()
{

}

// 更新
void GameObject::Update(float delta_time)
{

}

// 描画
void GameObject::Draw() const
{

}

// 終了
void GameObject::Finalize()
{

}

// Zレイヤー取得
const unsigned char GameObject::GetZLayer() const
{
	return z_layer;
}

// 座標設定
void GameObject::SetLocation(const Vector2D location)
{
	this->location = location;
}

//座標取得
const Vector2D GameObject::GetLocation()
{
	return this->location;
}

