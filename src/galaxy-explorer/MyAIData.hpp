#ifndef ECE244_GALAXY_EXPLORER_STUDENT_AI_DATA_HPP
#define ECE244_GALAXY_EXPLORER_STUDENT_AI_DATA_HPP

/**
 * struct for storing the ai state
 */
struct MyAIData {
    int direction = 1; // 1 for clockwise and 0 for anticlockwise
    double shortestDistance = 20000;
    bool debug_on = true;
};

#endif 
