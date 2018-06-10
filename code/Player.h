#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d;
class Player : public cocos2d::Sprite
{
private:
	int _runTag;//ִ�ж���
	bool _move;//�Ƿ��ƶ�

public:
	static Player* create(const std::string& filename) {
		Player * sprite = new Player();
		if (sprite && sprite->initWithFile(filename)) {
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}

	void setRunTag(int tag) {
		_runTag = tag;
	}

	int getRunTag() {
		return _runTag;
	}

	void setMove(bool m) {
		_move = m;
	}

	int getMove() {
		return _runTag;
	}
};

