  
#include <galaxy-explorer/GameAI.hpp>
#include <galaxy-explorer/MyAIData.hpp>

#include <SFML/Graphics.hpp>


GameAI::GameAI(const GameInfo& game_info, sf::RenderTarget* debug_rt)
{
	this->debug_rt = debug_rt;
	this->game_info = game_info;
	this->asteroid_observer = AsteroidsObserver(this);
	this->my_game_ai = new MyAIData();

	//customState().debug_on = false;
}

GameAI::~GameAI() {
	delete my_game_ai;
}

SuggestedAction GameAI::suggestAction(const ShipState& ship_state) {
	debug_rt->clear(sf::Color::Transparent);
        
        AsteroidListItem* traverse = asteroid_observer.asteroids().begin();
        AsteroidListItem* shootThis = NULL;
        double x_dist;
        double y_dist;
        double distance;
        double angleToShoot;
        double x_ast;
        double y_ast;
        double shipAngle = ship_state.millidegree_rotation;
        bool isBetween = false;
        
        while(traverse != NULL) {
            x_dist = traverse->getData().getCurrentHitbox().left - 9000;
            y_dist = 20000 - traverse->getData().getCurrentHitbox().top;
            distance = sqrt(pow(x_dist,2) + pow(y_dist,2));
            if(x_dist < 3000 && x_dist > -3000 && y_dist > 0 && y_dist < 4000 && distance < my_game_ai->shortestDistance) {
                my_game_ai -> shortestDistance = distance;
                shootThis = traverse;
            }   
            traverse = traverse->getNext();
        }
        
        my_game_ai -> shortestDistance = 20000;
        
        //Random shooting from -44 degrees to 44 degrees
        if(ship_state.millidegree_rotation == (-44*1000)) {
            my_game_ai->direction = 1;
        } else if(ship_state.millidegree_rotation == (44*1000)){
            my_game_ai->direction = 0;
        }
        
        //Calculate the angle that the ship needs to turn to shoot the asteroid
        if(shootThis != NULL) {
            x_ast = shootThis->getData().getCurrentHitbox().left -9000;
            y_ast = 20000 - shootThis->getData().getCurrentHitbox().top;
                        
            angleToShoot = 1000*atan(x_ast/y_ast)*(180/3.141519);
            if((shipAngle - shipAngle*0.7) < angleToShoot && (shipAngle + shipAngle*0.7) > angleToShoot) {
                isBetween = true;
            }
        }
        
        if(shootThis != NULL && isBetween) {
            if(shipAngle > angleToShoot - 6000 && shipAngle < angleToShoot + 6000) {
                return SimpleActions::STOP_YAWING_AND_FIRE;
            } else if(shipAngle < angleToShoot) {
                return SuggestedAction{ SuggestedAction::YawingClockwise, SuggestedAction::FiringTry};
            } else {
                return SuggestedAction{ SuggestedAction::YawingAntiClockwise, SuggestedAction::FiringTry};
            }
        } else {
            if(my_game_ai->direction == 1) {
                return SuggestedAction{ SuggestedAction::YawingClockwise, SuggestedAction::FiringTry};
            } else {
                return SuggestedAction{ SuggestedAction::YawingAntiClockwise, SuggestedAction::FiringTry};
            }
        }  
        
}
