/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "../gcode.h"
#include "../../module/planner.h"

/**
 * M221: Set extrusion percentage (M221 T0 S95)
 */
void GcodeSuite::M221() {

  const int8_t target_extruder = get_target_extruder_from_command();
  if (target_extruder < 0) return;

  if (parser.seenval('S')) {
    planner.flow_percentage[target_extruder] = parser.value_int();
    planner.refresh_e_factor(target_extruder);
  }
  else {
    SERIAL_ECHO_START();
    SERIAL_CHAR('E');
    SERIAL_CHAR('0' + target_extruder);
    SERIAL_ECHOPAIR(" Flow: ", planner.flow_percentage[target_extruder]);
    SERIAL_CHAR('%');
    SERIAL_EOL();
  }
}
