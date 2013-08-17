/*
 * WebRadio web-based Software Defined Radio
 *
 * Copyright (C) 2013 Mike Stirling
 *
 * This file is part of WebRadio (http://www.mike-stirling.com/webradio)
 *
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>

#include "randsource.h"

RandSource::RandSource(const string &name) :
	SourceBlock(DspData::Int16, name, "RandSource")
{

}

RandSource::~RandSource()
{

}

bool RandSource::init()
{
	/* Output is always whatever was asked for */
	_outputSampleRate = inputSampleRate();
	_outputChannels = inputChannels();

	return true;
}

void RandSource::deinit()
{

}

bool RandSource::process(const DspData &in, DspData &out)
{
	out.resize(in.size());

	short *outptr = (short*)out.data();

	for (unsigned int n = 0; n < out.size() * outputChannels(); n++)
		*outptr++ = (short)random();

	return true;
}
