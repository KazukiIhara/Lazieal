#pragma once

// リークチェッカ
class D3DResourceLeakChecker {
public:
	static D3DResourceLeakChecker* GetInstance();
private:
	D3DResourceLeakChecker() = default;
	~D3DResourceLeakChecker();
	D3DResourceLeakChecker(const D3DResourceLeakChecker&) = delete;
	const D3DResourceLeakChecker& operator=(const D3DResourceLeakChecker&) = delete;
};