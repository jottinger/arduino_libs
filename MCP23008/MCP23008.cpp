/************************************************************
 * This is a library to aid in block reads from an MCP23008.
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
 * This code owes a great deal to the Adafruit_MCP23008
 * library, written by Limor Fried/ladyada. Any similarities
 * are very intentional, and any errors are mine.
 *
 * See https://github.com/adafruit/Adafruit-MCP23008-library
 */

#include "Arduino.h"
#include <Wire.h>
#include <avr/pgmspce.h>
#include "MCP23008.h"

MCP23008::MCP23008(int addr) {
    address=addr;
}

void MCP23008::begin(int addr) {
    address=addr;
    begin();
}

void MCP23008::begin() {
    Wire.begin();
    Wire.beginTransmission(MCP23008_ADDRESS|address);
    Wire.write((byte)MCP23008_IODIR);
    Wire.write((byte)0xff); // all inputs
    for(int i=0; i<9; i++) {
        Wire.write((byte)0x00);
    }
    Wire.endTransmission();
}

uint8_t MCP23008::read8(uint8_t addr) {
    Wire.beginTransmission(MCP23008_ADDRESS | address);
    Wire.write((byte)addr);
    Wire.endTransmission();
    Wire.requestFrom(MCP23008_ADDRESS | address, 1);
    lastRead=Wire.read();
    return lastRead;
}

void MCP23008::write8(uint8_t addr, uint8_t data) {
    Wire.beginTransmission(MCP23008_ADDRESS | address);
    Wire.write((byte)addr);
    Wire.write((byte)data);
    Wire.endTransmission();
}

void MCP23008::modeAll(int mode) {
    uint8_t iodir=0x00;
    if(mode==HIGH) {
        iodir=0xff;
    }
    write8(MCP23008_IODIR, iodir);
}

uint8_t MCP23008::readAll() {
    return read8(MCP23008_GPIO);
}

/* Note lack of error checking here! */
uint8_t MCP23008::readCached() {
    return lastRead;
}

uint8_t MCP23008::readPin(int pin, uint8_t value) {
    return (value & (1<<pin))!=0;
}

