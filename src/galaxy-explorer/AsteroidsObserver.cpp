#include <galaxy-explorer/AsteroidsObserver.hpp>

//Function that inserts a new asteroid in range at the end of the list using the insertAfter function
void AsteroidsObserver::onAsteroidInRange(Asteroid asteroid) {
    AsteroidList* list = &asteroid_list;
    list -> insertAfter(list->beforeEnd(), asteroid);
}

//Function that updates the asteroid data by deleting the asteroid then inserting the same asteroid with updated information
void AsteroidsObserver::onAsteroidUpdate(Asteroid asteroid) {
    AsteroidListItem* temp = asteroid_list.begin();
    AsteroidListItem* beforeTemp = asteroid_list.beforeBegin();
    while(temp != NULL) {
        if(temp -> getData().getID() == asteroid.getID()) {
            break;
        }
        beforeTemp = temp;
        temp = temp -> getNext();
    }
    if(temp != NULL) {
        asteroid_list.eraseAfter(beforeTemp);
        asteroid_list.insertAfter(beforeTemp, asteroid);
    } else {
        onAsteroidInRange(asteroid);
    }
}

//Function to traverse through the list and find the asteroid with the same ID
//If found, it deletes it
void AsteroidsObserver::onAsteroidOutOfRange(Asteroid asteroid) {
    AsteroidListItem* temp = asteroid_list.begin();
    AsteroidListItem* beforeTemp = asteroid_list.beforeBegin();
    while(temp != NULL) {
        if(temp -> getData().getID() == asteroid.getID()) {
            break;
        }
        beforeTemp = temp;
        temp = temp -> getNext();
    }
    if(temp != NULL) {
        asteroid_list.eraseAfter(beforeTemp);
    }
}

//Function to traverse through the list and find the asteroid with the same ID
//If found, it deletes it
void AsteroidsObserver::onAsteroidDestroy(Asteroid asteroid) {
    AsteroidListItem* temp = asteroid_list.begin();
    AsteroidListItem* beforeTemp = asteroid_list.beforeBegin();
    while(temp != NULL) {
        if(temp -> getData().getID() == asteroid.getID()) {
            break;
        }
        beforeTemp = temp;
        temp = temp -> getNext();
    }
    if(temp != NULL) {
        asteroid_list.eraseAfter(beforeTemp);
    }
}
