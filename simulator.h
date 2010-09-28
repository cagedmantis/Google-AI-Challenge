#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <string>
#include <vector>
#include "PlanetWars.h"

class Simulator {
 public:
  // Constructor
  Simulator( PlanetWars &pw );
  
  // Return Planet Wars object.
  &Planetwars getPw();

  // Obtain my total ship count.
  int MyShipCount() const;
  
  // Obtain my ship count for ships on a planet.
  int MyPlanetShipCount(int PlanetID) const;

  // Obtain my ship count in fleets.
  int MyFleetShipCount() const;
  
  // Total enemy ship count.
  int EnemyShipCount() const;
  
  // Total enemy planet ship count.
  int EnemyPlanetShipCount(int PlanetID) const;
  
  // Total enemy fleet ship count.
  int EnemyFleetShipCount() const;

  // Total planets.
  int MyPlanetCount() const;
  
  // Total Enemy planets.
  int EnemyPlanetCount() const;

  // Total Neutral planets.
  int NeutralPlanetCount() const;

  // Value of a Planet
  int ValueOfPlanet(int PlanetID) const;

  // Count of my ships enroute to planet.
  int MyShipsEnroute(int PlanetID) const;

  // Count of enemy ships enroute to planet.
  int EnemyShipsEnroute(int PlanetID) const;

  // vector of fleets enroute

  // Average shipcount per planet
  int MyAverageShipCountPerPlanet() const;

  // Enemy Average shipcount per planet.
  int EnemyAverageShipCountPerPlanet() const;

  //**********************************
  // Worth of a planet
  int ValueOfNearbyPlanet(int PlanetID, int PlanetID) const;

  // Worth of a planet
  int ValueOfPlanet(int PlanetID) const;

  // Do I have enough ships to invade?
  bool MyInvadable(int PlanetID) const;
  
  // Does the Enemy have enough ships to invade?
  bool EnemyInvadable(int PlanetID) const; 

  // how many ships does the planet have
  int ShipsOnPlanet(int PlanetID) const;

  // Am I winning or loosing?
  // Is it close to an enemy planet?
  // Do I have enough ships to invade it? 
  
  // Defend a planet.
  void DefendPlanet(int PlanetID) const;

  // Create a pool of planets to send from
  void DeployPool() const;

  // Move ships
  void MoveShips(int PlanetID, int PlanetID);

  // Expected status state
  int ExpectedStatus(int PlanetID, int turns);


  // SIMULATIONS
  void State(int turn);
  
  


 private:

#endif
