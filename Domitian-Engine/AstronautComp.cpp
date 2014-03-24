#include "AstronautComp.h"

AstronautComp::AstronautComp(double myMaxCO2, double myFuelConsumptionPerForce, double myMaxO2,double myO2Consumption) 
	: Component("Astronaut"), 
	max_co2(myMaxCO2), current_co2(myMaxCO2),
	fuel_cost_per_force(myFuelConsumptionPerForce),
	o2_consumption(myO2Consumption),
	max_o2(myMaxO2), current_o2(myMaxO2)
{

};

void AstronautComp::setCurrentO2(double o2)
{
	current_o2 = o2; 
};
void AstronautComp::setCurrentCO2(double co2)
{
	current_co2 = co2;
};

double AstronautComp::getCurrentO2()
{
	return current_o2;
};
double AstronautComp::getCurrentCO2()
{
	return current_co2;
};

void AstronautComp::setMaxO2(double o2)
{
	max_o2 = o2;
};
void AstronautComp::setMaxCO2(double co2)
{
	max_co2 = co2;
};

double AstronautComp::getMaxO2()
{
	return max_o2;
};
double AstronautComp::getMaxCO2()
{
	return max_co2;
};

void AstronautComp::update(double dt)
{
	current_o2 -= o2_consumption*dt;

	if(current_o2<=0) 
		current_o2 = 0;
};