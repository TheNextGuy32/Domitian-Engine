#ifndef AstronautComp_H
#define AstronautComp_H

#include "Component.h"

class AstronautComp : public Component
{
public:
	AstronautComp(double myMaxCO2, double myFuelCostPerForce, double myMaxO2,double myO2Consumption);

	void setCurrentO2(double o2);
	void setCurrentCO2(double co2);

	double getCurrentO2();
	double getCurrentCO2();

	void setMaxO2(double o2);
	void setMaxCO2(double co2);

	double getMaxO2();
	double getMaxCO2();

	double getFuelCost()
	{
		return fuel_cost_per_force;
	};
	double getO2Consumption()
	{
		return o2_consumption;
	}

	void update(double dt);
private:
	double max_co2;
	double current_co2;
	double fuel_cost_per_force;

	double max_o2;
	double current_o2;
	double o2_consumption;
};
#endif