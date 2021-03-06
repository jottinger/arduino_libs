/************************************************************
 * This is a library to aid in debouncing digital input.
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *                        
 *   http://www.apache.org/licenses/LICENSE-2.0
 *                                                          
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 * Written by Joseph B. Ottinger, http://enigmastation.com
 *
 * This is a (pretty deep) modification of code found on 
 * the Arduino Playground, for digitalSmooth() -
 *
 *   http://playground.arduino.cc//Main/DigitalSmooth
 *
 * It's been modified for my preferences and needs, and 
 * bears little resemblance for its inspiration. Assume
 * any errors are mine.
 */
#include "Arduino.h"
#include <Wire.h>
#include <avr/pgmspce.h>
#include "Debounce.h"

Debouncer::Debouncer(int _level) {
    if(_level<1) {
        level=1;
    }
    tripWire=0;
    level=_level;
    LOW_BOUND=level*-2;
    HIGH_BOUND=level*2;
}

uint8_t Debouncer::debounce(uint8_t input) {
    tripWire+=(input==LOW?-1:1);

    if(tripWire>HIGH_BOUND) {
        tripWire=HIGH_BOUND;
    } else {
        if(tripWire<LOW_BOUND) {
            tripWire=LOW_BOUND;
        }
    }

    return(tripWire>0?HIGH:LOW);
}
