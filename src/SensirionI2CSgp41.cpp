/*
 * THIS FILE IS AUTOMATICALLY GENERATED
 *
 * I2C-Generator: 0.3.0
 * Yaml Version: 0.1.0
 * Template Version: 0.7.0-62-g3d691f9
 */
/*
 * Copyright (c) 2021, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "SensirionI2CSgp41.h"
#include "Arduino.h"
#include "SensirionCore.h"
#include <Wire.h>

#define SGP41_I2C_ADDRESS 0x59

SensirionI2CSgp41::SensirionI2CSgp41() {
}

void SensirionI2CSgp41::begin(TwoWire& i2cBus) {
    _i2cBus = &i2cBus;
}

uint16_t SensirionI2CSgp41::executeConditioning(uint16_t defaultRh,
                                                uint16_t defaultT,
                                                uint16_t& srawVoc) {
    uint16_t error;
    uint8_t buffer[8];
    SensirionI2CTxFrame txFrame =
        SensirionI2CTxFrame::createWithUInt16Command(0x2612, buffer, 8);

    error = txFrame.addUInt16(defaultRh);
    error |= txFrame.addUInt16(defaultT);
    if (error) {
        return error;
    }

    error = SensirionI2CCommunication::sendFrame(SGP41_I2C_ADDRESS, txFrame,
                                                 *_i2cBus);
    if (error) {
        return error;
    }

    delay(50);

    SensirionI2CRxFrame rxFrame(buffer, 8);
    error = SensirionI2CCommunication::receiveFrame(SGP41_I2C_ADDRESS, 3,
                                                    rxFrame, *_i2cBus);
    if (error) {
        return error;
    }

    error |= rxFrame.getUInt16(srawVoc);
    return error;
}

uint16_t SensirionI2CSgp41::measureRawSignals(uint16_t relativeHumidity,
                                              uint16_t temperature,
                                              uint16_t& srawVoc,
                                              uint16_t& srawNox) {
    uint16_t error;
    uint8_t buffer[8];
    SensirionI2CTxFrame txFrame =
        SensirionI2CTxFrame::createWithUInt16Command(0x2619, buffer, 8);

    error = txFrame.addUInt16(relativeHumidity);
    error |= txFrame.addUInt16(temperature);
    if (error) {
        return error;
    }

    error = SensirionI2CCommunication::sendFrame(SGP41_I2C_ADDRESS, txFrame,
                                                 *_i2cBus);
    if (error) {
        return error;
    }

    delay(50);

    SensirionI2CRxFrame rxFrame(buffer, 8);
    error = SensirionI2CCommunication::receiveFrame(SGP41_I2C_ADDRESS, 6,
                                                    rxFrame, *_i2cBus);
    if (error) {
        return error;
    }

    error |= rxFrame.getUInt16(srawVoc);
    error |= rxFrame.getUInt16(srawNox);
    return error;
}

uint16_t SensirionI2CSgp41::executeSelfTest(uint16_t& testResult) {
    uint16_t error;
    uint8_t buffer[3];
    SensirionI2CTxFrame txFrame =
        SensirionI2CTxFrame::createWithUInt16Command(0x280E, buffer, 3);

    error = SensirionI2CCommunication::sendFrame(SGP41_I2C_ADDRESS, txFrame,
                                                 *_i2cBus);
    if (error) {
        return error;
    }

    delay(320);

    SensirionI2CRxFrame rxFrame(buffer, 3);
    error = SensirionI2CCommunication::receiveFrame(SGP41_I2C_ADDRESS, 3,
                                                    rxFrame, *_i2cBus);
    if (error) {
        return error;
    }

    error |= rxFrame.getUInt16(testResult);
    return error;
}

uint16_t SensirionI2CSgp41::turnHeaterOff() {
    uint16_t error;
    uint8_t buffer[2];
    SensirionI2CTxFrame txFrame =
        SensirionI2CTxFrame::createWithUInt16Command(0x3615, buffer, 2);

    error = SensirionI2CCommunication::sendFrame(SGP41_I2C_ADDRESS, txFrame,
                                                 *_i2cBus);
    delay(1);
    return error;
}

uint16_t SensirionI2CSgp41::getSerialNumber(uint16_t serialNumber[]) {
    uint16_t error;
    uint8_t buffer[9];
    SensirionI2CTxFrame txFrame =
        SensirionI2CTxFrame::createWithUInt16Command(0x3682, buffer, 9);

    error = SensirionI2CCommunication::sendFrame(SGP41_I2C_ADDRESS, txFrame,
                                                 *_i2cBus);
    if (error) {
        return error;
    }

    delay(1);

    SensirionI2CRxFrame rxFrame(buffer, 9);
    error = SensirionI2CCommunication::receiveFrame(SGP41_I2C_ADDRESS, 9,
                                                    rxFrame, *_i2cBus);
    if (error) {
        return error;
    }

    error |= rxFrame.getUInt16(serialNumber[0]);
    error |= rxFrame.getUInt16(serialNumber[1]);
    error |= rxFrame.getUInt16(serialNumber[2]);
    return error;
}
