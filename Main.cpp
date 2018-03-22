#include "CimpleBulletEngine.h"
#include "Background.h"
#include "Player.h"
#include <list>
#include "AnimatedSprite.h"
#include "Action.h"
#include <SDL.h>
#include "Enemy.h"


int main(int argc, char** argv) {
	// Create a new engine instance, the name is a lie
	CimpleBulletEngine* cbe = new CimpleBulletEngine(1200,1000,60,"Simple Game");

	// Make a level
	Level* level = new Level("level 1");
	cbe->addLevel(level);

	// Make & add background
	Background* back = new Background(0, 0, 1200, 1000, "media/background.bmp");
	level->addBackground(back);


	// Fetch the CommandManager, which handles all input
	CommandManager& cmd = cbe->getCommandManager();

	// Make an animation for an AnimatedSprite
	std::list<AnimationNode*> playerAnimation;
	playerAnimation.push_back(new AnimationNode("media/right0.bmp"));
	playerAnimation.push_back(new AnimationNode(3));
	playerAnimation.push_back(new AnimationNode("media/right1.bmp"));
	playerAnimation.push_back(new AnimationNode(5));
	playerAnimation.push_back(new AnimationNode("media/right2.bmp"));
	playerAnimation.push_back(new AnimationNode(2));
	playerAnimation.push_back(new AnimationNode("media/right3.bmp"));
	playerAnimation.push_back(new AnimationNode(3));
	playerAnimation.push_back(new AnimationNode("media/right4.bmp"));
	playerAnimation.push_back(new AnimationNode(2));
	playerAnimation.push_back(new AnimationNode("media/right3.bmp"));
	playerAnimation.push_back(new AnimationNode(4));

	// Make a player that in this case is a subtype of AnimedSprite
	Player* player = new Player(0, 0, 1200, 1000, 145, 50, 500, cbe->getTimeDiff(), playerAnimation, level);
	level->addSprite(player);
	
	// Create an action
	KeyAction* playerAction = new KeyAction(player, &Player::speedConstrainedMove, 1);
	// Bind the action to a key, or several keys
	cmd.bindKey(SDL_SCANCODE_RIGHT, *playerAction);
	cmd.bindKey(SDL_SCANCODE_LEFT, *playerAction);
	cmd.bindKey(SDL_SCANCODE_UP, *playerAction);
	cmd.bindKey(SDL_SCANCODE_DOWN, *playerAction);

	// Create & bind an action
	KeyAction* playerFire = new KeyAction(player, &Player::fire, 500);
	cmd.bindKey(SDL_SCANCODE_SPACE, *playerFire);

	// This is for text input which works but is pretty much unusable in its current state due to how it is implemented(badly)
	/*KeyAction* enterAction = new KeyAction(&cmd, &CommandManager::acceptKeyInput, 750);
	cmd.bindSystemKey(SDL_SCANCODE_RETURN, *enterAction);*/

	// More actions
	KeyAction* pauseAction = new KeyAction(cbe, &CimpleBulletEngine::pause, 750);
	cmd.bindSystemKey(SDL_SCANCODE_P, *pauseAction);

	// This is an event action which will fire when the specified event is polled
	Action* quitAction = new Action(cbe, &CimpleBulletEngine::onQuitEvent);
	cmd.bindEvent(SDL_QUIT, *quitAction);

	// Make two enemies
	Enemy* enemy = new Enemy(1000, 750, 1200, 1000, 145, 50, 500, cbe->getTimeDiff(), level, "media/enemy.bmp");
	level->addSprite(enemy);
	Enemy* enemy2 = new Enemy(1000, 250, 1200, 1000, 145, 50, 500, cbe->getTimeDiff(), level, "media/enemy.bmp");
	level->addSprite(enemy2);

	// Start the main game loop
	cbe->start();

	// delete & exit
	delete cbe;
	return 0;
}