#pragma once
#ifndef __KEY_H__
#define __KEY_H__

//! Clase que representa una tecla del sistema
enum Key 
{ 
	/* Direcciones */
	kUP,
	kLEFT,
	kDOWN,
	kRIGHT,

	/* Otras teclas */
	kRCTRL,
	kLCTRL,
	kRSHIFT,
	kLSHIFT,
	kRALT,
	kLALT,

	kESC,
	kENTER,
	kSPACE,
	kBACK,
	kMAYUS,
	kTAB,

	kF1,
	kF2,
	kF3,
	kF4,
	kF5,
	kF6,
	kF7,
	kF8,
	kF9,

	/* Teclado numérico */
	kN0,
	kN1,
	kN2,
	kN3,
	kN4,
	kN5,
	kN6,
	kN7,
	kN8,
	kN9,

	/* Letras */
	kA, kB, kC, kD, kE, kF, kG, kH, kI, kJ, kK, kL, kM, kN, kO, kP, kQ, kR, kS, kT, kU, kV, kW, kX, kY, kZ
};
#endif