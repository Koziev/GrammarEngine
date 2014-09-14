// -----------------------------------------------------------------------------
// File PHYSCONS.H
//
// (c) by Koziev Elijah, Obninsk, Russia, 1995-2004
//
// Набор физических констант. Physical constans (from MATHCAD PLUS)
// -----------------------------------------------------------------------------
//
// CD->11.07.95
// LC->16.10.04
// ------------

#ifndef LEM_PHYSICAL_CONST__H
#define LEM_PHYSICAL_CONST__H
#pragma once

 #include <lem/real.h>
 #include <lem/math_constants.h>

 const REAL PHYS_c  = 299792458;      // Скорость света, м/с. Velocity of light in a vacuum, [m/sec].
 const REAL PHYS_G  = 6.67259e-11;    // Гравитационная постоянная. Gravitational constant, [m^3/(kg*s^2)].
 const REAL PHYS_NA = 6.0221367e23;   // Постоянная Авогадро. Avogadro's number, [1/mole].
 const REAL PHYS_Mp = 1.6726231e-27;  // Масса покоя протона, кг. Proton rest mass, [kg].
 const REAL PHYS_Mn = 1.6749286e-27;  // Масса покоя нейтрона, кг. Neutron rest mass, [kg].
 const REAL PHYS_Me = 9.1093897e-31;  // Масса покоя электрона, кг. Electron rest mass, [kg].
 const REAL PHYS_e  = 1.60217733e-19; // Заряд электрона, Кл Electron charge, [coul].
 const REAL PHYS_h  = 6.6260755e-34;  // Постоянная Планка, Дж*сек. Planck's constant, [joule*sec].
 const REAL PHYS_ma = 1.6605402e-27;  // Atomic mass unit, [kg]


 const REAL PHYS_E0 = 1.e-7/(4.*PI*PHYS_C*PHYS_C); // Электр. пост, Ф/м.
 const REAL PHYS_M0 = 4.*PI*1e-7;  // Магнитная постоянная, Гн/м.

 const REAL PHYS_VM  = 0.00224138;  // Молярный объем ид. газа при н.у., м^3/моль
 const REAL PHYS_R   = 8.314;       // Моляр. газ. пост., Дж/(К*моль)
 const REAL PHYS_F   = 96485;       // Пост. Фарадея, Кл/моль
 const REAL PHYS_k   = 1.38066e-23; // Пост. Больцмана, Дж/К
 const REAL PHYS_e0  = 1.e-7/(4.*PI*PHYS_C*PHYS_C); // Permittivity of vacuum, [farad/m].
 const REAL PHYS_mu0 = 4.e-7*PI;    // Permeability of vacuum, [newton/amp^2].
 const REAL PHYS_ncw = 1,31959110e-15; // Neutron Compton wavelengh, [m].
 const REAL PHYS_mrm = 1.8835327e-28; // Muon rest mass, [kg].
 const REAL PHYS_cer = 2.81794092e-15; // Classical electron radius, [m].
 const REAL PHYS_qc  = 3.63694807e-4; // Quantum of circulation, [m^2/s].
 const REAL PHYS_mvg = 22.41410; // Molar volume of ideal gas at STP, [liter/mole].
 const REAL PHYS_fc  = 96485.309; // Faraday constant, [coul/mole].
 const REAL PHYS_sbc = 5.67051e-8; // Stefan-Boltzmann constant, [watt/(m^2*K^4)]
 const REAL PHYS_rc  = 10973731.534; // Rydberg constant, [1/m]
 const REAL PHYS_br  = 0.529177249e-10; // Bohr radius, [m].
 const REAL PHYS_emm = 928.47701e-26; // Electron magnetic moment, [joule/tesla].
 const REAL PHYS_pmm = 1.41060761e-26; // Proton magnetic moment, [joule/tesla].
 const REAL PHYS_bm  = 9.2740154e-24; // Bohr magneton, [joule/tesla].
 const REAL PHYS_nm  = 5.0507866e-27; // Nuclear magneton, [joule/tesla].
 const REAL PHYS_fsc = 7.29735308e-3; // Fine structure constant.
 const REAL PHYS_ecw = 2.42631058e-12; // Electron Compton wavelength, [m].
 const REAL PHYS_pcw = 1.32141002e-15; // Proton Compton wavelength, [m].
 const REAL PHYS_mgc = 8.314510; // Molar gas constant, [joule/(mole*K)].
 const REAL PHYS_k   = 1.380658e-23; // Boltzmann's constant, [joule/K].
 const REAL PHYS_frc = 3.7417749e-16; // First radiation constant, [watt*m^2].
 const REAL PHYS_src = 0.01438769; // Second radiation constant, [m*K].


 /*************************************************************************
  MATHCAD Physical Constants are from:

  CRC Handbook of Chemistry and Physics, 72nd edition, edited by
  David R. Lide, CRC Press, 1991.
 *************************************************************************/
 
/*
      ***  Нестандартные единицы измерения  ***

                1 Ангстрем = 1e-10 м
                1 дюйм     = 2.54e-2 м
                1 ферми    = 1e-15 м
                1 барн     = 1e-28 м^2
                1 а.е.     = 1.49e11 м
                1 св. год  = 9.46e15 м
                1 кг.-с.   = 9.81 Н
                1 эрг      = 1e-7 Дж
                1 калория  = 4.19 Дж
                1 эВ       = 1.60e-19 Дж
                1 л.с.     = 736 Вт
                1 ат.      = 9.81e4 Па
                1 мм.рт.с. = 133 Па
                1 атм.     = 1.01e5 Па
                1 Кюри     = 3.7e10 Бк
                1 рад      = 1e-2 Гр
                1 рентген  = 2.58e-4 Кл/кг
*/

/*
                   Разное

  Средний радиус Земли = 6.37e6 м
  Средняя плотность Земли = 5500 кг/м^3
  Масса Земли = 5.96e24 кг
  Радиус Солнца = 6.95e30 м
  Радиус Луны = 1.74e6 м
  Масса Солнца = 1.97e30 кг
  Масса Луны = 7.3e22 кг 
  Средняя Плотность Солнца = 1400 кг/м^3
*/

#endif
// ------------------------- End Of File [PHYSCONS.H] --------------------------
