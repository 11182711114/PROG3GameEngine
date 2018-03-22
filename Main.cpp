#include "CimpleBulletEngine.h"
#include "Background.h"
#include "Player.h"
#include <list>
#include "AnimatedSprite.h"
#include "Action.h"
#include <SDL.h>


int main(int argc, char** argv) {
	CimpleBulletEngine* cbe = new CimpleBulletEngine(1200,1000,60,"my title");

	Level* level = new Level("level 1");

	Background* back = new Background(0, 0, 1200, 1000, "C:/Users/Fredrik/source/repos/cBH/media/background.bmp");
	level->addBackground(back);

	Player* player = new Player(0, 0, 145, 50, 500, cbe->getTimeDiff(), "C:/Users/Fredrik/source/repos/cBH/media/right.bmp");
	level->addSprite(player);
	
	KeyAction* playerAction = new KeyAction(player, &Player::speedConstrainedMove);

	CommandManager& cmd = cbe->getCommandManager();
	cmd.bindKey(SDL_SCANCODE_RIGHT, *playerAction);
	cmd.bindKey(SDL_SCANCODE_LEFT, *playerAction);
	cmd.bindKey(SDL_SCANCODE_UP, *playerAction);
	cmd.bindKey(SDL_SCANCODE_DOWN, *playerAction);

	KeyAction* pauseAction = new KeyAction(cbe, &CimpleBulletEngine::pause, 750);
	cmd.bindSystemKey(SDL_SCANCODE_P, *pauseAction);

	Action* quitAction = new Action(cbe, &CimpleBulletEngine::onQuitEvent);
	cmd.bindEvent(SDL_QUIT, *quitAction);

	std::list<AnimationNode*> animation;
	animation.push_back(new AnimationNode("C:/Users/Fredrik/source/repos/cBH/media/right.bmp"));
	animation.push_back(new AnimationNode(500));
	animation.push_back(new AnimationNode("C:/Users/Fredrik/source/repos/cBH/media/left.bmp"));
	animation.push_back(new AnimationNode(500));

	AnimatedSprite* as = new AnimatedSprite(500, 500, 145, 50, animation);
	level->addSprite(as);

	cbe->addLevel(level);
	cbe->start();

	delete cbe;

	return 0;
}