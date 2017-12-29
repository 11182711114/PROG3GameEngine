#include "CimpleBulletEngine.h"
#include "Background.h"
#include "Player.h"
#include <list>
#include "AnimatedSprite.h"
#include "Action.h"


int main(int argc, char** argv) {
	CimpleBulletEngine* cbe = new CimpleBulletEngine(1200,1000,60,"my title");

	Background* back = new Background(0, 0, 1200, 1000, "C:/Users/Fredrik/source/repos/cBH/media/background.bmp");
	cbe->addSprite(back);

	Player* player = new Player(0, 0, 145, 50, 500, cbe->getTimeDiff(), "C:/Users/Fredrik/source/repos/cBH/media/right.bmp");
	cbe->addSprite(player);
	
	Action* playerAction = new Action(player, &Player::onEvent);
	cbe->addCommand(SDL_KEYDOWN, playerAction);

	Action* quitAction = new Action(cbe, &CimpleBulletEngine::onQuitEvent);
	cbe->addCommand(SDL_QUIT, quitAction);

	std::list<AnimationNode*> animation;
	animation.push_back(new AnimationNode("C:/Users/Fredrik/source/repos/cBH/media/right.bmp"));
	animation.push_back(new AnimationNode(500));
	animation.push_back(new AnimationNode("C:/Users/Fredrik/source/repos/cBH/media/left.bmp"));
	animation.push_back(new AnimationNode(500));

	AnimatedSprite* as = new AnimatedSprite(500, 500, 145, 50, animation);
	cbe->addSprite(as);

	cbe->start();

	delete cbe;

	return 0;
}