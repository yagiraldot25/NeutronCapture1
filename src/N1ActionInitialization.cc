/*
 * Neutron Capture 1.0
 * Copyright (c) 2020
 * Universidad Nacional de Colombia
 * Servicio Geológico Colombiano
 * All Right Reserved.
 *
 * Developed by Andrea Giraldo Torres
 *              Andrés Camilo Sevilla Moreno
 *
 * Use and copying of these libraries and preparation of derivative works
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 *
 * Bogotá, Colombia.
 *
 */

// N1 Headers


#include "N1RunAction.hh"
#include "N1EventAction.hh"
#include "N1TrackingAction.hh"
#include "N1SteppingAction.hh"
#include "N1ActionInitialization.hh"
#include "N1PrimaryGeneratorAction.hh"

N1ActionInitialization::N1ActionInitialization():G4VUserActionInitialization()
{}

N1ActionInitialization::~N1ActionInitialization()
{}

void N1ActionInitialization::BuildForMaster() const
{
	SetUserAction(new N1RunAction());
}

void N1ActionInitialization::Build() const
{

  SetUserAction(new N1PrimaryGeneratorAction);
  SetUserAction(new N1RunAction());
  SetUserAction(new N1EventAction());
  SetUserAction(new N1TrackingAction());
  SetUserAction(new N1SteppingAction());

}
