/*******************************************************************************
 * Copyright 2009-2013 Jörg Müller
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

#include "file/SndFile.h"
#include "file/SndFileReader.h"
#include "file/SndFileWriter.h"
#include "file/FileManager.h"

AUD_NAMESPACE_BEGIN

SndFile::SndFile()
{
}

void SndFile::registerPlugin()
{
	std::shared_ptr<SndFile> plugin = std::shared_ptr<SndFile>(new SndFile);
	FileManager::registerInput(plugin);
	FileManager::registerOutput(plugin);
}

std::shared_ptr<IReader> SndFile::createReader(std::string filename)
{
	return std::shared_ptr<IReader>(new SndFileReader(filename));
}

std::shared_ptr<IReader> SndFile::createReader(std::shared_ptr<Buffer> buffer)
{
	return std::shared_ptr<IReader>(new SndFileReader(buffer));
}

std::shared_ptr<IWriter> SndFile::createWriter(std::string filename, DeviceSpecs specs, Container format, Codec codec, unsigned int bitrate)
{
	return std::shared_ptr<IWriter>(new SndFileWriter(filename, specs, format, codec, bitrate));
}

#ifdef LIBSNDFILE_PLUGIN
extern "C" void registerPlugin()
{
	SndFile::registerPlugin();
}

extern "C" const char* getName()
{
	return "LibSndFile";
}
#endif

AUD_NAMESPACE_END
