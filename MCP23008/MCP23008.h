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
 */

#ifndef __MCP23008_H__
#define __MCP23008_H__ 1

#define MCP23008_ADDRESS 0x20
#define MCP23008_IODIR 0x00
#define MCP23008_GPIO 0x09

class MCP23008 {
    int address;
    uint8_t lastRead;
protected:
    uint8_t read8(uint8_t addr);
    void write8(uint8_t addre, uint8_t data);
public:
    MCP23008(int addr=0);
    void begin();
    void begin(int addr);
    void modeAll(int mode);
    uint8_t readAll();
    uint8_t readCached();
    uint8_t readPin(int pin, uint8_t value);
};

#endif
